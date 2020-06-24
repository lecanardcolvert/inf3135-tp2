test_queue: test_queue.o queue.o
	gcc test_queue.o queue.o $(shell pkg-config --libs tap) -o test_queue

test_queue.o: test_queue.c
	gcc $(shell pkg-config --cflags tap) -c test_queue.c

queue.o: queue.h queue.c
	gcc -c queue.c

.PHONY: clean test

clean:
	rm -f *.o
	rm -f test_queue

test: test_queue
	./test_queue
