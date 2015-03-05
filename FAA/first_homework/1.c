#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LIMIT 256


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
  char *str_2 = reader();
  char *str_3 = reader();
  char *str_4 = reader();

  int size_of_strings = strlen(str_1) + strlen(str_2) + strlen(str_3) + strlen(str_4);

  if (size_of_strings > 0)  {
    char all_strings[size_of_strings];
    strcpy(all_strings, str_1);
    strcat(all_strings, str_2);
    strcat(all_strings, str_3);
    strcat(all_strings, str_4);

    printf("String content: %s, and string lenght: %i\n", all_strings, strlen(all_strings));

  } else  {
    printf("Invalid string \n");
  }

  free(str_1);
  free(str_2);
  free(str_3);
  free(str_4);

  return 0;
}
