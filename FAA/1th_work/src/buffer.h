#ifndef BUFFER
#define BUFFER

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "buffer.h"
#include "lib_crypt.h"

#define INFD 0
#define OUTFD 1

typedef struct {
  char *data;
  size_t allocated_size;
  size_t current_legth;
} t_buffer;

t_buffer* give_me_a_buffer( size_t size );
void assign_data_to_buffer( t_buffer *buffer, char *data );
void reverse_buffer_data( t_buffer *buffer );

#endif /* !BUFFER */
