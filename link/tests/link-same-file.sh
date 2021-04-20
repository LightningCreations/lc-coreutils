#!/bin/bash

test_dir=$(dirname $0)

for i in {0..128}
do
  $1 ${test_dir}/a${i} a${i}
  code=$?
  if [ $code -ne 1 ]
  then
    rm -f a${i}
    exit $code
  fi

  if [ ! \( ${test_dir}/a${i} -ef a${i} \) ]
  then
    rm -f a${i}
    exit 1
  fi
  rm -f a${i}
done

