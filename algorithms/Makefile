CC=gcc
CFLAGS=-g -std=c99 -Wall -Wextra -O3 -fstack-protector -fstack-usage -ggdb -o

1: static_array.c
	$(CC) $< $(CFLAGS) static_array.run

2: hanoi.c
	$(CC) $< $(CFLAGS) hanoi.run

3: colorful.c
	$(CC) $< $(CFLAGS) colorful.run

all: 1 2

clean:
	rm -rf *.run colorful *.su
