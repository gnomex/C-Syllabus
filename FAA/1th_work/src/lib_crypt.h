#ifndef LIBCRYPT
#define LIBCRYPT

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "buffer.h"

#define INFD 0
#define OUTFD 1
#define CH_HIGHER 255
#define CH_LOWER 0
#define ENCRYPT 1
#define DECRYPT 2

typedef struct {
  char *input_file;
  char *output_file;
} f_descriptors;

size_t find_the_size_of_text_file( FILE *file );

void reverse_me( char *p );

// unsigned char rotate_carry_left_of_char( const unsigned char ch, const unsigned char d );
// unsigned char rotate_carry_rigth_of_char( const unsigned char ch, const unsigned char d );

t_buffer* give_me_a_chunk_from_file( const char *filename,
                                     const size_t current,
                                     const size_t meta,
                                     int *c_eof );

void crypt( char *password, char *salt, t_buffer *destination );
void decrypt( char *password, char *salt, t_buffer *destination );

void crypt_engine( f_descriptors *files,
                   t_buffer *password,
                   int option );

void partial_writer_to_a_file( t_buffer *stream, char *filename );

int check_files( f_descriptors *files );

f_descriptors* give_me_a_f_descriptor( size_t size );

void assign_fin( f_descriptors *src, const char *filename );
void assign_fout( f_descriptors *src, const char *filename );

void die( const char *message );

#endif /* !LIBCRYPT */
