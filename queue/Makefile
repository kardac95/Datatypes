CC=gcc
CFLAGS=-std=c99 -Wall -g
DEPS=queue.h
FILES=test.o queue.o

test: $(FILES) $(DEPS)                                                          
	$(CC) $(CFLAGS) $(FILES) -o test
test.o: test.c $(DEPS)                                                          
	$(CC) $(CFLAGS) -c test.c
queue.o: queue.c $(DEPS)
	$(CC) $(CFLAGS) -c queue.c
clean:                                                 
	rm *.o test
