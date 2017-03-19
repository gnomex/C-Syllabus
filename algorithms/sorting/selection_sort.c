#include <stdio.h>

#define ARRAY_LENGTH 20

#define TM_PRINTF(f_, ...) printf((f_), __VA_ARGS__)



void printArray(char *str, int* array)  {
  int i;

  if (str != NULL) TM_PRINTF("%s", str);

  for (i = 0; i < ARRAY_LENGTH; i++) {
    TM_PRINTF("%d ", array[i]);
  }

  TM_PRINTF("\n", NULL);
}

int main() {

  int array[ARRAY_LENGTH] = { 19, 18, 17, 16, 15, 14, 13, 12, 11, 20 ,1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  printArray("Original Array: ", array);

  return 0;
}
