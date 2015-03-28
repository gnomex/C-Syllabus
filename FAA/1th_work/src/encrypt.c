#include "encrypt.h"

/**
  Initializes and return a general purpose buffer
  @param size: the size of the char array
  @return poiter to buffer
*/
t_buffer* give_me_a_buffer( size_t size )  {
  t_buffer *buffer = NULL;
  char *data = NULL;

  size_t reserved_size = size + 1;

  buffer = (struct _Buffer *) malloc (sizeof (struct _Buffer));
  memset( buffer, 0, sizeof (struct _Buffer) );

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

// size_t find_the_size_of_text_file( FILE *file ) {
//   size_t size = 0;

//   fseek(file, 0L, SEEK_END);
//   size = ftell(file);
//   fseek(file, 0L, SEEK_SET);

//   return size;
// }

// void read_the_file( size_t *stream, char *filename ) {
//   int streamer_size = stream->length;
//   int approx = 0;

//   FILE *file = NULL;

//   t_buffer *aux = give_me_a_buffer(streamer_size);

//   if (file = fopen(filename,"r")){
//     approx = find_the_size_of_text_file( file );

//     fread(???)

//     while ( !feof(file) ){


//       fread(???);
//     }

//     fclose(file);

//   }else{
//     deal_with_errors();
//   }

//   free(aux);

// }
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

void die( char *message ) {
  printf("[ERROR] %s. {INFO: Use gdb to debbug}\n", message);
  exit(1);
}


int main(int argc, char const *argv[])  {

  t_buffer *a = give_me_a_buffer(10);

  assign_data_to_buffer( a, "1234567891");

  printf("Data is: %s\n", a->data);

  printf("Length of data is: %d \n", strlen(a->data));
  printf("Associated length is: %d\n", a->current_legth);
  printf("Allocated buffer size is: %d\n", a->allocated_size);

  reverse_me( a->data );

  printf("Reversed is: %s\n", a->data);

  free(a);

  return 0;
}
