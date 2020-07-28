#!/bin/bash

touch test0

$1 --silent a=rx test0
ch=$?
if [ $ch -ne 0 ]
then
  exit $ch
fi

if [ -w ./test0 ]
then
  exit 1
fi

if [ ! -x ./test0  ]
then
  exit 1
fi
