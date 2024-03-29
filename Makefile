CC = g++
CFLAGS = -std=c++11
LINKER = -lpthread -lfftw3 -lm

all: main

main: main.cpp dct.o
	$(CC) $(CFLAGS) dct.o $(LINKER) $< -o $@

dct.o: dct.cpp dct.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f dct main *.o

