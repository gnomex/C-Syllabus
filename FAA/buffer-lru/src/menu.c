#include <stdio.h>

#define BUFFER_LIMIT 256

void
remove_carriage_return_from_string(char *str)  {
  char *pos = NULL;
  if ( (pos = strchr( str, '\n' )) != NULL ) *pos = '\0';
}

char*
reader( char *message )  {
  char *str = NULL;
  char *str_t = NULL;
  char aux[BUFFER_LIMIT];

  printf("%s: ", message);
  __fpurge(stdin);
  fgets(aux, BUFFER_LIMIT + 1, stdin);

  remove_carriage_return_from_string(aux);

  size_t str_lenght = strlen(aux);
  str = malloc(sizeof(char) * str_lenght);

  strncpy(str, aux, str_lenght);

  return str;
}

int
num_reader()  {
  int number;

  printf("Choose one: ");
  __fpurge(stdin); //wait for the prompt to be written on the screen
  scanf("%d",&number);

  return number;
}

void
wait_a_time()  {
  int number;

  printf("Type a number and next enter to continue...");
  __fpurge(stdin); //wait for the prompt to be written on the screen
  scanf("%d",&number);
}
