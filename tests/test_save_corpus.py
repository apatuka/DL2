"""Cross-check the C++ SAV codec against the original files and Python parser.

The game installation is read-only. Every generated input/output lives in an
automatically removed temporary directory beneath the supplied build directory.
"""
import argparse
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import savparse


def require(condition, message):
    if not condition:
        raise AssertionError(message)


def run_cli(cli, *arguments, succeeds=True):
    result = subprocess.run(
        [str(cli), *(str(value) for value in arguments)],
        capture_output=True, text=True, encoding="utf-8", errors="replace",
        timeout=15, check=False,
    )
    command = " ".join(str(value) for value in arguments)
    if succeeds:
        require(result.returncode == 0,
                f"{command}: exit {result.returncode}\n{result.stdout}{result.stderr}")
    else:
        require(result.returncode != 0, f"{command}: invalid operation was accepted")
    return result


def expected_summary(state):
    options = state["options"]
    world = state["world"]
    return {
        "version": state["header"]["version"],
        "is_map": False,
        "turn": options["turn"],
        "players": options["numPlayers"],
        "local_player": options["localPlayer"],
        "width": world["width"],
        "height": world["height"],
        "territories": len(state["territories"]),
        "buildings": len(state["buildings"]),
        "armies": len(state["armies"]),
        "events": len(state["events"]),
        "local_values": len(state["localList"]),
        "minister_nodes": [len(nodes) for nodes in state["ministerJobs"]],
        "queue_records": sum(len(queue) for territory in state["territories"]
                             for queue in territory["queues"]),
        "trailing_bytes": state["trailing"],
        "credits": [player["credits"] for player in state["players"]],
    }


def check_summary(result, label, expected):
    actual = json.loads(result.stdout)
    require(isinstance(actual, dict), f"{label}: inspect must produce a JSON object")
    for key, value in expected.items():
        require(key in actual, f"{label}: inspect omitted {key}")
        require(actual[key] == value,
                f"{label}: {key}: C++={actual[key]!r}, Python={value!r}")


def inspect(cli, path, expected):
    check_summary(run_cli(cli, "inspect", path), path.name, expected)


def require_no_staged_files(directory):
    staged = list(directory.rglob("*.dl2tmp-*"))
    require(not staged, f"Temporary publication files were not cleaned up: {staged}")


def check_one(cli, directory, ordinal, name, original):
    state = savparse.parse_save(original, name)
    require(state["header"]["gen"] == 4 and not state["header"]["is_map"],
            f"{name}: corpus includes a format outside this test's scope")
    cross_refs = savparse.deep_check(state)
    building_ids = {building["id"] for building in state["buildings"]}
    for building in state["buildings"]:
        require(all(building[field] == 0 or building[field] in building_ids
                    for field in ("prev", "next")),
                f"{name}: invalid building list ID in Python reference parser")
    for field in ("sites", "blds", "tiles", "tlist", "adj", "armies", "alists"):
        require(cross_refs[field] == cross_refs[field + "_ok"],
                f"{name}: Python reference check failed: {field}")

    # Archive entry names are never used as paths; untrusted names cannot escape.
    source = directory / f"{ordinal:02d}-input.sav"
    roundtrip = directory / f"{ordinal:02d}-roundtrip.sav"
    edited = directory / f"{ordinal:02d}-edited.sav"
    source.write_bytes(original)
    summary = expected_summary(state)
    inspect(cli, source, summary)

    run_cli(cli, "roundtrip", source, roundtrip)
    require(roundtrip.read_bytes() == original, f"{name}: roundtrip changed file bytes")

    player = state["options"]["localPlayer"]
    require(0 <= player < 7, f"{name}: invalid local player in reference input")
    old_credits = state["players"][player]["credits"]
    new_credits = old_credits + (1 if old_credits < 0x7fffffff else -1)
    run_cli(cli, "set-credits", source, edited, player, new_credits)
    expected_bytes = bytearray(original)
    credit_offset = (savparse.SZ_HEADER + savparse.SZ_OPTIONS + savparse.SZ_WORLD
                     + player * savparse.SZ_PLAYER + 0x0c)
    struct.pack_into("<i", expected_bytes, credit_offset, new_credits)
    edited_bytes = edited.read_bytes()
    require(edited_bytes == expected_bytes,
            f"{name}: credit edit changed bytes outside the selected four-byte field")
    edited_state = savparse.parse_save(edited_bytes, name + " (edited)")
    require(edited_state["players"][player]["credits"] == new_credits,
            f"{name}: Python did not read the edited credits")
    summary["credits"][player] = new_credits
    inspect(cli, edited, summary)

    if ordinal == 0:
        # Both writing commands must reject existing destinations, even the input.
        run_cli(cli, "roundtrip", source, roundtrip, succeeds=False)
        run_cli(cli, "set-credits", source, edited, player, old_credits, succeeds=False)
        run_cli(cli, "roundtrip", source, source, succeeds=False)
        require(roundtrip.read_bytes() == original, "Existing roundtrip was overwritten")
        require(edited.read_bytes() == expected_bytes, "Existing edited file was overwritten")
        require_no_staged_files(directory)
    require(source.read_bytes() == original, f"{name}: command modified its input")


def check_bad_inputs(cli, directory, valid):
    variants = {"empty": b"", "short-header": valid[:savparse.SZ_HEADER - 1]}
    wrong_magic = bytearray(valid)
    wrong_magic[0] ^= 0xff
    variants["wrong-magic"] = wrong_magic
    future_version = bytearray(valid)
    struct.pack_into("<I", future_version, 0x58, savparse.CURRENT_VERSION + 1)
    variants["future-version"] = future_version
    # Truncate within the fixed Player[7] block, not ignorable trailing bytes.
    variants["short-player"] = valid[:savparse.SZ_HEADER + savparse.SZ_OPTIONS
                                     + savparse.SZ_WORLD + 5]
    for name, data in variants.items():
        source = directory / f"invalid-{name}.sav"
        destination = directory / f"invalid-{name}-output.sav"
        source.write_bytes(data)
        run_cli(cli, "inspect", source, succeeds=False)
        run_cli(cli, "roundtrip", source, destination, succeeds=False)
        require(not destination.exists(), f"{name}: failure left an output file")
    require_no_staged_files(directory)
    return len(variants)


def check_archive(cli, directory, base, entries):
    for name, data in entries:
        expected = expected_summary(savparse.parse_save(data, name))
        check_summary(run_cli(cli, "inspect-archive", base, name), name, expected)

    # CHCHT1 carries a substantial trailing block: extraction must preserve it.
    chcht1 = next(((name, data) for name, data in entries if name == "CHCHT1"), None)
    require(chcht1 is not None, "Expected CHCHT1 scenario not found in LEVELS")
    require(savparse.parse_save(chcht1[1], chcht1[0])["trailing"] > 0,
            "CHCHT1 no longer exercises trailing-byte preservation")
    second = next(((name, data) for name, data in entries if name != "CHCHT1"), None)
    require(second is not None, "Need a second archive scenario to test extraction")
    for ordinal, (name, expected_bytes) in enumerate((chcht1, second)):
        destination = directory / f"archive-extracted-{ordinal}.sav"
        run_cli(cli, "extract-save", base, name, destination)
        require(destination.read_bytes() == expected_bytes,
                f"{name}: archive extraction changed file bytes")
        inspect(cli, destination, expected_summary(savparse.parse_save(expected_bytes, name)))
        run_cli(cli, "extract-save", base, name, destination, succeeds=False)
        require(destination.read_bytes() == expected_bytes,
                f"{name}: archive extraction overwrote an existing destination")
        require_no_staged_files(directory)
    return 2


def check_bad_archives(cli, directory):
    name = b"TEST\0\0\0\0"
    valid_index = struct.pack("<I8sI", 1, name, 0)
    variants = {
        "huge-count": (struct.pack("<I", 0xffffffff), struct.pack("<I", 0)),
        "invalid-offset": (struct.pack("<I8sI", 1, name, 0xfffffff0), struct.pack("<I", 0)),
        "entry-too-long": (valid_index, struct.pack("<I", 4096) + bytes(16)),
    }
    for label, (index, data) in variants.items():
        base = directory / f"invalid-archive-{label}"
        Path(str(base) + ".HDX").write_bytes(index)
        Path(str(base) + ".HDD").write_bytes(data)
        destination = directory / f"invalid-archive-{label}-output.sav"
        run_cli(cli, "inspect-archive", base, "TEST", succeeds=False)
        run_cli(cli, "extract-save", base, "TEST", destination, succeeds=False)
        require(not destination.exists(), f"{label}: malformed archive left an output file")
        require_no_staged_files(directory)
    return len(variants)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("cli", type=Path)
    parser.add_argument("data_dir")
    parser.add_argument("output_dir", type=Path)
    args = parser.parse_args()
    data_dir = Path(args.data_dir)
    required = ("TUTORIAL.SAV", "LEVELS.HDX", "LEVELS.HDD")
    if not args.data_dir or any(not (data_dir / name).is_file() for name in required):
        print("SKIP: original saves unavailable; configure DL2_DATA_DIR.")
        return 77
    require(args.cli.is_file(), f"C++ save tool not found: {args.cli}")
    require(args.output_dir.is_dir(), f"Build output directory missing: {args.output_dir}")
    items = [("TUTORIAL.SAV", (data_dir / "TUTORIAL.SAV").read_bytes())]
    for relative in ("Saves/AUTOSAVE.SAV", "Campaign/AUTOSAVE.CPN", "Campaign/ChCht001.CPN"):
        path = data_dir / relative
        if path.is_file():
            items.append((relative, path.read_bytes()))
    archive = list(savparse.read_hdx(str(data_dir / "LEVELS")))
    require(bool(archive), "LEVELS archive contains no scenarios")
    items.extend(archive)
    with tempfile.TemporaryDirectory(prefix="save-corpus-", dir=args.output_dir) as temporary:
        directory = Path(temporary)
        for ordinal, (name, data) in enumerate(items):
            try:
                check_one(args.cli, directory, ordinal, name, data)
            except Exception as error:
                raise AssertionError(f"{name}: {error}") from error
        bad_count = check_bad_inputs(args.cli, directory, items[0][1])
        extracted = check_archive(args.cli, directory, data_dir / "LEVELS", archive)
        bad_archives = check_bad_archives(args.cli, directory)
        require_no_staged_files(directory)
    print(f"C++ SAV corpus: {len(items)}/{len(items)} inspections, lossless roundtrips "
          f"and isolated credit edits passed ({len(archive)} archive scenarios); "
          f"{len(archive)} direct archive inspections and {extracted} exact extractions passed; "
          f"{bad_count} malformed saves and {bad_archives} malformed archives rejected; "
          "overwrite protection and temporary cleanup passed.")
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except Exception as error:
        print(f"FAIL: {error}", file=sys.stderr)
        sys.exit(1)
