cc=gcc
cflags=-Wall -Werror

all: main.o
	mkdir -p build
	$(cc) main.o -o build/uwufy

main.o: src/main.cpp
	$(cc) -c src/main.cpp

clean:
	rm -rf *.o build/*

ifeq ($(PREFIX),)
	PREFIX := /usr/
endif

install: build/uwufy
	mkdir -p $(DESTDIR)$(PREFIX)/bin/
	cp build/uwufy $(DESTDIR)$(PREFIX)/bin/uwufy -f

remove:
	rm -f $(DESTDIR)$(PREFIX)/bin/uwufy
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/uwufy