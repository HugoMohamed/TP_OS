CC = gcc
OPTIONS = -Wall

algo: algo.o allocation.o liste.o pile.o file.o
	$(CC) $(OPTIONS) algo.o allocation.o liste.o pile.o file.o -o algo
%o:%c %h
	$(CC) -o $@ -c $< $(OPTIONS)

clean:
	rm -rf *.o algo
