CC = g++
CFLAGS = -std=c++11
LINKER = -lpthread -lX11 -lfftw3 -lm

all: main

main: main.c dct.o
	$(CC) $(CFLAGS) dct.o $(LINKER) $< -o $@

dct.o: dct.c dct.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f dct main *.o

