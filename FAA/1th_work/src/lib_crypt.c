#include "lib_crypt.h"

// int crypt( char *password, char *salt ) {

// }

unsigned char rotate_carry_left_of_char( const unsigned char ch, const unsigned char d )  {
  // unsigned char x = (ch + d); // Auto overflow control
  unsigned short int x = (ch + d); // By-hands overflow control

  if ( x > CH_HIGHER ) {
    return CH_LOWER + ( x - CH_HIGHER );
  }

  return x;
}

unsigned char rotate_carry_rigth_of_char( const unsigned char ch, const unsigned char d )  {
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

void read_the_file( t_buffer *stream, char *filename ) {
  int streamer_size = stream->current_legth;
  int approx = 0;

  FILE *file = NULL;

  t_buffer *aux = give_me_a_buffer(streamer_size);

  if ( file = fopen( filename, "r" ) ) {
    approx = find_the_size_of_text_file( file );

    if ( streamer_size > approx ) die("Action: read the input file, message: The stream is bigger than the file");

    printf("File lenght is: %d\n", approx);
    // fread(???)

    // while ( !feof(file) ){


    //   fread(???);
    fclose(file);

  } else{
    // deal_with_errors();
  }

  free(aux);

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
