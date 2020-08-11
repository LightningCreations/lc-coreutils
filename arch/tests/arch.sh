#!/bin/bash

if [ "$($1)" != "$2" ]
then
  exit 1
fi

exit 0