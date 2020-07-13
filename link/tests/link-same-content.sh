#!/bin/bash

test_dir=$(dirname $0)

for i in {0..128}
do
  $1 ${test_dir}/a${i} a${i}
  code=$?
  if [ $code -ne 0 ]
  then
    exit $code
  fi
done

for hash in {md5,sha1,sha224,sha256,sha384,sha512}
do
  ${hash}sum -c ${test_dir}/${hash}sums
done

for i in {0..128}
do
  $1 ${test_dir}/a${i} a${i}
  code=$?
  if [ $code -ne 1 ]
  then
    exit $code
  fi
  rm -f a${i}
done
