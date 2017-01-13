#!/usr/bin/env python
# -*-: encoding: utf-8 -*-
from tinydb import TinyDB


def main():
    db = TinyDB("db.json")
    rows = db.all()
    rows.sort(key=lambda x: int(x['rid']), reverse=True)
    levels = {1: [], 2: [], 3: []}
    for row in rows:
        levels[row['level']].append(row)

    out = []
    header = '|%-35s|%-40s|%-6s|' % ("round", "problem", "solved")
    for k, v in levels.items():
        out.append('# LEVEL %d' % k)
        out.append('-' * len(header))
        out.append(header)
        out.append('-' * len(header))
        for i in v:
            out.append('|%-35s|%-40s|%-6s|' % (i['round'], i['name'], i['solved']))
        out.append('*' * len(header))
    with open("../statistic.txt", 'w') as f:
        for i in out:
            f.write(i + '\n')

if __name__ == "__main__":
    main()
