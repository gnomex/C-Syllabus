CC=gcc
CFLAGS = -g -Wall -o

1: 1.c
	$(CC) $(CFLAGS) exe1 1.c

2: 2.c
	$(CC) $(CFLAGS) exe2 2.c
