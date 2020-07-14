#!/bin/bash

y=$($1 | head -n 1)

echo "${y}"
if [ "${y}" != "y" ]
then
  exit 1
fi

