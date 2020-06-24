all: map.o map_graph.o

map.o: map.h map.c
	gcc $(shell pkg-config --cflags cairo) -c map.c

map_graph.o: map_graph.h map_graph.c
	gcc $(shell pkg-config --cflags cairo) -c map_graph.c

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
