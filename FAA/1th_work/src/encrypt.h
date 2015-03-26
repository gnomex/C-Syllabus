#ifndef ENCRYPTER
#define ENCRYPTER

// #include <linux/module.h>
// #include <linux/kernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define INFD 0
#define OUTFD 1

typedef struct _Buffer {
  char *data;
  int length;
} t_buffer;

typedef void (*fptr)(void);

// fptr  ptrs[3] = { NULL, another_thing, something };

// int main(int argc, char const *argv[]);

#endif /* !ENCRYPTER */
