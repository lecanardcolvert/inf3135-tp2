CFLAGS = -std=c11 -Wall -Wextra $(shell pkg-config --cflags cairo)
c_files = $(wildcard *.c)
obj_files = $(patsubst %.c,%.o,$(c_files))

all: $(obj_files)

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o
