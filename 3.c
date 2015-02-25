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

  strrev(str_1);

  printf("%s\n", str_1);


  return 0;
}
