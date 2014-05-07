#!/bin/bash

./ccbuild.sh 1>/dev/null 2>/tmp/out && grep --color=always "error" /tmp/out
