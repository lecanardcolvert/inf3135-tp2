.PHONY: all clean test

all:
	$(MAKE) -C src/
	$(MAKE) -C tests/

test:
	$(MAKE) test -C tests/

clean:
	$(MAKE) clean -C src/
	$(MAKE) clean -C tests/

