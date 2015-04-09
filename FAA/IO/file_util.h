#ifndef FILE_UTIL
#define FILE_UTIL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int pk;
  char* column;
  int column_lenght;
  int column_allocated_size;
} table_t;

/**
  int fseek(FILE *stream, long int offset, int whence)

  SEEK_SET  Beginning of file
  SEEK_CUR  Current position of the file pointer
  SEEK_END  End of file
*/

/**
  FILE *fopen( const char * filename, const char * mode );

  r Opens an existing text file for reading purpose.
  w Opens a text file for writing, if it does not exist then a new file is created. Here your program will start writing content from the beginning of the file.
  a Opens a text file for writing in appending mode, if it does not exist then a new file is created. Here your program will start appending content in the existing file content.
  r+  Opens a text file for reading and writing both.
  w+  Opens a text file for reading and writing both. It first truncate the file to zero length if it exists otherwise create the file if it does not exist.
  a+  Opens a text file for reading and writing both. It creates the file if it does not exist. The reading will start from the beginning but writing can only be appended.

  "rb", "wb", "ab", "rb+", "r+b", "wb+", "w+b", "ab+", "a+b"
*/

#endif
