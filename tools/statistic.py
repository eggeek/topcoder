#!/usr/bin/env python
# -*-: encoding: utf-8 -*-
from tinydb import TinyDB


def main():
    db = TinyDB("db.json")
    rows = db.all()
    rows.sort(key=lambda x: int(x['rid']), reverse=True)
    out = []
    out.append('%-40s|%-35s|%-8s|%-3s\n' % ("problem", "round", "level", "solved"))
    out.append('-' * (len(out[0]) - 1) + '\n')
    for row in rows:
        out.append('%-40s|%-35s|%-8s|%-5s\n' % (row['name'], row['round'], row['level'], row['solved']))
    with open("../statistic.txt", 'w') as f:
        for i in out:
            f.write(i)

if __name__ == "__main__":
    main()
