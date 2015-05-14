#include "file_util.h"

// int
// tokenizer()
// {
//   const char str[80] = "This is - www.tutorialspoint.com - website";
//   const char s[2] = "-";
//   char *token;

//   /* get the first token */
//   token = strtok(str, s);

//   /* walk through other tokens */
//   while( token != NULL )
//   {
//     printf( " %s\n", token );

//     token = strtok(NULL, s);
//   }

//   return(0);
// }


/**
  Initializes and return a general purpose table
  @param size: the size of the char array
  @return poiter to buffer
*/
table_t*
give_me_a_table(
  size_t size )
{
  table_t *buffer = NULL;
  char *data = NULL;

  size_t reserved_size = size + 1;

  buffer = (table_t *) malloc( sizeof( table_t ) );
  memset( buffer, 0, sizeof( table_t ) );

  data = (char *) malloc (sizeof(char) * reserved_size);

  buffer->pk     = 0;
  buffer->column = data;
  buffer->column_length = strlen( buffer->column );
  buffer->column_allocated_size = reserved_size;

  return buffer;
}

void
assign_column_data_to_table(
  table_t *source,
  const char *string )
{
  size_t data_length = strlen( string );

  if ( data_length > source->column_allocated_size ) {
    die("You tried to put a bigger array that your buffer can hold");
  }

  strncpy( source->column, string, data_length ); // Avoid buffer overflows
  source->column_length = data_length;

}

size_t
find_the_size_of_a_file( FILE *file ) {
  size_t size = 0;

  fseek(file, 0L, SEEK_END);
  size = ftell(file);
  fseek(file, 0L, SEEK_SET);

  return size;
}

off_t
find_the_size_of_a_regularfile( char *filename )
{
  struct stat stbuf;
  int fd;

  fd = open( filename, O_RDONLY );
  if (fd == -1) {
    FILE *a = fopen( filename, "w");
    fclose(a);
  }

  if ( (fstat(fd, &stbuf) != 0) || ( !S_ISREG(stbuf.st_mode) ) ) { /* Handle error */ }

  return stbuf.st_size;
}



void
assign_column_pk_to_table(
  table_t *source,
  const off_t pk )
{
  source->pk = pk;
}

int
write_table_to_text_file(
  char *filename,
  table_t *table,
  int FILETYPE )
{
  FILE *file = NULL;

  off_t id = find_the_size_of_a_regularfile( filename );

  if ( (file = fopen( filename, "a" )) ) {

    assign_column_pk_to_table( table, id );

    fputs( table->column, file );

    fclose(file);
  } /* END_WHILE_FEOF_FILE*/
  else {
    perror("auheuhaeuhae");
    return 0;
  }

  return 1;
}

int
write_table_to_bin_file(
  char *filename,
  table_t *table,
  int FILETYPE )
{
  FILE *file = NULL;

  off_t id = find_the_size_of_a_regularfile( filename );

  if ( (file = fopen( filename, "a" )) ) {

    assign_column_pk_to_table( table, id );

    fwrite( table, sizeof(table_t), 1, file );

    fclose(file);
  } /* END_WHILE_FEOF_FILE*/
  else {
    perror("auheuhaeuhae");
    return 0;
  }

  return 1;
}


/**
  From: http://www.tutorialspoint.com/cprogramming/c_file_io.htm

  int fseek(FILE *stream, long int offset, int whence)

  SEEK_SET  Beginning of file
  SEEK_CUR  Current position of the file pointer
  SEEK_END  End of file

  FILE *fopen( const char * filename, const char * mode );

  r Opens an existing text file for reading purpose.
  w Opens a text file for writing, if it does not exist then a new file is created. Here your program will start writing content from the beginning of the file.
  a Opens a text file for writing in appending mode, if it does not exist then a new file is created. Here your program will start appending content in the existing file content.
  r+  Opens a text file for reading and writing both.
  w+  Opens a text file for reading and writing both. It first truncate the file to zero length if it exists otherwise create the file if it does not exist.
  a+  Opens a text file for reading and writing both. It creates the file if it does not exist. The reading will start from the beginning but writing can only be appended.

  "rb", "wb", "ab", "rb+", "r+b", "wb+", "w+b", "ab+", "a+b"

int fputc( int c, FILE *fp );
int fgetc( FILE * fp );
int fputs( const char *s, FILE *fp );
char *fgets( char *buf, int n, FILE *fp );

size_t fread(void *ptr, size_t size_of_elements,
             size_t number_of_elements, FILE *a_file);
size_t fwrite(const void *ptr, size_t size_of_elements,
             size_t number_of_elements, FILE *a_file);

*/



/**
  Error handler
*/
void
die( const char *message )
{
  if(errno) {
      perror(message);
  } else {
    printf("[ ERROR ] %s. {INFO: Use gdb to debbug}\n", message);
  }

  exit(1);
}


int main(int argc, char const *argv[])
{
  /* code */
  return 0;
}
