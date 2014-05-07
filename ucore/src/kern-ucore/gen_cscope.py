#!/usr/bin/env python
"""
    Generate cscope.out for current working dir

    capable of ignoring some directories and add other directories

    generated database use absolute path, so you can use it anywhere instead of
    absolutely under current directory
"""

from subprocess import *
import os

appendix = 'arch/arm'
ignore = ['arch','dde36', 'module', 'numa']

cd = os.getcwd()
ls = check_output('ls '+cd,shell=True).strip().split('\n')
dirs = filter(lambda x:os.path.isdir(x),ls)
dirs = filter(lambda x:x not in ignore,ls)
dirs.append(appendix)

files = []
for d in dirs:
    files.append(check_output('find '+d+' -name \"*.[c,h,S,s]\"',shell=True).split('\n'))

for f in files:
    print f

map(lambda x:os.path.join(cd,x),files)

