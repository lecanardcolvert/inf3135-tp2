.PHONY: all clean test

all:
	$(MAKE) -C src/

clean:
	$(MAKE) clean -C src/
	$(MAKE) clean -C tests/

test:
	$(MAKE) test -C tests/
