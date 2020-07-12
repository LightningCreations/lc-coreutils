#!/bin/bash

if [ $($1 -P) != $(pwd -P) ]
then
exit 1
fi

if [ $($1 -L) != $(pwd -L) ]
then
exit 1
fi

exit 0