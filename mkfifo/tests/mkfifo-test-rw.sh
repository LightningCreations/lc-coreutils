#!/bin/bash

$1 test-pipe

echo 0 >test-pipe &
$2 <test-pipe
c=$?
unlink test-pipe

exit $c
