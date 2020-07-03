ROOT_DIR = $(shell dirname "$(PWD)")
CFLAGS = -DROOT_DIR="\"$(ROOT_DIR)/\"" -g -std=c11 -Wall -Wextra $(shell pkg-config --cflags cairo)
LFLAGS = $(shell pkg-config --libs tap cairo) -ljansson
c_files = $(wildcard *.c)
obj_files = $(patsubst %.c,%.o,$(c_files))
exec = isomap

all: $(exec)

$(exec): $(obj_files) main.o
	gcc $^ $(LFLAGS) -o $(exec)

main.o: main.c
	gcc $(CFLAGS) -c $<

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o
