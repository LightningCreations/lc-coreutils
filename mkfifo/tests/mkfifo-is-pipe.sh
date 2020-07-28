#!/bin/bash

$1 test1
ch=$?

if [ $ch -ne 0 ]
then
  unlink test1 && true
  exit $ch
fi

if [ ! -p test1 ]
then
  unlink test1 && true
  exit 1
fi

unlink test1

