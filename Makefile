HOMEBREW_PREFIX := $(shell brew --prefix)

LFLAGS  :=$(shell sdl2-config --libs)
CFLAGS :=$(shell sdl2-config --cflags) -I$(HOMEBREW_PREFIX)/include

build:
	clang -Wall -std=c99 $(CFLAGS) ./src/*.c $(LFLAGS) -o renderer

run:
	./renderer

clean:
	rm ./renderer
