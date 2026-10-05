"""Behavioral tests for metrics, golden execution, evidence and fail-closed gates."""
import copy
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from types import SimpleNamespace

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from status_metrics.core import byte_summary, compare, percentage, regressions, sha256
from status_metrics.runner import (catalog, coverage, discover, execute_case, text_hash, write_json)
from status_metrics.report import render
from status import capture, parse_junit


class ComparisonTests(unittest.TestCase):
    def test_exact_and_hash(self):
        result = compare(bytes(range(256)), bytes(range(256)))
        self.assertTrue(result["exact"])
        self.assertTrue(result["hash_equal"])
        self.assertEqual(result["matching_bytes"], 256)
        self.assertEqual(result["match_percentage"], 100)
        self.assertEqual(sha256(b"abc"), "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad")

    def test_missing_and_extra_bytes(self):
        for left, right in ((b"abc", b"ax"), (b"ax", b"abc")):
            result = compare(left, right)
            self.assertEqual((result["matching_bytes"], result["different_bytes"], result["total_bytes"]), (1, 2, 3))
            self.assertEqual([d["offset"] for d in result["differences"]], [1, 2])
            self.assertFalse(result["hash_equal"])
        self.assertIsNone(compare(b"abc", b"a")["differences"][0]["actual"])

    def test_empty_and_zero_denominators(self):
        result = compare(b"", b"")
        self.assertTrue(result["exact"])
        self.assertIsNone(result["match_percentage"])
        self.assertEqual(compare(b"", b"a")["match_percentage"], 0)
        self.assertIsNone(percentage(0, 0))
        self.assertAlmostEqual(percentage(1, 3), 100 / 3)
        for values in ((-1, 3), (4, 3), (0, -1)):
            with self.assertRaises(ValueError):
                percentage(*values)

    def test_normalization_is_explicit_and_excludes_denominator(self):
        rule = {"ignore": [{"offset": 1, "length": 2, "reason": "runtime pointer"}]}
        raw, normalized = compare(b"abcd", b"aXYd"), compare(b"abcd", b"aXYd", rule)
        self.assertEqual(raw["match_percentage"], 50)
        self.assertEqual(normalized["matching_bytes"], 2)
        self.assertEqual(normalized["total_bytes"], 2)
        self.assertEqual(normalized["ignored_bytes"], 2)
        self.assertEqual(normalized["match_percentage"], 100)
        self.assertTrue(normalized["hash_equal"])
        self.assertFalse(raw["hash_equal"])

    def test_invalid_rules_never_hide_size_errors(self):
        cases = [
            {"unknown": []}, {"ignore": [{"offset": 0, "length": 1}]},
            {"ignore": [{"offset": -1, "length": 1, "reason": "bad"}]},
            {"ignore": [{"offset": 0, "length": 0, "reason": "bad"}]},
            {"ignore": [{"offset": True, "length": 1, "reason": "bad"}]},
            {"ignore": [{"offset": 0, "length": 1, "reason": " "}]},
            {"ignore": [{"offset": 1, "length": 2, "reason": "missing"}]},
            {"ignore": [{"offset": 0, "length": 1, "reason": "a"},
                        {"offset": 0, "length": 1, "reason": "overlap"}]}]
        for rules in cases:
            with self.subTest(rules=rules), self.assertRaises(ValueError):
                compare(b"abc", b"ab", rules)

    def test_diff_limit_never_limits_count(self):
        result = compare(bytes(1024), bytes([255]) * 1024, diff_limit=4)
        self.assertEqual(len(result["differences"]), 4)
        self.assertEqual(result["different_bytes"], 1024)
        self.assertTrue(result["differences_truncated"])

    def test_weighted_bytes_not_average_of_percentages(self):
        tests = [record("small", b"x", b"y"), record("large", bytes(99), bytes(99))]
        summary = byte_summary(tests, "raw")
        self.assertEqual(summary["test_percentage"], 50)
        self.assertEqual(summary["match_percentage"], 99)
        tests.append(dict(test_id="missing", status="error", raw=None, normalized=None))
        summary = byte_summary(tests, "raw")
        self.assertEqual(summary["total_tests"], 3)
        self.assertEqual(summary["compared_tests"], 2)
        self.assertAlmostEqual(summary["test_percentage"], 100/3)


def record(test_id, expected=b"abc", actual=b"abc"):
    return {"test_id": test_id, "status": "completed", "contract_hash": "contract",
            "raw": compare(expected, actual), "normalized": compare(expected, actual)}


def report(tests):
    return {"tests": tests, "summary": {mode: byte_summary(tests, mode) for mode in ("raw", "normalized")},
            "libraries": {"known_ids": ["a"], "verified_ids": ["a"]},
            "shaders": {"known_ids": ["VOP1:x"], "verified_ids": ["VOP1:x"]},
            "functional": {"tests": {"function": "passed"}}}


class RegressionTests(unittest.TestCase):
    def test_identical_and_improvement(self):
        before = report([record("a", b"abc", b"axc")])
        self.assertEqual(regressions(before, copy.deepcopy(before)), [])
        self.assertEqual(regressions(before, report([record("a")])), [])

    def test_individual_regression_despite_global_improvement(self):
        before = report([record("a"), record("b", bytes(100), bytes([1])*100)])
        after = report([record("a", b"abc", b"xbc"), record("b", bytes(100), bytes(100))])
        self.assertIn("raw byte regression: a", regressions(before, after))

    def test_deleted_skipped_and_reference_changed(self):
        before = report([record("a")])
        self.assertIn("removed test: a", regressions(before, report([])))
        for field, value in (("status", "skipped"), ("contract_hash", "new-reference")):
            after = copy.deepcopy(before)
            after["tests"][0][field] = value
            self.assertTrue(regressions(before, after))

    def test_removed_support_and_catalog(self):
        before = report([record("a")])
        for category in ("libraries", "shaders"):
            for key in ("verified_ids", "known_ids"):
                after = copy.deepcopy(before)
                after[category][key] = []
                self.assertTrue(regressions(before, after))
        after = copy.deepcopy(before)
        after["functional"]["tests"]["function"] = "skipped"
        self.assertIn("lost functional test: function", regressions(before, after))


class GoldenTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.case = self.root / "case"
        self.case.mkdir()
        self.output = self.root / "results"
        self.output.mkdir()
        self.meta = {"id": "case", "module": "test", "function": "probe", "description": "unit test adapter",
                     "version": "1", "provenance": {"kind": "derived-oracle", "source": "unit test"},
                     "command": [sys.executable, "-c", "from pathlib import Path; import sys; Path(sys.argv[1]).write_bytes(b'abc')", "{output}"],
                     "input_sha256": sha256(b"input"), "expected_sha256": sha256(b"abc")}
        (self.case / "input.bin").write_bytes(b"input")
        (self.case / "expected.bin").write_bytes(b"abc")
        write_json(self.case / "metadata.json", self.meta)

    def execute(self):
        return execute_case(self.case, self.meta, self.output, {}, {"commit": "unit"})

    def test_discovery_and_real_execution(self):
        self.assertEqual(len(discover(self.case)), 1)
        result = self.execute()
        self.assertEqual(result["status"], "completed")
        self.assertTrue(result["raw"]["exact"])
        self.assertEqual((self.output / result["actual_output"]).read_bytes(), b"abc")
        self.assertEqual(result["actual_hash"], sha256(b"abc"))

    def test_mismatch_retains_full_offsets(self):
        self.meta["command"][2] = self.meta["command"][2].replace("b'abc'", "b'ax'")
        result = self.execute()
        self.assertFalse(result["raw"]["exact"])
        diff = (self.output / result["raw"]["diff"]).read_text()
        self.assertIn("0x00000001   62        78", diff)
        self.assertIn("0x00000002   63        --", diff)

    def test_nonzero_empty_missing_and_timeout_fail(self):
        for code in ("raise SystemExit(3)", "pass", "import time; time.sleep(1)"):
            self.meta["command"][2] = code
            self.meta["timeout"] = 0.1
            result = self.execute()
            self.assertEqual(result["status"], "error")
            self.assertIsNone(result["actual_output"])
        self.meta["command"][0] = str(self.root / "does-not-exist")
        self.assertEqual(self.execute()["status"], "error")

    def test_normalization_failure_preserves_raw_diff(self):
        self.meta["normalization"] = {"ignore": [{"offset": 2, "length": 1, "reason": "pointer"}]}
        self.meta["command"][2] = self.meta["command"][2].replace("b'abc'", "b'ax'")
        result = self.execute()
        self.assertEqual(result["status"], "error")
        self.assertEqual(result["raw"]["different_bytes"], 2)
        self.assertTrue((self.output / result["raw"]["diff"]).is_file())

    def test_tampered_reference_and_duplicate_id_rejected(self):
        (self.case / "expected.bin").write_bytes(b"xyz")
        with self.assertRaisesRegex(ValueError, "hash"):
            discover(self.case)
        (self.case / "expected.bin").write_bytes(b"abc")
        duplicate = self.case / "duplicate"
        duplicate.mkdir()
        (duplicate / "input.bin").write_bytes(b"input")
        (duplicate / "expected.bin").write_bytes(b"abc")
        write_json(duplicate / "metadata.json", self.meta)
        with self.assertRaisesRegex(ValueError, "duplicate"):
            discover(self.case)

    def test_path_id_rejected(self):
        self.meta["id"] = "../escape"
        write_json(self.case / "metadata.json", self.meta)
        with self.assertRaisesRegex(ValueError, "invalid"):
            discover(self.case)

    def test_capture_records_executable_and_reference_hashes(self):
        destination = self.root / "captured"
        args = SimpleNamespace(input=self.case / "input.bin", metadata=self.case / "metadata.json",
                               reference_command=json.dumps(self.meta["command"]), timeout=10,
                               destination=destination)
        self.assertEqual(capture(args), 0)
        captured = discover(destination)[0][1]
        self.assertEqual(captured["provenance"]["kind"], "original-execution")
        self.assertEqual(captured["provenance"]["executable_sha256"], sha256(Path(sys.executable).read_bytes()))
        self.assertEqual((destination / "expected.bin").read_bytes(), b"abc")
        self.assertEqual((destination / "input.bin").read_bytes(), b"input")
        with self.assertRaises(FileExistsError):
            capture(args)

    def test_failed_capture_does_not_publish(self):
        destination = self.root / "failed-capture"
        args = SimpleNamespace(input=self.case / "input.bin", metadata=self.case / "metadata.json",
                               reference_command=json.dumps([sys.executable, "-c", "raise SystemExit(4)"]),
                               timeout=10, destination=destination)
        with self.assertRaises(subprocess.CalledProcessError):
            capture(args)
        self.assertFalse(destination.exists())

    def test_changed_after_discovery_is_an_error(self):
        discover(self.case)
        (self.case / "expected.bin").write_bytes(b"xyz")
        result = self.execute()
        self.assertEqual(result["status"], "error")
        self.assertIn("changed after discovery", result["error"])


class EvidenceTests(unittest.TestCase):
    def test_real_catalog_and_golden_fixtures(self):
        items = catalog()
        lines = (ROOT / "re/functions.jsonl").read_text().splitlines()
        self.assertEqual(len(items), len(lines))
        self.assertIn("004ae5b0", items)
        self.assertTrue({"rng-rand15", "rng-long31", "rng-secondary15"}.issubset(
            {meta["id"] for _, meta in discover(ROOT / "tests/golden")}))

    def test_enum_stub_and_passing_unrelated_test_are_not_evidence(self):
        items = {"x": {"id": "x", "name": "x", "group": "GPU"}}
        result = coverage(items, [], [record("unrelated")], {"unrelated": "passed"})
        self.assertEqual(result["implemented"], 0)
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / "code.cpp").write_text("real implementation")
            entry = {"id": "x", "contract": "reviewed semantics", "ctest": ["behavior"],
                     "golden_tests": ["golden"], "files": {"code.cpp": text_hash(root / "code.cpp")}}
            self.assertEqual(coverage(items, [entry], [record("golden")], {"behavior": "passed"}, root)["implemented"], 1)
            self.assertEqual(coverage(items, [entry], [record("golden")], {"behavior": "skipped"}, root)["implemented"], 0)
            self.assertEqual(coverage(items, [entry], [record("golden", b"", b"")], {"behavior": "passed"}, root)["implemented"], 0)
            (root / "code.cpp").write_text("return; // stub")
            self.assertEqual(coverage(items, [entry], [record("golden")], {"behavior": "passed"}, root)["implemented"], 0)

    def test_junit_fail_skip_and_html_escaping(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            xml = root / "ctest.xml"
            xml.write_text('<testsuite><testcase name="pass"/><testcase name="fail"><failure/></testcase><testcase name="skip"><skipped/></testcase></testsuite>')
            self.assertEqual(parse_junit(xml), {"pass": "passed", "fail": "failed", "skip": "skipped"})
            destination = root / "result.html"
            render({"malicious": "</script><script>alert(1)</script>"}, destination)
            html = destination.read_text(encoding="utf-8")
            self.assertNotIn('</script><script>alert(1)', html)
            self.assertIn('\\u003c/script\\u003e', html)


if __name__ == "__main__":
    unittest.main()
