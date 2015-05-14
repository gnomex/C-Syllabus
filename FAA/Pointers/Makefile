CC=gcc
CFLAGS = -g -O3 -Wall -fstack-protector-all -ggdb -o

1: pointers.c
	$(CC) $< $(CFLAGS) pointers

2: pointer_to_function.c
	$(CC) $< $(CFLAGS) ptr_to_f

all: 1

clean:
	rm -rf pointers
