#!/usr/bin/env python3
"""DL2 reproducible status CLI. Run with --help for commands."""
import argparse
import json
import os
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET
from pathlib import Path

from status_metrics.core import byte_summary, percentage, regressions, sha256
from status_metrics.report import render
from status_metrics.runner import (ROOT, build_info, collect_coverage, discover, execute_case,
                                  read_json, source_fingerprint, timestamp, write_json)


def parse_junit(path):
    tests = {}
    for node in ET.parse(path).iter("testcase"):
        name = node.attrib["name"]
        if name in tests:
            raise ValueError(f"duplicate CTest result: {name}")
        tests[name] = ("skipped" if node.find("skipped") is not None else
                       "failed" if node.find("failure") is not None or node.find("error") is not None
                       or node.attrib.get("status") in {"fail", "notrun"} else "passed")
    if not tests:
        raise ValueError("CTest reported no tests")
    return tests


def executable_hashes(build):
    files = list(build.rglob("*.exe")) + list(build.rglob("*.dll"))
    if os.name != "nt":
        files += [p for directory in (build / "src", build / "tests") for p in directory.rglob("*")
                  if p.is_file() and os.access(p, os.X_OK) and not p.suffix]
    return {p.relative_to(build).as_posix(): sha256(p.read_bytes()) for p in sorted(set(files))}


def run_tests(args):
    build = args.build_dir.resolve()
    if os.name == "nt":
        command = ["powershell", "-NoProfile", "-ExecutionPolicy", "Bypass", "-File",
                   str(ROOT / "tools/build.ps1"), "-BuildDir", str(build), "-Configuration", args.configuration]
        if args.data_dir:
            command += ["-DataDir", str(args.data_dir.resolve())]
    else:
        command = ["cmake", "--build", str(build), "--config", args.configuration]
    subprocess.run(command, cwd=ROOT, check=True)
    receipt = build / "status-ctest.json"
    # Invalidate old receipt before execution, including interrupted runs.
    write_json(receipt, {"valid": False})
    junit = build / "status-ctest.xml"
    junit.unlink(missing_ok=True)
    fingerprint = source_fingerprint()
    result = subprocess.run(["ctest", "--test-dir", str(build), "-C", args.configuration,
                             "--output-on-failure", "--no-tests=error", "--output-junit", str(junit)], cwd=ROOT)
    tests = parse_junit(junit)
    if fingerprint != source_fingerprint():
        raise ValueError("source changed during CTest; rerun tests")
    write_json(receipt, {"valid": True, "source_fingerprint": fingerprint, "tests": tests,
                         "executables": executable_hashes(build), "timestamp": timestamp(),
                         "exit_code": result.returncode})
    return result.returncode


def functional_results(build):
    receipt_path = build / "status-ctest.json"
    if not receipt_path.is_file():
        raise ValueError("missing CTest receipt; execute run-tests first")
    receipt = read_json(receipt_path)
    if not receipt.get("valid") or receipt["source_fingerprint"] != source_fingerprint():
        raise ValueError("stale CTest receipt: source changed; execute run-tests again")
    if receipt["executables"] != executable_hashes(build):
        raise ValueError("build binaries changed since CTest; execute run-tests again")
    tests = receipt["tests"]
    result = {state: sum(v == state for v in tests.values()) for state in ("passed", "failed", "skipped")}
    result.update(tests=tests, total=len(tests), percentage=percentage(result["passed"], len(tests)),
                  timestamp=receipt["timestamp"], exit_code=receipt["exit_code"])
    return result


def import_originals(data_dir, destination):
    """Reuse savparse's HDX reader. References are original artifacts, not port captures."""
    import savparse
    required = ("TUTORIAL.SAV", "LEVELS.HDX", "LEVELS.HDD")
    if data_dir is None or any(not (data_dir / name).is_file() for name in required):
        return {"name": "original-save-corpus", "status": "skipped",
                "reason": "original data unavailable (TUTORIAL.SAV, LEVELS.HDX/HDD)"}
    items = [("TUTORIAL.SAV", (data_dir / "TUTORIAL.SAV").read_bytes())]
    for relative in ("Saves/AUTOSAVE.SAV", "Campaign/AUTOSAVE.CPN", "Campaign/ChCht001.CPN"):
        path = data_dir / relative
        if path.is_file():
            items.append((relative, path.read_bytes()))
    items.extend(("LEVELS/" + name, blob) for name, blob in savparse.read_hdx(str(data_dir / "LEVELS")))
    if len({name for name, _ in items}) != len(items):
        raise ValueError("duplicate original corpus entry")
    for name, blob in items:
        # Stable, collision-resistant IDs independent of directory iteration order.
        test_id = "save-" + sha256(name.encode())[:16]
        directory = destination / test_id
        directory.mkdir(parents=True, exist_ok=False)
        (directory / "input.bin").write_bytes(blob)
        (directory / "expected.bin").write_bytes(blob)
        write_json(directory / "metadata.json", {
            "id": test_id, "module": "save_codec", "function": "readDocument/writeDocumentCopy",
            "description": "Lossless preservation of " + name, "version": "original-artifact-sha256:" + sha256(blob),
            "provenance": {"kind": "original-artifact", "source": name, "sha256": sha256(blob),
                           "scope": "archival roundtrip; no execution of the original game"},
            "critical": True, "command": ["{cli}", "roundtrip", "{input}", "{output}"],
            "input_sha256": sha256(blob), "expected_sha256": sha256(blob)})
    return {"name": "original-save-corpus", "status": "available", "tests": len(items)}


def locate(build, name, configuration):
    suffix = ".exe" if os.name == "nt" else ""
    folder = "tests" if name == "golden_probe" else "src"
    for path in (build / folder / (name + suffix), build / folder / configuration / (name + suffix)):
        if path.is_file():
            return str(path.resolve())
    return str(build / folder / (name + suffix))


def run_bytes(args):
    build, output = args.build_dir.resolve(), args.output.resolve()
    functional = functional_results(build)
    # Fresh output avoids stale binaries/diffs and never overwrites original data.
    output.mkdir(parents=True, exist_ok=False)
    info = build_info()
    dataset = import_originals(args.data_dir.resolve() if args.data_dir else None, output / "original-goldens")
    cases = discover(args.golden_dir)
    if dataset["status"] == "available":
        cases.extend(discover(output / "original-goldens"))
    if len({meta["id"] for _, meta in cases}) != len(cases):
        raise ValueError("duplicate golden IDs across catalogs")
    bindings = {"cli": locate(build, "dl2save", args.configuration),
                "probe": locate(build, "golden_probe", args.configuration)}
    tests = [execute_case(directory, meta, output, bindings, info) for directory, meta in cases]
    libraries, shaders = collect_coverage(tests, functional["tests"])
    report = {"schema_version": 1, "timestamp": timestamp(), "build": info, "tests": tests,
              "functional": functional, "libraries": libraries, "shaders": shaders, "datasets": [dataset],
              "summary": {mode: byte_summary(tests, mode) for mode in ("raw", "normalized")},
              "by_provenance": {}, "baseline": None, "delta": None, "regressions": []}
    report["summary"]["errors"] = sum(t["status"] == "error" for t in tests)
    for kind in sorted({t["provenance"]["kind"] for t in tests}):
        subset = [t for t in tests if t["provenance"]["kind"] == kind]
        report["by_provenance"][kind] = {mode: byte_summary(subset, mode) for mode in ("raw", "normalized")}
    if args.baseline:
        before = read_json(args.baseline)
        if before["schema_version"] != report["schema_version"]:
            raise ValueError("baseline schema mismatch")
        report["baseline"] = {"commit": before["build"]["commit"], "path": str(args.baseline)}
        report["regressions"] = regressions(before, report)
        report["delta"] = {}
        for mode in ("raw", "normalized"):
            left, right = before["summary"][mode]["match_percentage"], report["summary"][mode]["match_percentage"]
            report["delta"][mode] = {"before": left, "after": right,
                                     "points": right - left if right is not None and left is not None else None}
    if source_fingerprint() != info["source_fingerprint"]:
        raise ValueError("source changed during golden execution; rerun tests")
    # Revalidate binaries too: a concurrent build cannot silently mix versions.
    functional_results(build)
    failed = bool(functional["exit_code"] or report["regressions"] or report["summary"]["errors"] or
                  any(t["critical"] and (t["status"] != "completed" or not t["raw"]["exact"]) for t in tests) or
                  (args.require_originals and dataset["status"] != "available"))
    report["exit_code"] = int(failed)
    write_json(output / "results.json", report)
    render(report, output / "results.html")
    print(json.dumps({"output": str(output), "summary": report["summary"], "regressions": report["regressions"]}, indent=2))
    return int(failed)


def capture(args):
    """Explicit original-execution reference capture; metadata supplies the port argv."""
    meta = read_json(args.metadata)
    command_template = json.loads(args.reference_command)
    if not isinstance(command_template, list) or not command_template or not all(isinstance(s, str) for s in command_template):
        raise ValueError("reference command must be an argv JSON array")
    reference = Path(command_template[0])
    if not reference.is_absolute() or not reference.is_file():
        raise ValueError("reference executable must be an existing absolute path")
    source = args.input.read_bytes()
    with tempfile.TemporaryDirectory(prefix="dl2-reference-") as temporary:
        work = Path(temporary)
        (work / "input.bin").write_bytes(source)
        command = [v.format(input=str(work / "input.bin"), output=str(work / "expected.bin")) for v in command_template]
        subprocess.run(command, cwd=work, check=True, timeout=args.timeout)
        expected = (work / "expected.bin").read_bytes()
        if (work / "input.bin").read_bytes() != source:
            raise ValueError("reference program modified input")
    meta.update(input_sha256=sha256(source), expected_sha256=sha256(expected),
                provenance={"kind": "original-execution", "source": str(reference),
                            "executable_sha256": sha256(reference.read_bytes()),
                            "command": command_template, "captured_at": timestamp()})
    # Validate metadata before publishing.
    with tempfile.TemporaryDirectory(prefix="dl2-golden-check-") as temporary:
        work = Path(temporary)
        (work / "input.bin").write_bytes(source)
        (work / "expected.bin").write_bytes(expected)
        write_json(work / "metadata.json", meta)
        discover(work)
    args.destination.mkdir(parents=True, exist_ok=False)
    (args.destination / "input.bin").write_bytes(source)
    (args.destination / "expected.bin").write_bytes(expected)
    write_json(args.destination / "metadata.json", meta)
    return 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    for name in ("run-tests", "run-byte-matching"):
        command = sub.add_parser(name)
        command.add_argument("--build-dir", type=Path, default=ROOT / "build-verified")
        command.add_argument("--configuration", default="RelWithDebInfo")
        command.add_argument("--data-dir", type=Path, default=Path(os.environ["DL2_DATA"]) if os.environ.get("DL2_DATA") else None)
        if name == "run-byte-matching":
            command.add_argument("--golden-dir", type=Path, default=ROOT / "tests/golden")
            command.add_argument("--output", type=Path, default=ROOT / "results" / ("run-" + timestamp().replace(":", "-")))
            command.add_argument("--baseline", type=Path)
            command.add_argument("--require-originals", action="store_true")
    generate = sub.add_parser("generate-status")
    generate.add_argument("--results", type=Path, required=True)
    capture_parser = sub.add_parser("capture-reference")
    capture_parser.add_argument("--input", type=Path, required=True)
    capture_parser.add_argument("--metadata", type=Path, required=True)
    capture_parser.add_argument("--reference-command", required=True, help='JSON argv; use {input} and {output}')
    capture_parser.add_argument("--destination", type=Path, required=True)
    capture_parser.add_argument("--timeout", type=int, default=30)
    args = parser.parse_args(argv)
    if args.command == "run-tests":
        return run_tests(args)
    if args.command == "run-byte-matching":
        return run_bytes(args)
    if args.command == "capture-reference":
        return capture(args)
    report = read_json(args.results)
    render(report, args.results.with_suffix(".html"))
    print(args.results.with_suffix(".html"))
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except (OSError, ValueError, KeyError, subprocess.SubprocessError, ET.ParseError) as error:
        print(f"ERROR: {error}", file=sys.stderr)
        sys.exit(2)
