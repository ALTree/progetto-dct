CC = gcc
CFLAGS = -std=c99 -Wall 
IMG = immagini/blu.bmp

dct: dct.c
	$(CC) $(CFLAGS) $< -lfftw3 -lm -o $@

bmp: bmp.c bmp.h
	$(CC) $(CFLAGS) $< -o $@

test: bmp
	./$< $(IMG)

.PHONY: clean
clean:
	rm -f bmp dct

