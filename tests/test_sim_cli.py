"""CLI contract checks; original inputs are read-only, outputs test-owned."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile


def main():
    binary, data, output = Path(sys.argv[1]), Path(sys.argv[2]), Path(sys.argv[3])
    tutorial = data / "TUTORIAL.SAV"
    if not tutorial.is_file():
        print("SKIP: TUTORIAL.SAV unavailable")
        return 77
    original = tutorial.read_bytes()

    def run(*args, success=True):
        result = subprocess.run([str(binary), *map(str, args)], capture_output=True, text=True)
        assert result.returncode == (0 if success else 1), (args, result.returncode, result.stderr)
        return json.loads(result.stdout) if success else result

    prepared = run("prepare", tutorial)
    assert prepared["stage"] == "prepared" and not prepared["complete_turn"]
    assert prepared["territories"] == 36 and prepared["armies"] > 0
    taxes = run("taxes", tutorial)
    assert taxes == run("taxes", tutorial), "independent preparations must be deterministic"
    assert taxes["stage"] == "taxes_applied_in_memory" and not taxes["complete_turn"]
    assert taxes["turn_before"] == taxes["turn_after"] == prepared["turn"]
    assert taxes["players"][0] == {"player": 0, "before": 500, "collected": 20, "after": 520}
    assert taxes["players"][1] == {"player": 1, "before": 500, "collected": 32, "after": 532}
    assert "Full turn unavailable" in run("turn", tutorial, success=False).stderr
    with tempfile.TemporaryDirectory(prefix="sim-cli-", dir=output) as temporary:
        folder = Path(temporary)
        copy = folder / "prepared.sav"
        assert run("roundtrip", tutorial, copy)["stage"] == "prepared"
        assert copy.read_bytes() == original
        run("roundtrip", tutorial, copy, success=False)
        assert copy.read_bytes() == original
        run("prepare", folder / "missing.sav", success=False)
        assert not list(folder.glob("*.dl2tmp-*"))
    if (data / "LEVELS.HDX").is_file() and (data / "LEVELS.HDD").is_file():
        assert run("prepare-archive", data / "LEVELS", "CHCHT1")["stage"] == "prepared"
        assert not run("taxes-archive", data / "LEVELS", "CHCHT1")["complete_turn"]
        run("prepare-archive", data / "LEVELS", "MISSING", success=False)
    assert hashlib.sha256(tutorial.read_bytes()).digest() == hashlib.sha256(original).digest()
    print("simulation CLI: exact preparation, deterministic taxes, non-turn rejection and safe copies passed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
