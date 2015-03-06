CC=gcc
CFLAGS = -g -Wall -fstack-protector -o

first: *.c
  $(CC) $(CFLAGS)

with_lib: *.c
  $(CC) $(CFLAGS)  -lm

all: first

clean:
