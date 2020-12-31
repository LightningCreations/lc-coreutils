#!/bin/sh

mkdir test

$1 test

code=$?

if [ $code -ne 0 ]
then 
exit $code
fi

if [ -d test ]
then
exit 1
fi
