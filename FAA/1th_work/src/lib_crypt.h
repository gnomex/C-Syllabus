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

typedef void ( *fptr )( void );
typedef unsigned char ( *f_rotate )( unsigned char a, unsigned char b );

void find_the_size_of_text_file( FILE *file );

// fptr  ptrs[3] = { NULL, another_thing, something };

void reverse_me( char *p );

void die( const char *message );

void find_the_size_of_text_file( FILE *file );

unsigned char rotate_carry_left_of_char( const unsigned char ch, const unsigned char d );
unsigned char rotate_carry_rigth_of_char( const unsigned char ch, const unsigned char d );

#endif /* !LIBCRYPT */
