cc=g++
cflags=-Wall -Werror -std=c++17

all: main.o
	mkdir -p build
	$(cc) main.o -o build/uwufy $(cflags)

main.o: src/main.cpp
	$(cc) -c src/main.cpp $(cflags)

clean:
	rm -rf *.o build/*

install: build/uwufy
	mkdir -p $(DESTDIR)/usr/bin
	install -m 0755 ./build/uwufy $(DESTDIR)/usr/bin/uwufy 

remove:
	rm -f $(DESTDIR)/usr/bin/uwufy
uninstall:
	rm -f $(DESTDIR)/usr/bin/uwufy