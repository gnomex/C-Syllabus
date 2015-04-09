#include "file_util.h"

int
tokenizer()
{
  const char str[80] = "This is - www.tutorialspoint.com - website";
  const char s[2] = "-";
  char *token;

  /* get the first token */
  token = strtok(str, s);

  /* walk through other tokens */
  while( token != NULL )
  {
    printf( " %s\n", token );

    token = strtok(NULL, s);
  }

  return(0);
}


int
main(
  int argc,
  char const *argv[])
{

  return 0;
}
