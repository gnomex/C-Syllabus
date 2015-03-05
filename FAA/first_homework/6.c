#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LIMIT 12
#define DECIMAL 10
#define ARRAY_SIZE 10

int posix_reader()  {
  int number;
  /* .. */
  printf("Enter a number: ");
  fflush(stdout); //wait for the prompt to be written on the screen
  scanf("%d",&number);

  return number;
}

long alternative_reader()  {
  char *str;
  long number;
  char aux[BUFFER_LIMIT];

  printf("Enter a number: ");
  fgets(aux, BUFFER_LIMIT, stdin);

  number = strtol(aux, &str, DECIMAL);

  return number;
}

void reverse_a_array(int *src, int *dst)  {
  int i = 0;
  int j = ARRAY_SIZE - 1;
  for ( ; i < ARRAY_SIZE; ++i) {
    dst[j] = src[i];
    j--;
  }
}

void populate_a_array_with_user_input(int *array)  {
  int i = 0;
  for ( ; i < ARRAY_SIZE; ++i)  {
    array[i] = posix_reader();
    // array[i] = alternative_reader();
  }
}

void show_elements_from_array(int *array, char *optnional_message) {
  int i = 0;
  for ( ; i < ARRAY_SIZE; ++i)  {
    printf("%s at[%i] is: %i\n", optnional_message, i, array[i] );
  }
}

int main()  {

  int array[ARRAY_SIZE] = {0};
  int reversed_array[ARRAY_SIZE] = {0};

  populate_a_array_with_user_input(array);

  show_elements_from_array(array, "First");

  reverse_a_array(array, reversed_array);

  show_elements_from_array(reversed_array, "Reversed");

  return(0);
}
