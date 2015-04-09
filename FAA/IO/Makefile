CC=gcc
CFLAGS = -g -O3 -Wall -fstack-protector-all -ggdb -o

first: *.c
	$(CC) $(CFLAGS)

with_lib: *.c
	$(CC) $(CFLAGS)  -lm

time: time.c
	$(CC) $< $(CFLAGS) time

files: file_util.c
	$(CC) $< $(CFLAGS) file_util

# all: first

clean:
	rm -rf time file_util
