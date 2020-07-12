#!/bin/bash

wd=$(pwd -P)
lwd=$(pwd -L)

mkdir test0
ln -s -T test0 test
pushd test

if [ $($1 -P) != ${wd}/test0 ]
then
popd
rm test
rmdir test0
exit 1
fi

if [ $($1 -L) != ${lwd}/test ]
then
popd
rm test
rmdir test0
exit 1
fi

popd
rm test
rmdir test0
exit 0