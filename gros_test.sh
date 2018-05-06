#!/usr/bin/env bash

$i
$j
$algo
$nbCase
algo=1

while(( $algo <= 4 ))
do
    i=1
    while(( 2**$i <= 10000 ))
    do
	j=1
	while(( $j <= $i ))
	do
	    nbCase=$(( 2 ** $j ))
	    echo $nbCase $i
	    ./algo $algo $nbCase c test/test$i >> algos/algo$algo-$nbCase
	    j=$(( $j + 1 ))
	done
	i=$(( $i + 1 ))
    done
    algo=$(( $algo + 1 ))
done
