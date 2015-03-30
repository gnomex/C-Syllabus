#include "buffer.h"

/**
  Initializes and return a general purpose buffer
  @param size: the size of the char array
  @return poiter to buffer
*/
t_buffer* give_me_a_buffer( size_t size )  {
  t_buffer *buffer = NULL;
  char *data = NULL;

  size_t reserved_size = size + 1;

  buffer = (t_buffer *) malloc (sizeof (t_buffer));
  memset( buffer, 0, sizeof (t_buffer) );

  data = (char *) malloc (sizeof(char) * reserved_size); // Always more than you need, for security reasons

  buffer->data = data;
  buffer->allocated_size = reserved_size;
  buffer->current_legth = strlen(buffer->data);

  return buffer;
}

/**
  Assign content data to a buffer and check buffer overflow.
  @param buffer: the buffer
  @param data: the content do assign to the buffer
*/
void assign_data_to_buffer( t_buffer *buffer, char *data) {
  size_t data_length = strlen(data);

  if ( data_length > buffer->allocated_size ) {
    die("You tried to put a bigger array that your buffer can hold");
  }

  strncpy( buffer->data, data, data_length ); // Avoid buffer overflows
  buffer->current_legth = data_length;
}

void reverse_buffer_data( t_buffer *buffer )  {
  char *p = buffer->data;
  char *q = p;

  while(q && *q) ++q;
  for(--q; p < q; ++p, --q)
    *p = *p ^ *q,
    *q = *p ^ *q,
    *p = *p ^ *q;
}
