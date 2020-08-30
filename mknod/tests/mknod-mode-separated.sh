#!/bin/bash

$1 -m u-w test p

ch=$?


if [ $ch -ne 0 ]
then
  unlink test
  exit $ch
fi

if [ \! -w test ]
then
  unlink test
  exit $ch
fi

unlink test
exit 0

