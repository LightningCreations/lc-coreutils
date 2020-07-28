#!/bin/bash

touch test0

$1 --silent =555 test0
ch=$?
if [ $ch -ne 0 ]
then
  exit $ch
fi

if [ \! -r ./test0 ]
then
  exit 1
fi

if [ -w ./test0 ]
then
  exit 1
fi

if [ \! -x ./test0  ]
then
  exit 1
fi
