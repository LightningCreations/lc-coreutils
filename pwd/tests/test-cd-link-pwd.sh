#!/bin/bash

wd=$(pwd -P)
lwd=$(pwd -L)

mkdir test0
ln -s -T test0 test1
pushd test1

if [ $($1 -P) != ${wd}/test0 ]
then
popd
rm test1
rmdir test0
exit 1
fi

if [ $($1 -L) != ${lwd}/test1 ]
then
popd
rm test1
rmdir test0
exit 1
fi

popd
rm test1
rmdir test0
exit 0