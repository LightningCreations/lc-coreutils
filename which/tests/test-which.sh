#!/bin/bash

PATH=$2

val=$($1 $3)

if [ "$val" != "$2/$3" ]
then
  exit 1
fi

exit 0