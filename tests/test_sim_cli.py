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
    placement = run("placement", tutorial, 1, 1, 0)
    assert placement == run("placement", tutorial, 1, 1, 0), "placement queries must be deterministic"
    assert placement["read_only"] and placement["stage"] == "prepared"
    assert not placement["complete_turn"] and not placement["complete_build_permission"]
    assert not placement["applies_construction"] and placement["turn"] == prepared["turn"]
    assert placement["territory"] == 1 and placement["building_type"] == 1 and placement["site"] == 0
    assert placement["footprint"] == {"size": 1, "fits": True, "sites": [0]}
    assert placement["placement_allowed"] == (placement["reason"] == 0)
    for site in (-1, 36, 2147483647, -2147483648):
        outside = run("placement", tutorial, 1, 1, site)
        assert outside["reason"] == 1 and not outside["placement_allowed"]
        assert not outside["footprint"]["fits"] and not outside["footprint"]["sites"]
    for args in ((0, 1, 0), (-1, 1, 0), (37, 1, 0), (1, 0, 0), (1, 48, 0),
                 (1, "1junk", 0), (1, 1, "2147483648"), (1, 1, "")):
        assert not run("placement", tutorial, *args, success=False).stdout
    assert "Full turn unavailable" in run("turn", tutorial, success=False).stderr
    assert "Complete load activation unavailable" in run("activate", tutorial, success=False).stderr
    normalized = run("normalize-load", tutorial)
    assert normalized == run("normalize-load", tutorial)
    assert normalized["stage"] == "load_normalized_in_memory"
    assert not normalized["complete_load"] and not normalized["can_play"] and not normalized["complete_turn"]
    assert normalized["turn_before"] == normalized["turn_after"] == prepared["turn"]
    assert all(normalized[k] for k in ("continents_rebuilt", "roads_rebuilt", "shrines_rebuilt", "labor_normalized"))
    assert normalized["territories"] == prepared["territories"] and normalized["buildings"] == prepared["buildings"]
    assert normalized["rng"]["seed_source"] == "options.gameId" and normalized["rng"]["operations"] == 0
    assert normalized["rng"]["rtl_low"] == normalized["rng"]["secondary"] and normalized["rng"]["rtl_high"] == 0
    assert "ai_turn" in normalized["playability_missing"] and not normalized["ai_executable"]
    assert "ai_execution" not in normalized["missing"], "LoadGame does not execute an AI turn"
    assert normalized["ai_initialization_complete"] and "native_presentation" in normalized["missing"]
    assert normalized["ai_data_initialized"] and normalized["visibility_rebuilt"]
    assert normalized["building_intelligence_rebuilt"] and normalized["contact_discovery_skipped_on_load"]
    assert not {"visibility", "contacts", "building_intelligence"} & set(normalized["missing"])
    seeded = run("normalize-load-seeded", tutorial, 123)
    assert seeded == run("normalize-load-seeded", tutorial, 123) and seeded["events_rebuilt"]
    assert seeded["rng"] == normalized["rng"], "pre-event draws cannot leak past final gameplay reseed"
    assert not run("normalize-load-seeded", tutorial, "bad", success=False).stdout
    session = run("normalize-session", tutorial, 123)
    assert session == run("normalize-session", tutorial, 123)
    assert all(session[k] for k in ("startup_rebuilt", "world_presentation_rebuilt", "timer_planned", "ai_initialization_complete"))
    assert session["missing"] == ["native_presentation"] and not session["can_play"]
    assert session["headless_load_complete"] and session["shrine_notices_delivered"]
    assert session["rng"] == normalized["rng"] and session["turn_after"] == prepared["turn"]
    for seed in ("bad", "2147483648", "-2147483649", ""):
        assert not run("normalize-session", tutorial, seed, success=False).stdout
    unit = run("create-unit", tutorial, 14, 0, 1)
    assert unit == run("create-unit", tutorial, 14, 0, 1)
    assert unit["army_count"] == prepared["armies"] + 1 and unit["created_ids"] == [unit["primary_id"]]
    assert unit["counter_after"] == unit["counter_before"] + 1 and not unit["manufacturing_order"]
    assert unit["stage"] == "entities_edited_in_memory" and not unit["complete_turn"]
    # The actual tutorial has one ChCh't colonizer10243 in territory14.
    for command, refunds in (("delete-unit", 0), ("disband-unit", 1)):
        removed = run(command, tutorial, 10243)
        assert removed == run(command, tutorial, 10243)
        assert removed["removed_ids"] == [10243] and removed["army_count"] == prepared["armies"] - 1
        assert removed["refund_count"] == refunds and removed["turn"] == prepared["turn"]
        for bad_id in (0, -1, 65536, "bad"):
            assert not run(command, tutorial, bad_id, success=False).stdout
    for args in ((0, 0, 1), (14, -1, 1), (14, 7, 1), (14, 0, 0), (14, 0, 39), (14, 0, "bad")):
        assert not run("create-unit", tutorial, *args, success=False).stdout
    for command, args, credits in (("delete-building", (10241,), 0), ("demolish-building", (10241, 0), 25)):
        removed = run(command, tutorial, *args)
        assert removed == run(command, tutorial, *args)
        assert removed["building_count"] == prepared["buildings"] - 1 and removed["building_id"] == 10241
        assert removed["refund_credits"] == credits and removed["turn"] == prepared["turn"]
        assert removed["roads_target_was_sentinel"] == (command == "demolish-building")
    assert not run("delete-building", tutorial, 0, success=False).stdout
    assert not run("demolish-building", tutorial, 10241, 7, success=False).stdout
    assert not run("demolish-building", tutorial, 10244, 0, success=False).stdout  # Shrine campaign effects not fabricated.
    order = run("start-building", tutorial, 14, 1, 35, 1)
    assert order == run("start-building", tutorial, 14, 1, 35, 1)
    assert order["accepted"] and order["paid_construction_order"] and not order["complete_turn"]
    assert order["work_remaining"] == 10 and order["credits_before"] == 500 and order["credits_after"] == 450
    assert order["paid"][0] == 50 and order["paid"][3] == 10 and sum(order["paid"]) == 60
    assert order["local_labor_balanced"] and order["site_roads_rebuilt"] and order["logged_events"] == 1
    assert order["rng_operations"] == 1 and order["building_count"] == prepared["buildings"] + 1
    denied = run("start-building", tutorial, 14, 1, 14, 1)
    assert not denied["accepted"] and not denied["payment_evaluated"] and denied["building_count"] == prepared["buildings"]
    assert denied["counter_after"] == denied["counter_before"] + 1 and denied["rng_operations"] == 0
    for args in ((0, 1, 35, 1), (14, 48, 35, 1), (14, 1, 35, "bad")):
        assert not run("start-building", tutorial, *args, success=False).stdout
    site = run("find-site", tutorial, 14, 1, 1)
    assert site == run("find-site", tutorial, 14, 1, 1) and site["read_only"] and site["found"]
    assert not site["applies_construction"] and site["rng_operations"] == 0
    assert run("placement", tutorial, 14, 1, site["site"])["placement_allowed"]
    assert not run("find-site", tutorial, 0, 1, 1, success=False).stdout
    queued = run("queue-unit", tutorial, 14, 1, 1)
    assert queued == run("queue-unit", tutorial, 14, 1, 1)
    assert queued["queued"] and queued["queue"] == 1 and queued["credits_after"] == 465
    assert queued["manufacturing_substep"] and queued["isolated"] and not queued["complete_turn"] and not queued["can_save"]
    assert queued["queue_records"] == [{"unit_type": 1, "work_remaining": 30, "paid": [35] + [0] * 10}]
    assert not queued["created_ids"] and queued["events_dispatched"] == 0 and queued["turn"] == prepared["turn"]
    # All tutorial queues are empty. Separate commands always start from the
    # untouched SAV; their experiments are not secretly persisted between calls.
    dequeued = run("dequeue-unit", tutorial, 14, 1, 0)
    assert not dequeued["removed"] and not dequeued["queue_records"] and dequeued["refund_credits"] == 0
    produced = run("produce-units", tutorial, 14, 1, 30, 1)
    assert produced == run("produce-units", tutorial, 14, 1, 30, 1)
    assert produced["production_supplied"] == produced["production_remaining"] == 30
    assert not produced["created_ids"] and produced["army_count"] == prepared["armies"] and not produced["complete_turn"]
    progressed = run("progress-buildings", tutorial, 14, 1)
    assert progressed == run("progress-buildings", tutorial, 14, 1)
    assert progressed["initial_labor_balanced"] and progressed["isolated"]
    assert not progressed["complete_production_pass"] and not progressed["can_save"] and progressed["turn"] == prepared["turn"]
    for command, bad_args in (
        ("queue-unit", ((0, 1, 1), (14, 0, 1), (14, 39, 1), (14, 1, "bad"))),
        ("dequeue-unit", ((0, 1, 0), (14, 0, 0), (14, 6, 0), (14, 1, -1))),
        ("produce-units", ((0, 1, 30, 1), (14, 6, 30, 1), (14, 1, "2147483648", 1))),
        ("progress-buildings", ((0, 1), (37, 1), (14, "bad"))),
    ):
        for args in bad_args:
            assert not run(command, tutorial, *args, success=False).stdout
    # Territory14 is human-owned; territory1's minister-managed buildings are
    # deliberately outside this completed-building initializer's safe domain.
    created = run("create-building", tutorial, 14, 1, 35)
    assert created == run("create-building", tutorial, 14, 1, 35)
    assert created["stage"] == "entities_edited_in_memory" and not created["complete_turn"]
    assert created["finished_building"] and not created["paid_construction_order"]
    assert created["local_labor_balanced"] and created["site_roads_rebuilt"]
    assert created["building_count"] == prepared["buildings"] + 1 and created["footprint"] == [35]
    assert created["turn"] == prepared["turn"] and created["building_id"] == (created["counter_after"] & 0xffff)
    assert not run("create-building", tutorial, 14, 1, 36, success=False).stdout
    assert not run("create-building", tutorial, 14, 1, -1, success=False).stdout
    assert "minister-managed" in run("create-building", tutorial, 1, 1, 35, success=False).stderr
    with tempfile.TemporaryDirectory(prefix="sim-cli-", dir=output) as temporary:
        folder = Path(temporary)
        copy = folder / "prepared.sav"
        assert run("roundtrip", tutorial, copy)["stage"] == "prepared"
        assert copy.read_bytes() == original
        run("roundtrip", tutorial, copy, success=False)
        assert copy.read_bytes() == original
        run("prepare", folder / "missing.sav", success=False)
        for command in ("economy", "energy", "labor", "normalize-load", "activate"):
            assert not run(command, folder / "missing.sav", success=False).stdout
            partial = folder / "forbidden-partial.sav"
            rejected = subprocess.run([str(binary), command, str(tutorial), str(partial)],
                                      capture_output=True, text=True)
            assert rejected.returncode == 2 and not partial.exists(), "experiments must not accept a save destination"
        assert not list(folder.glob("*.dl2tmp-*"))
        partial = folder / "forbidden-placement.sav"
        rejected = subprocess.run([str(binary), "placement", str(tutorial), "1", "1", "0", str(partial)],
                                  capture_output=True, text=True)
        assert rejected.returncode == 2 and not partial.exists(), "placement cannot accept a save destination"
        for command, args in (("create-building", (1, 1, 35)), ("normalize-load-seeded", (123,)),
                              ("normalize-session", (123,)), ("create-unit", (14, 0, 1)),
                              ("delete-unit", (10243,)), ("disband-unit", (10243,)),
                              ("delete-building", (10241,)), ("demolish-building", (10241, 0)),
                              ("start-building", (14, 1, 35, 1)), ("find-site", (14, 1, 1)),
                              ("queue-unit", (14, 1, 1)), ("dequeue-unit", (14, 1, 0)),
                              ("produce-units", (14, 1, 30, 1)), ("progress-buildings", (14, 1))):
            rejected = subprocess.run([str(binary), command, str(tutorial), *map(str, args), str(partial)],
                                      capture_output=True, text=True)
            assert rejected.returncode == 2 and not partial.exists(), "new experiments cannot accept a save destination"
    if (data / "LEVELS.HDX").is_file() and (data / "LEVELS.HDD").is_file():
        assert run("prepare-archive", data / "LEVELS", "CHCHT1")["stage"] == "prepared"
        assert not run("taxes-archive", data / "LEVELS", "CHCHT1")["complete_turn"]
        assert run("economy-archive", data / "LEVELS", "CHCHT1")["read_only"]
        assert run("energy-archive", data / "LEVELS", "CHCHT1")["isolated"]
        assert run("labor-archive", data / "LEVELS", "CHCHT1")["isolated"]
        assert not run("normalize-load-archive", data / "LEVELS", "CHCHT1")["can_play"]
        migrated = run("normalize-load-archive", data / "LEVELS", "CYTH3")
        assert migrated["source_version"] == 35 and migrated["normalized_version"] == 36
        assert migrated["legacy_jobs_discarded"] and not migrated["can_play"]
        assert run("placement-archive", data / "LEVELS", "CHCHT1", 1, 1, 0)["read_only"]
        run("prepare-archive", data / "LEVELS", "MISSING", success=False)
    assert hashlib.sha256(tutorial.read_bytes()).digest() == hashlib.sha256(original).digest()
    print("simulation CLI: exact preparation, production/needs/placement, isolated taxes/energy/labor, non-turn rejection and safe copies passed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
