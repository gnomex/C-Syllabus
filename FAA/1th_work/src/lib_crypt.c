#include "lib_crypt.h"

// int crypt( char *password, char *salt ) {

// }

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
  t_buffer *buffer = NULL; buffer = give_me_a_buffer( meta );  // The whole buffer

  if ( file = fopen( filename, "r" ) ) {
    printf("Opened\n");
    fseek( file, current, SEEK_CUR );

    printf("Seeked\n");

    char current;

    while ( !feof(file) ) {
      current = fgetc(file);  //int fgetc(FILE *stream)
      // printf("# reader: current[%c,%d]\n", current, current);

      if ( current == EOF) {
        *c_eof = 1;
        break;
      }

      if ( buffer->current_legth == meta ) break;
      else append_a_char_to_buffer( buffer, &current );

    } /* END_WHILE_FEOF_FILE*/

    fclose(file);

    return buffer;
  }
  else perror("auheuhaeuhae");
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

// void partial_writer_to_a_file( t_buffer *stream, char *filename )  {
//   FILE *file = NULL;  // The given file

//   if ( file = fopen( filename, "a" ) ) {

//     fputs( stream->data, file );

//     fclose( file );
//   } else  {
//     // deal_with_errors();
//   }
// }

// crypt -> buffer, salt
//   magic

// decrypt -> buffer, salt
//   magic

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
