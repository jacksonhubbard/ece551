CFLAGS=-Wall -pedantic -std=gnu99
test-subseq: maxSeq.o test-subseq.o
	gcc -o test-subseq maxSeq.o test-subseq.o
maxSeq.o: maxSeq.c
	gcc $(CFLAGS) -c maxSeq.c
test-subseq.o: test-subseq.c
	gcc $(CFLAGS) -c test-subseq.c
