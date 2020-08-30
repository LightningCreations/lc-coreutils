#!/bin/bash

$1 --mode=u-w test p

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

