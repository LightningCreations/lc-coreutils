#!/bin/bash

if [ "$($1)" != "$(uname -m)" ]
then
  exit 1
fi

exit 0
