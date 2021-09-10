CFLAGS=-Wall -pedantic -std=gnu99
test-power: power.o test-power.o
	gcc -o test-power power.o test-power.o
power.o: power.c
	gcc $(CFLAGS) -c power.c
test-power.o: test-power.c
	gcc $(CFLAGS) -c test-power.c
