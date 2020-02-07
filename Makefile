
cc=gcc
cflags=-Wall -Werror

all: main.o
	$(cc) main.o -o build/uwuify

main.o: src/main.c
	$(cc) -c src/main.c

clean:
	rm -rf *.o build/*

install: build/uwuify
	cp build/uwuify /usr/bin/uwuify -f

remove:
	rm -f /usr/bin/uwuify