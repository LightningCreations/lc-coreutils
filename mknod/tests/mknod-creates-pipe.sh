#!/bin/bash

$1 test p
ch=$?

if [ $ch -ne 0 ]
then
  unlink test
  exit $ch
fi

if [ \! -p test ]
then
  unlink test
  exit 1
fi

unlink test
exit 0