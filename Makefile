exec = isomap

.PHONY: all bindir clean html test

all: bindir
	$(MAKE) -C src/
	cp src/$(exec) bin

test: all
	$(MAKE) test -C tests/

clean:
	$(MAKE) clean -C src/
	$(MAKE) clean -C tests/
	rm -rf bin

bindir:
	mkdir -p bin/

html:
	pandoc README.md -o README.html
	pandoc sujet.md -o sujet.html
