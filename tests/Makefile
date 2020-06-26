src_dir = src
tests_c_files = $(wildcard *.c)
tests_obj_files = $(patsubst %.c,%.o,$(tests_c_files))
tests_exec_files = $(patsubst %.c,%,$(tests_c_files))
src_obj_files = $(wildcard ../$(src_dir)/*.o)
CFLAGS = -Wall -Wextra $(shell pkg-config --cflags tap cairo)
LFLAGS = $(shell pkg-config --libs tap cairo)

.PHONY: all clean source test

all: source $(tests_exec_files)

$(tests_exec_files): %: %.o
	gcc $(src_obj_files) $< $(LFLAGS) -o $@

%.o: %.c 
	gcc $(CFLAGS) -c $<

source:
	$(MAKE) -C ../$(src_dir)

clean:
	rm -f *.o
	rm -f $(tests_exec_files)

test: all
	./test_queue
