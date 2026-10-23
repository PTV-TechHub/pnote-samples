#!/usr/bin/env python3
"""Validate a pnote-samples tree in CI. The PNote sync never runs code from this repository: it uses its own pinned,
reviewed copy in infra gitops/pnote/samples/check_samples.py (infra#879). Keep the two in step.

usage: check_samples.py [ROOT]        (ROOT defaults to the repository root; exit 0 = OK, 1 = problems found)

Checks: only the allowed top-level entries; no symlinks or special files; per-file and total size limits; file-name
characters; text files decode as UTF-8; no secret-looking or personal data (Wi-Fi credentials other than the
placeholders, tokens/keys, e-mail addresses, phone numbers, learner robot data files such as Lb117072_*.json).
Standard library only (runs on the PNote host's python3 without extra packages).
"""
import os
import re
import sys

ALLOWED_TOP = {"README.md", "sao-chep-vao-thu-muc-cua-toi.ipynb", "leanbot-basic", "digital-twin", "synapse-city"}
DEV_ONLY = {".git", ".github", "tools", ".gitattributes", ".gitignore", "CHANGELOG.md"}   # not published (export-ignore)
MAX_FILE = 10 * 1024 * 1024
MAX_TOTAL = 100 * 1024 * 1024
MAX_FILES = 2000
TEXT_EXT = {".md", ".py", ".ino", ".json", ".csv", ".ipynb", ".bduino", ".xml", ".txt"}
NAME_OK = re.compile(r"^[A-Za-z0-9 ._()+-]+$")
WIFI_PLACEHOLDERS = {"YOUR_WIFI_SSID", "YOUR_WIFI_PASSWORD"}
PATTERNS = [
    ("wifi credential", re.compile(r"WIFI_(?:SSID|PASSWORD|PASS)\s+F?\(?\s*\"([^\"]*)\"")),
    ("private key", re.compile(r"-----BEGIN [A-Z ]*PRIVATE KEY-----")),
    ("github token", re.compile(r"\b(?:ghp|gho|ghs|ghu|github_pat)_[A-Za-z0-9_]{20,}")),
    ("aws key", re.compile(r"\bAKIA[0-9A-Z]{16}\b")),
    ("google api key", re.compile(r"\bAIza[0-9A-Za-z_-]{35}\b")),
    ("openai/anthropic key", re.compile(r"\bsk-(?:ant-)?[A-Za-z0-9_-]{20,}")),
    ("slack/telegram token", re.compile(r"\bxox[abprs]-[A-Za-z0-9-]{10,}|\b\d{8,10}:AA[A-Za-z0-9_-]{30,}")),
    ("password assignment", re.compile(r"(?i)\b\w*(?:password|passwd|pwd|secret|token)\w*\s*[:=]\s*[\"'][^\"'\s]{6,}[\"']")),
    ("e-mail address", re.compile(r"\b[A-Za-z0-9._%+-]+@[A-Za-z0-9-]+(?:\.[A-Za-z0-9-]+)*\.[A-Za-z]{2,}\b")),
    ("phone number", re.compile(r"(?<![\w.])(?:\+84|0)(?:3|5|7|8|9)\d{8}(?![\w.])")),
]
LEARNER_FILE = re.compile(r"(?i)^lb\d{5,}_")


def main(root):
    problems, total, count = [], 0, 0
    for entry in sorted(os.listdir(root)):
        if entry in DEV_ONLY:
            continue
        if entry not in ALLOWED_TOP:
            problems.append(f"{entry}: not an allowed top-level entry ({', '.join(sorted(ALLOWED_TOP))})")
    for dirpath, dirnames, filenames in os.walk(root):
        rel_dir = os.path.relpath(dirpath, root)
        top = rel_dir.split(os.sep)[0]
        if top in DEV_ONLY:
            dirnames[:] = []
            continue
        dirnames[:] = [d for d in dirnames if not (rel_dir == "." and d in DEV_ONLY)]
        for d in dirnames:
            p = os.path.join(dirpath, d)
            if os.path.islink(p):
                problems.append(f"{os.path.relpath(p, root)}: symlink")
            if not NAME_OK.match(d):
                problems.append(f"{os.path.relpath(p, root)}: directory name has unusual characters")
        for name in filenames:
            p = os.path.join(dirpath, name)
            rel = os.path.relpath(p, root).replace(os.sep, "/")
            if rel.split("/")[0] in DEV_ONLY:
                continue
            if os.path.islink(p) or not os.path.isfile(p):
                problems.append(f"{rel}: symlink or special file")
                continue
            count += 1
            size = os.path.getsize(p)
            total += size
            if size > MAX_FILE:
                problems.append(f"{rel}: {size} bytes > {MAX_FILE}")
            if not NAME_OK.match(name) or name.startswith("."):
                problems.append(f"{rel}: file name has unusual characters or is hidden")
            if LEARNER_FILE.match(name):
                problems.append(f"{rel}: looks like a learner's own robot data file (Lb<id>_*)")
            if os.path.splitext(name)[1].lower() not in TEXT_EXT:
                continue
            try:
                text = open(p, encoding="utf-8").read()
            except UnicodeDecodeError:
                problems.append(f"{rel}: not UTF-8 text")
                continue
            for label, rx in PATTERNS:
                for m in rx.finditer(text):
                    if label == "wifi credential" and m.group(1) in WIFI_PLACEHOLDERS:
                        continue
                    line = text.count("\n", 0, m.start()) + 1
                    problems.append(f"{rel}:{line}: {label}")   # never print the match itself
    if count > MAX_FILES:
        problems.append(f"{count} files > {MAX_FILES}")
    if total > MAX_TOTAL:
        problems.append(f"total {total} bytes > {MAX_TOTAL}")
    for p in problems:
        print("PROBLEM", p)
    print(f"checked {count} files, {total} bytes: {'OK' if not problems else str(len(problems)) + ' problem(s)'}")
    return 0 if not problems else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1] if len(sys.argv) > 1 else os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
