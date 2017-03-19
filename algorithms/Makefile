CC=gcc
CFLAGS=-g -std=c99 -Wall -Wextra -O3 -fstack-protector -fstack-usage -ggdb -o

1: static_array.c
	$(CC) $< $(CFLAGS) static_array

2: binary_search.c
	$(CC) $< $(CFLAGS) binary_search

3: colorful.c
	$(CC) $< $(CFLAGS) colorful

all: 1 2

clean:
	rm -rf static_array binary_search colorful *.su
