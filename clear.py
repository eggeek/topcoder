#!/usr/bin/env python
from os import listdir as ls
from os import remove
from os.path import isfile, join
from shutil import rmtree
protected = ['.git']
track_types = ['cpp', 'py']
cur = '.'
trash = []
dirs = []


for f in ls(cur):
    if not (isfile(join(cur, f)) or f in protected):
        dirs.append(f)

for d in dirs:
    curd = join(cur, d)
    for f in ls(curd):
        if not f.split('.')[-1] in track_types:
            trash.append(join(curd, f))
if trash:
    print 'Detect those files and folds'
    for i in trash:
        print i
    x = raw_input("Press 'y/n' to delete...")
    if x == 'y':
        for i in trash:
            print 'rm', i
            if isfile(i):
                remove(i)
            else:
                rmtree(i)
print 'Clean!'
