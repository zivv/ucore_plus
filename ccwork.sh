#!/bin/bash

git reset --hard "$1"

./ccmodifyMakefiles.sh

./ccbuild.sh
