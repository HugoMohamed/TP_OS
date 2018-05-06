#!/usr/bin/env bash

$nbCase
$algo

algo=1

while(( algo <= 4 ))
do
    i=1
    while(( 2**$i <= 10000 ))
    do
	nbCase=$(( 2 ** $i ))
	
	touch resultat.conf
	echo "set terminal pdf" >> resultat.conf
	echo "set output 'algos/algo$algo-$nbCase.pdf" >> resultat.conf
	echo "plot 'algos/algo$algo-$nbCase' w l" >> resultat.conf

	gnuplot resultat.conf

	rm resultat.conf
	i=$(( $i + 1 ))
    done
    algo=$(( $algo + 1 ))
done
