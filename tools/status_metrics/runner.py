"""Golden execution and catalog collection; never manufactures a reference from the port."""
import json
import re
import subprocess
import tempfile
from datetime import datetime, timezone
from pathlib import Path

from .core import compare, percentage, sha256

ROOT = Path(__file__).resolve().parents[2]


def read_json(path):
    return json.loads(Path(path).read_text(encoding="utf-8-sig"))


def write_json(path, value):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")


def canonical_hash(value):
    return sha256(json.dumps(value, sort_keys=True, separators=(",", ":")).encode())


def text_hash(path):
    return sha256(Path(path).read_text(encoding="utf-8-sig").replace("\r\n", "\n").encode())


def source_fingerprint(root=ROOT):
    paths = [root / "CMakeLists.txt"]
    for directory in ("src", "tests", "tools", "metrics"):
        paths.extend(p for p in (root / directory).rglob("*") if p.is_file()
                     and p.suffix in {".c", ".cpp", ".h", ".hpp", ".cmake", ".py", ".txt", ".json", ".html", ".js", ".css"}
                     and "local" not in p.relative_to(root / directory).parts)
    return canonical_hash({p.relative_to(root).as_posix(): text_hash(p) for p in sorted(set(paths))})


def build_info():
    def git(*args):
        result = subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True, check=True)
        return result.stdout.strip()
    return {"commit": git("rev-parse", "HEAD"), "dirty": bool(git("status", "--porcelain")),
            "source_fingerprint": source_fingerprint()}


def timestamp():
    return datetime.now(timezone.utc).isoformat()


def inside(root, name):
    path = (root / name).resolve()
    if not path.is_relative_to(root.resolve()):
        raise ValueError(f"path escapes directory: {name}")
    return path


def discover(directory):
    cases = []
    ids = set()
    for path in sorted(Path(directory).rglob("metadata.json")):
        meta = read_json(path)
        for key in ("id", "module", "function", "description", "version", "provenance", "command"):
            if key not in meta or not meta[key]:
                raise ValueError(f"{path}: missing {key}")
        if not re.fullmatch(r"[A-Za-z0-9_.-]+", meta["id"]) or meta["id"] in ids:
            raise ValueError(f"invalid or duplicate test id: {meta['id']}")
        ids.add(meta["id"])
        provenance = meta["provenance"]
        if provenance.get("kind") not in {"original-execution", "original-artifact", "derived-oracle"}:
            raise ValueError(f"{path}: unknown reference provenance")
        if not provenance.get("source"):
            raise ValueError(f"{path}: missing reference source")
        if not isinstance(meta["command"], list) or not all(isinstance(v, str) for v in meta["command"]):
            raise ValueError(f"{path}: command must be a nonempty argv list")
        if type(meta.get("critical", True)) is not bool:
            raise ValueError(f"{path}: critical must be a boolean")
        timeout = meta.get("timeout", 30)
        if type(timeout) not in (int, float) or not 0 < timeout <= 3600:
            raise ValueError(f"{path}: timeout must be positive and at most 3600 seconds")
        for name in ("input.bin", "expected.bin"):
            data = inside(path.parent, name).read_bytes()
            if meta.get(name.replace(".bin", "_sha256")) != sha256(data):
                raise ValueError(f"{path}: {name} hash missing or changed")
        # Validate the declared rules even before an implementation is available.
        expected = (path.parent / "expected.bin").read_bytes()
        compare(expected, expected, meta.get("normalization"))
        cases.append((path.parent, meta))
    if not cases:
        raise ValueError("no golden tests discovered")
    return cases


def write_diff(path, test_id, expected, actual, result, rules=None):
    ignored = set()
    for rule in (rules or {}).get("ignore", []):
        ignored.update(range(rule["offset"], rule["offset"] + rule["length"]))
    with path.open("w", encoding="utf-8") as output:
        output.write(f"TEST: {test_id}\nExpected size: {len(expected)}\nActual size: {len(actual)}\n")
        output.write(f"Matching bytes: {result['matching_bytes']}\nDifferent bytes: {result['different_bytes']}\n")
        output.write(f"Match: {result['match_percentage']}%\nOffset       Expected  Actual\n")
        for offset in range(max(len(expected), len(actual))):
            if offset in ignored:
                continue
            left = expected[offset] if offset < len(expected) else None
            right = actual[offset] if offset < len(actual) else None
            if left != right:
                a = f"{left:02X}" if left is not None else "--"
                b = f"{right:02X}" if right is not None else "--"
                output.write(f"0x{offset:08X}   {a}        {b}\n")


def execute_case(directory, meta, output, bindings, build):
    test_id = meta["id"]
    artifact_dir = output / "artifacts" / test_id
    artifact_dir.mkdir(parents=True, exist_ok=True)
    expected = (directory / "expected.bin").read_bytes()
    input_bytes = (directory / "input.bin").read_bytes()
    for name, data in (("input.bin", input_bytes), ("expected.bin", expected)):
        (artifact_dir / name).write_bytes(data)
    record = {"test_id": test_id, "module": meta["module"], "function": meta["function"],
              "description": meta["description"], "version": meta["version"], "build": build,
              "timestamp": timestamp(), "critical": meta.get("critical", True),
              "provenance": meta["provenance"], "normalization": meta.get("normalization", {}),
              "contract_hash": canonical_hash(meta), "input_hash": sha256(input_bytes),
              "input": f"artifacts/{test_id}/input.bin", "expected_output": f"artifacts/{test_id}/expected.bin",
              "actual_output": None, "expected_hash": sha256(expected), "actual_hash": None,
              "status": "error", "raw": None, "normalized": None}
    write_json(artifact_dir / "metadata.json", meta)
    try:
        if sha256(input_bytes) != meta["input_sha256"] or sha256(expected) != meta["expected_sha256"]:
            raise ValueError("golden bytes changed after discovery")
        with tempfile.TemporaryDirectory(prefix="golden-") as temporary:
            work = Path(temporary)
            input_path, actual_path = work / "input.bin", work / "actual.bin"
            input_path.write_bytes(input_bytes)
            values = dict(bindings, input=str(input_path), output=str(actual_path))
            command = [arg.format_map(values) for arg in meta["command"]]
            executable = Path(command[0])
            if not executable.is_file():
                raise FileNotFoundError(f"implementation executable unavailable: {executable}")
            record["executable_sha256"] = sha256(executable.read_bytes())
            record["command"] = command
            process = subprocess.run(command, cwd=work, capture_output=True, timeout=meta.get("timeout", 30))
            (artifact_dir / "stdout.txt").write_bytes(process.stdout)
            (artifact_dir / "stderr.txt").write_bytes(process.stderr)
            record["exit_code"] = process.returncode
            if process.returncode != 0:
                raise ValueError(f"implementation exited {process.returncode}; see stderr.txt")
            if input_path.read_bytes() != input_bytes:
                raise ValueError("implementation modified its input")
            actual = actual_path.read_bytes()
        (artifact_dir / "actual.bin").write_bytes(actual)
        record.update(actual_output=f"artifacts/{test_id}/actual.bin", actual_hash=sha256(actual), status="completed")
        record["raw"] = compare(expected, actual)
        for mode in ("raw", "normalized"):
            # Keep the raw result/diff if normalization rejects a truncated buffer.
            if mode == "normalized":
                record[mode] = compare(expected, actual, meta.get("normalization"))
            if not record[mode]["exact"]:
                diff = output / "mismatches" / f"{test_id}{'.normalized' if mode == 'normalized' else ''}.diff"
                diff.parent.mkdir(exist_ok=True)
                write_diff(diff, test_id, expected, actual, record[mode],
                           meta.get("normalization") if mode == "normalized" else None)
                record[mode]["diff"] = diff.relative_to(output).as_posix()
    except (OSError, ValueError, KeyError, subprocess.SubprocessError) as error:
        record.update(status="error", error=str(error))
    return record


def catalog(root=ROOT):
    functions = {}
    for line in (root / "re/functions.jsonl").read_text(encoding="utf-8").splitlines():
        row = json.loads(line)
        address = row["addr"].lower()
        if address in functions:
            raise ValueError(f"duplicate original function: {address}")
        functions[address] = {"id": address, "name": row["name"], "group": "unclassified"}
    if not functions:
        raise ValueError("original function catalog is empty")
    for path in sorted((root / "re/modules").glob("*.txt")):
        if path.stem == "gp_globals":
            continue
        for line in path.read_text(encoding="utf-8").splitlines():
            match = re.match(r"^([0-9a-fA-F]{8})\s+\d+\s", line)
            if not match:
                continue
            address = match[1].lower()
            if address not in functions:
                raise ValueError(f"module references unknown original function: {address}")
            if functions[address]["group"] != "unclassified":
                raise ValueError(f"original function belongs to multiple modules: {address}")
            functions[address]["group"] = path.stem
    return functions


def coverage(items, evidence, tests, functional, root=ROOT):
    passing = {t["test_id"] for t in tests if t["status"] == "completed" and
               t["raw"]["exact"] and t["raw"]["total_bytes"] > 0}
    verified, reasons, seen = [], {}, set()
    for entry in evidence:
        identity = entry["id"]
        if identity not in items or identity in seen:
            raise ValueError(f"unknown/duplicate evidence id: {identity}")
        seen.add(identity)
        if not entry.get("contract") or not entry.get("golden_tests") or not entry.get("ctest") or not entry.get("files"):
            raise ValueError(f"{identity}: evidence needs contract, files, CTest and golden tests")
        missing = []
        for name, digest in entry["files"].items():
            path = inside(root, name)
            if not path.is_file() or text_hash(path) != digest:
                missing.append(f"source/test requires review: {name}")
        missing.extend(f"golden not exact: {t}" for t in entry["golden_tests"] if t not in passing)
        missing.extend(f"CTest not passed: {t}" for t in entry["ctest"] if functional.get(t) != "passed")
        if missing:
            reasons[identity] = missing
        else:
            verified.append(identity)
    groups = {}
    for identity, item in items.items():
        group = groups.setdefault(item["group"], {"name": item["group"], "total": 0, "implemented": 0})
        group["total"] += 1
        group["implemented"] += identity in verified
    for group in groups.values():
        group.update(pending=group["total"] - group["implemented"],
                     percentage=percentage(group["implemented"], group["total"]))
    return {"total": len(items), "implemented": len(verified), "pending": len(items) - len(verified),
            "percentage": percentage(len(verified), len(items)), "groups": sorted(groups.values(), key=lambda g: g["name"]),
            "known_ids": sorted(items), "verified_ids": sorted(verified), "unverified_evidence": reasons,
            "items": [dict(item, implemented=identity in verified) for identity, item in sorted(items.items())]}


def collect_coverage(tests, functional, root=ROOT):
    manifest = read_json(root / "metrics/evidence.json")
    libraries = coverage(catalog(root), manifest["libraries"], tests, functional, root)
    shaders_config = read_json(root / "metrics/shaders.json")
    items = {}
    for instruction in shaders_config["instructions"]:
        identity = instruction["id"]
        if identity in items:
            raise ValueError(f"duplicate GPU instruction: {identity}")
        items[identity] = {"id": identity, "name": instruction["name"], "group": instruction["family"]}
    if not shaders_config["applicable"] and (items or manifest["shaders"]):
        raise ValueError("GPU cannot be not-applicable with declared instructions/evidence")
    shaders = coverage(items, manifest["shaders"], tests, functional, root)
    shaders.update(applicable=shaders_config["applicable"], reason=shaders_config["reason"],
                   catalog_source="metrics/shaders.json")
    libraries["catalog_source"] = "re/functions.jsonl + re/modules/*.txt"
    return libraries, shaders
