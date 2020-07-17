#!/bin/bash

dir=$($1 $0)
actual_dir=$2

if [ $dir != basename-matches-prgname.sh ]
then
  exit 1
fi
