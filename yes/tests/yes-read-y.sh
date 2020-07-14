#!/bin/bash

$1 | read y

echo $y

if [ "$y" != "y" ]
then
  exit 1
fi

