CFLAGS=-Wall -pedantic -std=gnu99
test: test.o
	gcc -o test test.o
test.o: test.c
	gcc $(CFLAGS) -c test.c
