CC = gcc
OPTIONS = -Wall

algo: algo.o liste.o
	$(CC) $(OPTIONS) algo.o liste.o -o algo
%o:%c %h
	$(CC) -o $@ -c $< $(OPTIONS)

clean:
	rm -rf *.o algo
