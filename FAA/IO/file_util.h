#ifndef FILE_UTIL
#define FILE_UTIL

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define TEXT_FILE 1
#define BINARY_FILE 2

typedef struct {
  off_t pk;
  char* column;
  int column_length;
  int column_allocated_size;
} table_t;

void die( const char *message );

#endif
