#include "lib_crypt.h"

void crypt( char *password, char *salt, t_buffer *destination ) {
  int i;
  int count = strlen( password );
  char n_ch;

  reverse_me( salt );

  for (i = 0; i < count; i++) {
    n_ch = rotate_carry_left_of_char( password[i], salt[i] );
    append_a_char_to_buffer( destination, &n_ch );
  }
}

void decrypt( char *password, char *salt, t_buffer *destination ) {
  int i;
  int count = strlen( password );
  char n_ch;

  for (i = 0; i < count; i++) {
    n_ch = rotate_carry_rigth_of_char( password[i], salt[i] );
    append_a_char_to_buffer( destination, &n_ch );
  }

  reverse_buffer_data( destination );
}

unsigned char rotate_carry_left_of_char( const unsigned char ch,
                                         const unsigned char d )  {
  unsigned char x = (ch + d); // Auto overflow control
  // unsigned short int x = (ch + d); // By-hands overflow control

  if ( x > CH_HIGHER ) {
    return CH_LOWER + ( x - CH_HIGHER );
  }

  return x;
}

unsigned char rotate_carry_rigth_of_char( const unsigned char ch,
                                          const unsigned char d )  {
  unsigned char x = ch - d; // Auto overflow control
  // short int x = (ch - d); // By-hands overflow control

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
  */
  t_buffer *buffer = NULL; buffer = give_me_a_buffer( meta );  // The whole buffer

  if ( (file = fopen( filename, "r" )) ) {
    fseek( file, current, SEEK_CUR );

    char current;

    while ( !feof(file) ) {
      current = fgetc(file);  //int fgetc(FILE *stream)

      if ( current == EOF) {
        *c_eof = 1; // To be SURE!!!
        break;
      }

      if ( buffer->current_legth == meta ) {break;}
      else {append_a_char_to_buffer( buffer, &current );}

    } /* END_WHILE_FEOF_FILE*/

    printf(" -- info: chunk[%d]\n", buffer->current_legth );

    fclose(file);
  }
  else perror("auheuhaeuhae");

  return buffer;
}

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
                   t_buffer *password,
                   int option ) {
  size_t f_counter = 0;
  size_t meta = password->current_legth;
  int f_eof = 0;

  t_buffer *aux = NULL;
  t_buffer *crypter = NULL;

  printf("Job in progress # --fin[%s] --fout[%s] --password-size[%d]\n",
    files->input_file,
    files->output_file,
    meta );

  while ( !f_eof )  {
    aux = give_me_a_chunk_from_file( files->input_file , f_counter, meta, &f_eof );
    crypter = give_me_a_buffer( meta );

    printf("+ info: aux[%d] meta[%d] f_counter[%d] feof[%d]\n", aux->current_legth, meta, f_counter, f_eof);

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

    // printf("++ info: aux[%d] meta[%d] f_counter[%d] feof[%d]\n", aux->current_legth, meta, f_counter, f_eof);

    free(aux);
    free(crypter);
  }

  printf("Job done!\n");
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
