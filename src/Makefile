test_queue: test_queue.o queue.o
	gcc test_queue.o queue.o -o test_queue

queue.o: queue.h queue.c
	gcc -c queue.c

test_queue.o: test_queue.c
	gcc -c test_queue.c
