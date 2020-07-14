#!/bin/bash

$1 Hello World | read a b

if [ $a != "Hello" ] || [ $b != "World" ]
then
  exit 1
fi