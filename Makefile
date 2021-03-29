.POSIX:

include config.mk

OBJECTS = main.o

all: options uwufy

options:
	@echo uwufy options:
	@echo "CFLAGS  = $(MYCFLAGS)"
	@echo "LDFLAGS = $(MYLDFLAGS)"
	@echo "CC      = $(CC)"

.c.o:
	$(CC) $(MYCFLAGS) -c $<

uwufy: $(OBJECTS)
	$(CC) $(OBJECTS) -o uwufy $(MYLDFLAGS)

# Remove binary and object files
clean:
	rm -f uwufy $(OBJECTS)

# Install program
install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f uwufy $(DESTDIR)$(PREFIX)/bin
	chmod +x $(DESTDIR)$(PREFIX)/bin/uwufy
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/uwufy

.PHONY: all options clean install uninstall
