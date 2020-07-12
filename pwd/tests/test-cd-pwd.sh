#!/bin/bash


wd=$(pwd -P)

mkdir test
pushd test

if [ "$($1 -P)" != "${wd}/test" ]
then
popd
rmdir test
exit 1
fi

popd
rmdir test

exit 0