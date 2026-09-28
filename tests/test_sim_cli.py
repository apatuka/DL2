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
    economy = run("economy", tutorial)
    assert economy == run("economy", tutorial), "economic queries must be deterministic"
    assert economy["read_only"] and not economy["complete_turn"] and economy["stage"] == "prepared"
    assert economy["snapshot"] == "as_saved" and not economy["applies_production"]
    assert economy["empty_task_slots"] == "normalized_zero"
    assert economy["turn"] == prepared["turn"]
    assert len(economy["needs"]) == len(economy["production"]) == prepared["territories"]
    assert sum(len(t["buildings"]) for t in economy["production"]) == prepared["buildings"]
    for territory in economy["production"]:
        for building in territory["buildings"]:
            assert len(building["assigned"]) == len(building["maximum"]) == 5
            if building["evaluated"]:
                for slot in building["assigned"]:
                    if slot["task"] == 0:
                        assert slot["output"] == slot["labor"] == 0, "empty-slot safety normalization"
    energy = run("energy", tutorial)
    assert energy == run("energy", tutorial), "isolated energy must be deterministic"
    assert energy["isolated"] and not energy["complete_turn"]
    assert energy["stage"] == "energy_applied_in_memory"
    assert energy["turn_before"] == energy["turn_after"] == prepared["turn"]
    assert len(energy["territories"]) == prepared["territories"]
    for need, effect in zip(economy["needs"], energy["territories"]):
        assert need["territory"] == effect["territory"] and need["energy"] == effect["need"]
        assert effect["after"] == effect["before"] - effect["consumed"]
    assert economy == run("economy", tutorial), "experiments must not overwrite the source"
    labor = run("labor", tutorial)
    assert labor == run("labor", tutorial), "task/labor normalization must be deterministic"
    assert labor["stage"] == "labor_balanced_in_memory" and labor["isolated"]
    assert not labor["complete_turn"] and not labor["complete_load"] and not labor["applies_production"]
    assert labor["turn_before"] == labor["turn_after"] == prepared["turn"]
    assert len(labor["buildings"]) == prepared["buildings"]
    assert len(labor["territories"]) == prepared["territories"]
    for building in labor["buildings"]:
        for snapshot in (building["before"], building["after"]):
            assert len(snapshot["tasks"]) == len(snapshot["labor"]) == 5
    for territory in labor["territories"]:
        before, after = territory["materials_before"], territory["materials_after"]
        assert len(before) == len(after) == 11 and before[0] == after[0]
        assert after[1:] == [min(value, 10000) for value in before[1:]]
        assert territory["assigned_labor"] + territory["unassigned_labor"] == territory["labor_pool"]
    assert economy == run("economy", tutorial), "normalization must not modify the archived input"
    assert "Full turn unavailable" in run("turn", tutorial, success=False).stderr
    with tempfile.TemporaryDirectory(prefix="sim-cli-", dir=output) as temporary:
        folder = Path(temporary)
        copy = folder / "prepared.sav"
        assert run("roundtrip", tutorial, copy)["stage"] == "prepared"
        assert copy.read_bytes() == original
        run("roundtrip", tutorial, copy, success=False)
        assert copy.read_bytes() == original
        run("prepare", folder / "missing.sav", success=False)
        for command in ("economy", "energy", "labor"):
            assert not run(command, folder / "missing.sav", success=False).stdout
            partial = folder / "forbidden-partial.sav"
            rejected = subprocess.run([str(binary), command, str(tutorial), str(partial)],
                                      capture_output=True, text=True)
            assert rejected.returncode == 2 and not partial.exists(), "experiments must not accept a save destination"
        assert not list(folder.glob("*.dl2tmp-*"))
    if (data / "LEVELS.HDX").is_file() and (data / "LEVELS.HDD").is_file():
        assert run("prepare-archive", data / "LEVELS", "CHCHT1")["stage"] == "prepared"
        assert not run("taxes-archive", data / "LEVELS", "CHCHT1")["complete_turn"]
        assert run("economy-archive", data / "LEVELS", "CHCHT1")["read_only"]
        assert run("energy-archive", data / "LEVELS", "CHCHT1")["isolated"]
        assert run("labor-archive", data / "LEVELS", "CHCHT1")["isolated"]
        run("prepare-archive", data / "LEVELS", "MISSING", success=False)
    assert hashlib.sha256(tutorial.read_bytes()).digest() == hashlib.sha256(original).digest()
    print("simulation CLI: exact preparation, production/needs, isolated taxes/energy/labor, non-turn rejection and safe copies passed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
