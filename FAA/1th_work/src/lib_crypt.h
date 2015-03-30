#ifndef LIBCRYPT
#define LIBCRYPT

// #include <linux/module.h>
// #include <linux/kernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "buffer.h"

#define INFD 0
#define OUTFD 1

typedef void (*fptr)(void);

void find_the_size_of_text_file( FILE *file );

// fptr  ptrs[3] = { NULL, another_thing, something };

void reverse_me( char *p );

void die(char *message);

void find_the_size_of_text_file( FILE *file );

#endif /* !LIBCRYPT */
