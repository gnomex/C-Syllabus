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
  size_t allocated_size;
  size_t current_legth;
} t_buffer;

typedef void (*fptr)(void);

t_buffer* give_me_a_buffer( size_t size );
void assign_data_to_buffer( t_buffer *buffer, char *data);

void strrev(char *p);

void find_the_size_of_text_file( FILE *file );

// fptr  ptrs[3] = { NULL, another_thing, something };

void die(char *message);

#endif /* !ENCRYPTER */
