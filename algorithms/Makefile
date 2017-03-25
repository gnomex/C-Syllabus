CC=gcc
CFLAGS=-g -std=c99 -Wall -Wextra -O3 -fstack-protector -fstack-usage -ggdb -o

1: static_array.c
	$(CC) $< $(CFLAGS) static_array.run

2: hanoi.c
	$(CC) $< $(CFLAGS) hanoi.run

3: colorful.c
	$(CC) $< $(CFLAGS) colorful.run

4: factorial.c
	$(CC) $< $(CFLAGS) factorial.run

6: fibonacci.c
	$(CC) $< $(CFLAGS) fibonacci.run

7: our_malloc.c
	$(CC) $< $(CFLAGS) our_malloc.run

9: balanced_parentheses.c
	$(CC) $< $(CFLAGS) balanced_parentheses.run

all: 1 2

clean:
	rm -rf *.run colorful *.su
