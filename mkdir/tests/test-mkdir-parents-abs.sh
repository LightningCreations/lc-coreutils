#!/bin/bash
rm -rf test_dir

if [ -d test_dir]
then
  exit 1
fi

$1 -p $(pwd)/test_dir/test_subdir

code=$?
if [ $code -ne 0 ]
then
  exit $code
fi

if [ ! -d $(pwd)/test_dir/test_subdir ]
then
  exit 1
fi

exit 0