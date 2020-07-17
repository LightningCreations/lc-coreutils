#!/bin/bash

dir=$($1 $0)
actual_dir=$2

if [ $dir != $actual_dir ]
then
  exit 1
fi
