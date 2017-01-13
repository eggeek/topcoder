#!/usr/bin/env python
# -*-: encoding: utf-8 -*-
from tinydb import TinyDB, Query
from os import path
from os import listdir as ls

ignore = ["README.md", "clear.py", "cpp.tmpl", "greed.conf", "py.tmpl", "tools", 'statistic.txt']

def main():
    db = TinyDB("db.json")
    cur = '../'
    problems = []
    for f in ls(cur):
        if f in ignore:
            continue
        if f.startswith('.'):
            continue
        if not path.isdir(cur + '/' + f):
            continue
        print 'find round: %s' % f
        for problem_name in ls(cur + '/' + f):
            problems.append(problem_name.split('.')[0])
    for p in problems:
        q = Query()
        if (db.search(q.name == p)):
            print 'db update, problem :`%s` solved' % p
            db.update({'solved': True}, (q.name == p))

if __name__ == "__main__":
    main()
