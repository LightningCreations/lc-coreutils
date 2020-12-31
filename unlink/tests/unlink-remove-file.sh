#!/bin/sh

touch file

$1 file

code=$?

if [ $code -ne 0 ]
then 
exit $code
fi

if [ -e file ]
then
exit 1
fi