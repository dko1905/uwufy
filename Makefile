
cc=g++
cflags=-Wall -Werror

all: main.o
	mkdir -p build
	$(cc) main.o -o build/uwufy

main.o: src/main.cpp
	$(cc) -c src/main.cpp

clean:
	rm -rf *.o build/*

install: build/uwufy
	cp build/uwufy /usr/bin/uwufy -f

remove:
	rm -f /usr/bin/uwufy