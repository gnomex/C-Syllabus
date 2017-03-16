CC=gcc
CFLAGS=-g -std=c99 -Wall -Wextra -O3 -fstack-protector -fstack-usage -ggdb -o

1: static_array.c
	$(CC) $< $(CFLAGS) static_array

all: 1

clean:
	rm -rf static_array *.su
