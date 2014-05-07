#!/bin/bash

FILE=ucore/Makefile

cp $FILE "$FILE.bak";
gsed -i "s/bs=1M/bs=1048576/g" $FILE; 

FILE=ucore/package/config/Makefile

cp $FILE "$FILE.bak";
gsed -i "/-lcurses$/ s/$/ -lintl/g" $FILE;


