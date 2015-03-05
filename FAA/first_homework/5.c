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

void strrev(char *p)  {
  char *q = p;
  while(q && *q) ++q;
  for(--q; p < q; ++p, --q)
    *p = *p ^ *q,
    *q = *p ^ *q,
    *p = *p ^ *q;
}


int main(int argc, char const *argv[]) {

  char *str_1 = reader();
  char *aux = malloc(sizeof(char) * strlen(str_1));

  strcpy(aux, str_1);

  strrev(aux);

  if (strcmp(str_1, aux) == 0 ) {
    printf("Yeaahh, you wrote a palindrome word. Good job. Check it: %s are equals to %s\n", str_1, aux);
  } else  {
    printf("You do not wrote a palindrome word. Try again. Check it: %s are not equals to %s\n", str_1, aux);
  }

  free(str_1);
  free(aux);

  return 0;
}
