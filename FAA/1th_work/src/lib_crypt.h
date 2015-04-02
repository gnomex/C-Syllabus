#ifndef LIBCRYPT
#define LIBCRYPT

// #include <linux/module.h>
// #include <linux/kernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "buffer.h"

#define INFD 0
#define OUTFD 1
#define CH_HIGHER 255
#define CH_LOWER 0

// typedef void ( *fptr )( void );
// typedef unsigned char ( *f_rotate )( unsigned char a, unsigned char b );

size_t find_the_size_of_text_file( FILE *file );

void reverse_me( char *p );

unsigned char rotate_carry_left_of_char( const unsigned char ch, const unsigned char d );
unsigned char rotate_carry_rigth_of_char( const unsigned char ch, const unsigned char d );

// t_buffer* give_me_a_chunk_from_file( const char *filename, const size_t current, const size_t meta, int *c_eof );

void die( const char *message );

#endif /* !LIBCRYPT */
