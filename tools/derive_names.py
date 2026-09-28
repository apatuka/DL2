#!/usr/bin/env python3
"""derive_names.py - propose original function names from assertion / debug strings.

Reads re/functions.jsonl (from ghidra_scripts/ExportAll.java) and optional manual overrides
(re/names_manual.tsv: addr<TAB>name[<TAB>comment]) and writes re/names.tsv for ApplyNames.java.
"""
import json, re, collections, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RE = os.path.join(ROOT, "re")

PATTERNS = [
    (re.compile(r"\b(?:in|In|from|by)\s+([A-Za-z_][A-Za-z0-9_]*(?:::[A-Za-z_][A-Za-z0-9_]*)?)\s*\(\)"), 6),  # "NULL x in Foo()"
    (re.compile(r"\b(?:in|In)\s+([A-Z_][A-Za-z0-9_]*(?:::[A-Za-z_][A-Za-z0-9_]*)?)\s*[.!]?$"), 5),          # "... in Foo"
    (re.compile(r"^([A-Z][A-Za-z0-9_]*)--"), 4),                                                            # "Master--Surrender"
    (re.compile(r"\b([A-Z][A-Za-z0-9_]*(?:::[A-Za-z_][A-Za-z0-9_]*)?)\(\)"), 3),                            # "Foo()"
    (re.compile(r"^([A-Z][A-Za-z0-9_]*):\s"), 2),                                                           # "Foo: ..."
    (re.compile(r"^([A-Z][a-z]+(?:[A-Z][a-z0-9]+)+)$"), 2),                                                 # bare CamelCase tag
    (re.compile(r"^_?([A-Z][a-z]+(?:[A-Z][a-z0-9]+)+)\b"), 1),                                              # leading CamelCase word
]
STOP = {"Deadlock", "Accolade", "Cyberlore", "Windows", "DirectDraw", "DirectSound", "Error", "Warning",
        "Oolan", "Advice", "Shrine", "Wars", "Please", "Sorry", "Not", "Null", "Invalid", "Could", "Couldn",
        "Unable", "Cannot", "Can", "You", "Your", "The", "This", "Turn", "Player", "Players", "Game", "New",
        "Custom", "Chat", "Combat", "Territory", "Colony", "Nothing", "None", "Yes", "No", "Load", "Save",
        "NetAccolade", "TCP", "IP", "Version", "Scenario", "Options", "Victory", "Condition", "Conquest",
        "Military", "Technology", "Intelligence", "Energy", "Food", "Wood", "Metal", "Steel", "Iron", "Power",
        "Never", "Finished", "Finish", "Place", "Revolt", "Flood", "Plague", "Earthquake", "Bonus", "Clear",
        "Rough", "Scout", "Broadcast", "Uncloak", "Sprite", "Sprites", "Master", "Slave", "Debug", "Combat"}

def candidates(strings):
    votes = collections.Counter()
    for s in strings:
        s = s.strip().strip('"')
        for pat, w in PATTERNS:
            for m in pat.finditer(s):
                n = m.group(1)
                base = n.split("::")[0]
                if base in STOP or len(n) < 5 or n.isupper():
                    continue
                votes[n] += w
    return votes

def main():
    fs = []
    for l in open(os.path.join(RE, "functions.jsonl"), encoding="utf-8"):
        try:
            fs.append(json.loads(l))
        except json.JSONDecodeError:
            print("skipping malformed line", file=sys.stderr)
    manual = {}
    mp = os.path.join(RE, "names_manual.tsv")
    if os.path.exists(mp):
        for line in open(mp, encoding="utf-8"):
            if not line.strip() or line.startswith("#"): continue
            p = line.rstrip("\n").split("\t")
            manual[p[0].lower()] = (p[1], p[2] if len(p) > 2 else "")
    out = []
    auto = 0
    used = set(n for n, _ in manual.values())
    for f in fs:
        a = f["addr"].lower()
        if a in manual:
            out.append((a, manual[a][0], manual[a][1])); continue
        if not f["strings"]: continue
        v = candidates(f["strings"].split("|"))
        if not v: continue
        name, score = v.most_common(1)[0]
        if score < 3: continue
        name = name.replace("::", "__")
        if name in used:
            name = name + "_" + a[-4:]
        used.add(name)
        out.append((a, name, "auto-named from string evidence: " + ", ".join(k for k, _ in v.most_common(3))))
        auto += 1
    out.sort()
    with open(os.path.join(RE, "names.tsv"), "w", encoding="utf-8") as o:
        for a, n, c in out:
            o.write(f"{a}\t{n}\t{c}\n")
    print(f"names.tsv: {len(out)} entries ({auto} automatic, {len(manual)} manual)")

if __name__ == "__main__":
    main()
