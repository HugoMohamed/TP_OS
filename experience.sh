#!/usr/bin/env bash
make clean
make
./fichier.sh
./gros_test.sh
./affichage.sh
pdflatex rapport.tex
