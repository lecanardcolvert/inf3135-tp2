exec = isomap

.PHONY: all bindir clean html test

all: bindir
	$(MAKE) -C src/
	$(MAKE) -C tests/
	cp src/$(exec) bin

test:
	$(MAKE) test -C tests/

clean:
	$(MAKE) clean -C src/
	$(MAKE) clean -C tests/
	rm -rf bin

bindir:
	mkdir -p bin/

html:
	pandoc README.md -o README.html
