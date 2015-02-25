#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LIMIT 80

void remove_carriage_return_from_string(char *str)  {
  char *pos;

  if ((pos=strchr(str, '\n')) != NULL)
    *pos = '\0';
}

void* reader()  {
  char *str;
  char aux[BUFFER_LIMIT];

  printf("Enter a string : ");
  fgets(aux, BUFFER_LIMIT, stdin);
  printf("You entered: %s", aux);

  remove_carriage_return_from_string(aux);

  str = malloc(sizeof(char) * strlen(aux));

  strcpy(str, aux);

  return str;
}

int main(int argc, char const *argv[]) {

  char *str_1 = reader();

  int size_of_string = strlen(str_1);

  printf("String content: %s, and string lenght: %i\n", str_1, size_of_string);

  free(str_1);

  return 0;
}
