CC=gcc
CFLAGS=-g -std=c99 -Wall -Wextra -O3 -fstack-protector -fstack-usage -ggdb -o

1: binary_search.c
	$(CC) $< $(CFLAGS) binary_search.run

all: 1

clean:
	rm -rf *.run *.su
