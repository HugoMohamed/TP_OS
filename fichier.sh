#!/usr/bin/env bash

$j
$nbPage

j=1

while(( 2**$j <= 10000 ))
do
    nbPage=$(( 2 ** $j ))
    ./page $nbPage test/test$j
    j=$(( $j + 1 ))
done

