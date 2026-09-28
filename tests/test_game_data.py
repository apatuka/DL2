"""Read-only checks against the user's original installation; never regenerate assets."""
import argparse
import contextlib
import io
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))


def check_saves(data_dir):
    import savparse

    savparse.CHECK = True
    items = [("TUTORIAL.SAV", (data_dir / "TUTORIAL.SAV").read_bytes())]
    for relative in ("Saves/AUTOSAVE.SAV", "Campaign/AUTOSAVE.CPN", "Campaign/ChCht001.CPN"):
        path = data_dir / relative
        if path.is_file():
            items.append((relative, path.read_bytes()))
    items.extend(savparse.read_hdx(str(data_dir / "LEVELS")))
    failures = 0
    for name, data in items:
        report = io.StringIO()
        try:
            with contextlib.redirect_stdout(report):
                state = savparse.parse_save(data, name)
                bad = savparse.summarize(name, state)
            if bad:
                failures += 1
                print(report.getvalue())
        except Exception as error:
            failures += 1
            print(f"FAIL {name}: {error}")
    print(f"SAV parser: {len(items) - failures}/{len(items)} files passed cross-reference checks.")
    return int(failures != 0)


def check_tables(data_dir):
    try:
        import extract_tables
    except ModuleNotFoundError as error:
        if error.name != "pefile":
            raise
        print("SKIP: pefile is needed to verify tables against DEADLOCK.EXE.")
        return 77

    exe = extract_tables.Exe(str(data_dir / "DEADLOCK.EXE"))
    try:
        tables = extract_tables.extract(exe)
    finally:
        exe.pe.close()
    if not extract_tables.validate(tables):
        return 1
    saved = json.loads((ROOT / "data/tables.json").read_text(encoding="utf-8"))
    failures = []
    if tables != saved["tables"]:
        failures.append("data/tables.json differs from the executable extraction")
    # Generate in memory only. Differences fail the test instead of overwriting the port.
    for path, expected in (
        ("src/game/data_tables.h", extract_tables.gen_header(tables)),
        ("src/game/data_tables.cpp", extract_tables.gen_cpp(tables)),
    ):
        if (ROOT / path).read_text(encoding="utf-8") != expected:
            failures.append(f"{path} differs from the executable extraction")
    for failure in failures:
        print(f"FAIL: {failure}")
    print(f"Static tables: {len(tables)} groups checked; {len(failures)} mismatches.")
    return int(bool(failures))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("mode", choices=("saves", "tables"))
    parser.add_argument("data_dir")
    args = parser.parse_args()
    data_dir = Path(args.data_dir)
    required = ("TUTORIAL.SAV", "LEVELS.HDX", "LEVELS.HDD") if args.mode == "saves" else ("DEADLOCK.EXE",)
    if not args.data_dir or any(not (data_dir / name).is_file() for name in required):
        print("SKIP: original game files are unavailable; set DL2_DATA_DIR when configuring CMake.")
        return 77
    try:
        return check_saves(data_dir) if args.mode == "saves" else check_tables(data_dir)
    except Exception as error:
        print(f"FAIL: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
