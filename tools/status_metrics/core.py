"""Pure comparisons, explicit normalization and regression policy."""
import hashlib
from fractions import Fraction


def percentage(numerator, denominator):
    if not 0 <= numerator <= denominator:
        raise ValueError("invalid metric counts")
    return numerator * 100 / denominator if denominator else None


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def ignore_offsets(rules, expected_size, actual_size):
    if set(rules) - {"ignore"}:
        raise ValueError("unknown normalization rule")
    ignored = set()
    for rule in rules.get("ignore", []):
        if set(rule) != {"offset", "length", "reason"}:
            raise ValueError("ignore requires offset, length and reason")
        start, length = rule["offset"], rule["length"]
        if type(start) is not int or type(length) is not int or start < 0 or length <= 0:
            raise ValueError("normalization ranges must be nonnegative integers with positive length")
        if not isinstance(rule["reason"], str) or not rule["reason"].strip():
            raise ValueError("normalization requires a reason")
        if start + length > min(expected_size, actual_size):
            raise ValueError("normalization cannot hide missing bytes or exceed a buffer")
        offsets = set(range(start, start + length))
        if ignored & offsets:
            raise ValueError("overlapping normalization ranges")
        ignored.update(offsets)
    return ignored


def compare(expected, actual, rules=None, diff_limit=256):
    """Missing/extra bytes differ. Empty denominator is N/A, never 100%."""
    ignored = ignore_offsets(rules or {}, len(expected), len(actual))
    total = max(len(expected), len(actual)) - len(ignored)
    matching = 0
    differences = []
    for offset in range(max(len(expected), len(actual))):
        if offset in ignored:
            continue
        left = expected[offset] if offset < len(expected) else None
        right = actual[offset] if offset < len(actual) else None
        if left == right:
            matching += 1
        elif len(differences) < diff_limit:
            differences.append({"offset": offset, "expected": left, "actual": right})
    left = bytes(b for i, b in enumerate(expected) if i not in ignored) if ignored else expected
    right = bytes(b for i, b in enumerate(actual) if i not in ignored) if ignored else actual
    return {"expected_size": len(expected), "actual_size": len(actual),
            "matching_bytes": matching, "different_bytes": total - matching,
            "total_bytes": total, "ignored_bytes": len(ignored),
            "match_percentage": percentage(matching, total),
            "expected_hash": sha256(left), "actual_hash": sha256(right),
            "hash_equal": sha256(left) == sha256(right), "exact": left == right,
            "differences": differences, "differences_truncated": total - matching > len(differences)}


def byte_summary(tests, mode):
    compared = [t[mode] for t in tests if t.get(mode) is not None]
    total = sum(t["total_bytes"] for t in compared)
    matching = sum(t["matching_bytes"] for t in compared)
    passed = sum(t.get("status") == "completed" and bool((t.get(mode) or {}).get("exact"))
                 for t in tests)
    return {"passed": passed, "total_tests": len(tests),
            "compared_tests": len(compared), "test_percentage": percentage(passed, len(tests)),
            "matching_bytes": matching, "different_bytes": total - matching,
            "total_bytes": total, "match_percentage": percentage(matching, total),
            "ignored_bytes": sum(t["ignored_bytes"] for t in compared)}


def lower(after_num, after_den, before_num, before_den):
    return bool(before_den and (not after_den or
                Fraction(after_num, after_den) < Fraction(before_num, before_den)))


def regressions(before, after):
    """Detect losses even when a test/catalog entry disappears or averages improve."""
    failures = []
    previous = {t["test_id"]: t for t in before["tests"]}
    current = {t["test_id"]: t for t in after["tests"]}
    for test_id, old in previous.items():
        new = current.get(test_id)
        if new is None:
            failures.append(f"removed test: {test_id}")
            continue
        if old.get("contract_hash") != new.get("contract_hash"):
            failures.append(f"changed reference/input/normalization contract: {test_id}")
        if old["status"] == "completed" and new["status"] != "completed":
            failures.append(f"lost execution: {test_id}")
        for mode in ("raw", "normalized"):
            left, right = old.get(mode), new.get(mode)
            if left is None:
                continue
            if right is None or (left["exact"] and not right["exact"]) or lower(
                    right["matching_bytes"], right["total_bytes"],
                    left["matching_bytes"], left["total_bytes"]):
                failures.append(f"{mode} byte regression: {test_id}")
    for mode in ("raw", "normalized"):
        left, right = before["summary"][mode], after["summary"][mode]
        for num, den in (("matching_bytes", "total_bytes"), ("passed", "total_tests")):
            if lower(right[num], right[den], left[num], left[den]):
                failures.append(f"aggregate {mode} regression: {num}/{den}")
    for category in ("libraries", "shaders"):
        left = before.get(category, {})
        right = after.get(category, {})
        for key in ("verified_ids", "known_ids"):
            lost = set(left.get(key, [])) - set(right.get(key, []))
            if lost:
                failures.append(f"{category} lost {key}: {', '.join(sorted(lost))}")
    for name, status in before.get("functional", {}).get("tests", {}).items():
        if status == "passed" and after.get("functional", {}).get("tests", {}).get(name) != "passed":
            failures.append(f"lost functional test: {name}")
    return failures
