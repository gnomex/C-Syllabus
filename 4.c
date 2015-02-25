#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LIMIT 256

void* reader()  {
  char *str;
  char aux[BUFFER_LIMIT];

  printf("Enter a string : ");
  fgets(aux, BUFFER_LIMIT, stdin);
  printf("You entered: %s", aux);

  str = malloc(sizeof(char) * strlen(aux));

  strcpy(str, aux);

  return str;
}

void mark_and_replace(char token, char replaced_by, char *str) {
  int token_count = 0;
  int str_length = strlen(str);
  int i = 0;

  for ( ; i < str_length ; i++)  {
    if ( str[i] == token ) {
      token_count++;
      str[i] = replaced_by;
    }
  }

  if (token_count > 0)  {
    printf("Yeahh, we find %i a, checkout the new string: %s\n", token_count, str );
  }  else {
    printf("Ow no, we find %i a\n", token_count );
  }

}

int main(int argc, char const *argv[]) {

  char *str_1 = reader();

  mark_and_replace('a', 'b', str_1);

  free(str_1);

  return 0;
}
