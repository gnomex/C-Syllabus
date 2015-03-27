#include "encrypt.h"

/**
  Initializes and return a general purpose buffer
  @param size: the size of the char array
  @return poiter to buffer
*/
t_buffer* give_me_a_buffer( size_t size )  {
  t_buffer *buffer = NULL;
  char *data = NULL;

  buffer = (struct _Buffer *) malloc (sizeof (struct _Buffer));
  memset( buffer, 0, sizeof (struct _Buffer) );

  data = (char *) malloc (sizeof(char) * size + 1); // Always more than you need, for security reasons

  buffer->data = data;
  buffer->length = size + 1;

  return buffer;
}

/**
  Reverse a char array. Side effects!
*/
void reverse_me(char *p)  {
  char *q = p;

  while(q && *q) ++q;
  for(--q; p < q; ++p, --q)
    *p = *p ^ *q,
    *q = *p ^ *q,
    *p = *p ^ *q;
}


// read_from_file -> filename
//   a buffer
//   a file
//   approx quantity of chars (sizeof(file) / sizeof(char))

//   while the file not end and current < approx (DEAL with EOF)

//     append to buffer ( DEAL with buffers sizes)

//     // async!!!!!!!
//     if buffer full
//         process
//         crypt
//         async write

//         no errors -> flush buffer
//         errors -> fuuu

//     done
// kill -9

// crypt -> buffer, salt
//   magic

// decrypt -> buffer, salt
//   magic

// reverse -> buffer


int main(int argc, char const *argv[])  {

  t_buffer *a = give_me_a_buffer(100);

  strcpy(a->data, "123456789101112131415");

  printf("Data is: %s\n", a->data);

  printf("Length of data is: %d \n", strlen(a->data));
  printf("Associated length is: %d\n", a->length);

  reverse_me( a->data );

  printf("Reversed is %s\n", a->data);

  free(a);

  return 0;
}
