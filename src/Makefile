test_queue: test_queue.o queue.o
	gcc test_queue.o queue.o $(shell pkg-config --libs tap) -o test_queue

test_queue.o: test_queue.c
	gcc $(shell pkg-config --cflags tap) -c test_queue.c

queue.o: queue.h queue.c
	gcc -c queue.c
