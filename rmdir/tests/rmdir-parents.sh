#!/bin/sh

mkdir -p hello/world/im/really/long

$1 -p hello/world/im/really/long

code=$?

if [ $code -ne 0 ]
then 
exit $code
fi

if [ -d hello ]
then
exit 1
fi