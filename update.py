#!/usr/bin/env python
# -*-: encoding: utf-8 -*-
import sys
from shutil import rmtree, move
from tinydb import TinyDB, Query
from os import path
from os import listdir as ls
from os import makedirs

ignore = ["README.md", "clear.py", "cpp.tmpl", "greed.conf", "py.tmpl", "tools",
'statistic.txt']

def update():
    db = TinyDB("data/db.json")
    cur = './Archive'
    problems = []
    for f in ls(cur):
        if f in ignore:
            continue
        if f.startswith('.'):
            continue
        if not path.isdir(cur + '/' + f):
            continue
        # print 'find round: %s' % f
        for problem_name in ls(cur + '/' + f):
            problems.append(problem_name.split('.')[0])
    counter = 0
    for p in problems:
        q = Query()
        dp = db.search(q.name == p)
        if (len(dp) > 0 and dp[0]['solved'] is False):
            print 'db update, problem :`%s` solved' % p
            db.update({'solved': True}, (q.name == p))
            counter += 1
    print '>>>> %d rows have been updated.' % counter


def difficulty(item):
    return item['submissions'] * item['correct_rate'] * item['average_pts']

def update_statistic():
    db = TinyDB("data/db.json")
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
    with open("data/statistic.txt", 'w') as f:
        for i in out:
            f.write(i + '\n')
    print '>>>> data/statistic.txt has been updated.'

def finish(dirname):
    fnames = []
    for f in ls(dirname):
        if f.split('.')[-1] == 'cpp':
            fnames.append(f)
    if not path.exists('./Archive/%s' % dirname):
        pathname = './Archive/%s' % dirname
        makedirs(pathname)
        print '>>>> create directory:[%s]'
    for f in fnames:
        oldpath = '%s/%s' % (dirname, f)
        newpath = './Archive/%s/%s' % (dirname, f)
        move(oldpath, newpath)
        print '>>>> move [%s] to [%s]' % (oldpath, newpath)
    rmtree(dirname)


def main(*args):
    if len(args) == 0:
        update()
        update_statistic()
    else:
        finish(args[0])

if __name__ == "__main__":
    main(*sys.argv[1:])
