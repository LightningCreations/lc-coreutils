#!/bin/bash
rm -rf test_dir

if [ -d test_dir ]
then
  exit 1
fi

$1 -m -0222 test_dir

code=$?
if [ $code -ne 0 ]
then
  exit $code
fi

if [ ! -d test_dir ]
then
  exit 1
fi

if [-w test_dir]
then
  exit 1
fi

exit 0