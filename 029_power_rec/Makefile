CFLAGS=-Wall -pedantic -std=gnu99 -ggdb3
test-power: power.o test-power.o
	gcc -g test-power power.o test-power.o
power.o: power.c
	gcc $(CFLAGS) -c power.c
test-power.o: test-power.c
	gcc $(CFLAGS) -c test-power.c
