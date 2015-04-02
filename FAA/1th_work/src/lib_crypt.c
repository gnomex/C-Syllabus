#include "lib_crypt.h"

int crypt( char *password, char *salt, t_buffer *destination ) {
  return 1;
}

int decrypt( char *password, char *salt, t_buffer *destination ) {
  return 1;
}


unsigned char rotate_carry_left_of_char( const unsigned char ch,
                                         const unsigned char d )  {
  // unsigned char x = (ch + d); // Auto overflow control
  unsigned short int x = (ch + d); // By-hands overflow control

  if ( x > CH_HIGHER ) {
    return CH_LOWER + ( x - CH_HIGHER );
  }

  return x;
}

unsigned char rotate_carry_rigth_of_char( const unsigned char ch,
                                          const unsigned char d )  {
  // unsigned char x = ch - d; // Auto overflow control
  short int x = (ch - d); // By-hands overflow control

  if ( x < CH_LOWER ) {
    return CH_HIGHER + ( x + CH_LOWER );
  }

  return x;
}

size_t find_the_size_of_text_file( FILE *file ) {
  size_t size = 0;

  fseek(file, 0L, SEEK_END);
  size = ftell(file);
  fseek(file, 0L, SEEK_SET);

  return size;
}

t_buffer* give_me_a_chunk_from_file( const char *filename,
                                     const size_t current,
                                     const size_t meta,
                                     int *c_eof )  {
  FILE *file = NULL;
  /**
    The question: What is the best buffer size?
    Using @param meta - @param current can give us a approximation
  */
  t_buffer *buffer = NULL; buffer = give_me_a_buffer( (meta - current) );  // The whole buffer

  if ( (file = fopen( filename, "r" )) ) {
    fseek( file, current, SEEK_CUR );

    char current;

    while ( !feof(file) ) {
      current = fgetc(file);  //int fgetc(FILE *stream)

      if ( current == EOF) {
        *c_eof = 1; // To be SURE!!!
        break;
      }

      if ( buffer->current_legth == meta ) break;
      else append_a_char_to_buffer( buffer, &current );

    } /* END_WHILE_FEOF_FILE*/

    fclose(file);
  }
  else perror("auheuhaeuhae");

  return buffer;
}

// void partial_reader_the_file( t_buffer *stream, char *filename ) {
//   int streamer_size = stream->current_legth;
//   int approx = 0;
//   FILE *file = NULL; // The given FILE
//   t_buffer *aux = give_me_a_buffer(streamer_size);  // The whole buffer
//   if ( file = fopen( filename, "r" ) ) {
//     approx = find_the_size_of_text_file( file );
//     if ( streamer_size > approx ) die("Action: read the input file, message: The stream is bigger than the file");
//     // printf("File lenght is: %d\n", approx); // Low level debug
//     while ( !feof(file) ) {
//       if (buffer.is_full) {
//         sync_and_reset( aux );
//       }
//       char current = fgetc(file);
//       append_to_buf(current);
//     } /* END_FEOF_FILE*/
//     fclose(file);
//   } else  {
//     // deal_with_errors();
//   }
//   free(aux); // Tnks buffer for your service
// }

void partial_writer_to_a_file( t_buffer *stream, char *filename )  {
  FILE *file = NULL;  // The given file

  if ( (file = fopen( filename, "a" )) ) {

    fputs( stream->data, file );

    fclose( file );
  } else  {
    // deal_with_errors();
  }
}

void crypt_engine( f_descriptors *files,
                   const t_buffer *password,
                   int option ) {
  unsigned int f_counter = 0;
  unsigned int meta = password->current_legth;
  int f_eof = 0;

  t_buffer *aux = NULL;
  t_buffer *crypter = NULL; crypter = give_me_a_buffer( (meta - f_counter) );

  while ( !f_eof )  {
    aux = give_me_a_chunk_from_file( files->input_file , f_counter, meta, &f_eof );

    switch (option) {
      case ENCRYPT:
        crypt( password->data, aux->data, crypter);
        break;
      case DECRYPT:
        decrypt( password->data, aux->data, crypter);
        break;
    }

    partial_writer_to_a_file( crypter, files->output_file );
    f_counter += meta;
  }
}

/**
  Reverse a char array. Side effects!
*/
void reverse_me( char *p )  {
  char *q = p;

  while(q && *q) ++q;
  for(--q; p < q; ++p, --q)
    *p = *p ^ *q,
    *q = *p ^ *q,
    *p = *p ^ *q;
}


/**
  Error handler
*/
void die( const char *message ) {
  if(errno) {
      perror(message);
  } else {
    printf("[ ERROR ] %s. {INFO: Use gdb to debbug}\n", message);
  }

  exit(1);
}


f_descriptors* give_me_a_f_descriptor( size_t size )  {
  f_descriptors *buffer = NULL;
  char *in = NULL;
  char *out = NULL;

  size_t reserved_size = size + 1;

  buffer = (f_descriptors *) malloc (sizeof (f_descriptors));
  memset( buffer, 0, sizeof (f_descriptors) );

  in = (char *) malloc (sizeof(char) * reserved_size); // Always more than you need, for security reasons
  out = (char *) malloc (sizeof(char) * reserved_size); // Always more than you need, for security reasons

  buffer->input_file = in;
  buffer->output_file = out;

  return buffer;
}

void assign_fin( f_descriptors *src, const char *filename ) {
  size_t data_length = strlen(filename);

  strncpy( src->input_file, filename, data_length ); // Avoid buffer overflows
}

void assign_fout( f_descriptors *src, const char *filename ) {
  size_t data_length = strlen(filename);

  strncpy( src->output_file, filename, data_length ); // Avoid buffer overflows
}
