#!/usr/bin/env python
# -*-: encoding: utf-8 -*-
from tinydb import TinyDB

def difficulty(item):
    return item['submissions'] * item['correct_rate'] * item['average_pts']


def main():
    db = TinyDB("db.json")
    rows = db.all()
    rows.sort(key=lambda x: int(x['rid']), reverse=True)
    levels = {1: [], 2: [], 3: []}
    for row in rows:
        levels[row['level']].append(row)

    out = []
    header = '|%-35s|%-40s|%-6s|%-10s|%5s|%10s|' % ("round", "problem", "solved", "ave_pts",
            "rate", "submission")
    for k, v in levels.items():
        out.append('# LEVEL %d' % k)
        out.append('-' * len(header))
        out.append(header)
        out.append('-' * len(header))
        v.sort(key=lambda x: difficulty(x), reverse=True)
        for i in v:
            out.append('|%-35s|%-40s|%-6s|%-10.2lf|%-4.3lf|%10s|' % (i['round'], i['name'], i['solved'],
                i['average_pts'], i['correct_rate'], i['submissions']))
        out.append('*' * len(header))
    with open("../statistic.txt", 'w') as f:
        for i in out:
            f.write(i + '\n')

if __name__ == "__main__":
    main()
