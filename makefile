CC = gcc
OPTIONS = -Wall

algo: algo.o liste.o page
	$(CC) $(OPTIONS) algo.o liste.o -o algo

page: page.o
	$(CC) $(OPTIONS) page.o -o page

%o:%c %h
	$(CC) -o $@ -c $< $(OPTIONS)

clean:
	rm -rf *.o algo page algos/* test/* *.aux *.log *.pdf *.toc
