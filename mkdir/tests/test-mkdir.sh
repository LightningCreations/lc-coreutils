#!/bin/bash
rm -rf test_dir


$1 test_dir

code=$?
if [ $code -ne 0 ]
then
  exit $code
fi

if [ ! -d test_dir ]
then
  exit 1
fi

exit 0