CC=gcc
CFLAGS = -g -Wall -fstack-protector -o

1: .c
  $(CC) $(CFLAGS)

2: .c
  $(CC) $(CFLAGS)  -lm

all: 1 2

clean:
  rm -rf exe*
