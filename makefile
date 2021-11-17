CC=gcc
CFLAGS=-g -O2 -std=gnu17 -Wall -pedantic 
LIBS=-lncurses -ltinfo --enable-ext-colors
TARGET=tinytetris
DEPS=tetris.h
OBJ=tetris.o tinytetris.o

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

all: $(TARGET)

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)
$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	-rm -f *.o tinytetris

.PHONY: install
install: $(TARGET)
	cp $< $(DESTDIR)$(PREFIX)/bin/

.PHONY: UNINSTALL
UNINSTALL:
	-rm  $(DESTDIR)$(PREFIX)/bin/tinytetris
