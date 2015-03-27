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
  size_t length;
} t_buffer;

typedef void (*fptr)(void);

t_buffer* give_me_a_buffer( size_t size );

// fptr  ptrs[3] = { NULL, another_thing, something };

#endif /* !ENCRYPTER */
