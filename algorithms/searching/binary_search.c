#include <stdio.h>

#define ARRAY_LENGTH 20

#define TM_PRINTF(f_, ...) printf((f_), __VA_ARGS__)

int binary_search(int *array, int a, int b, int target) {
  int m, t;

  if (b < a) return -1; // index out of bounds: target not found

  m = (a + b) / 2;
  t = target - array[m];

  if (!t) return m; // found

  if (t > 0) return binary_search(array, m + 1, b, target);
  else return binary_search(array, a, m - 1, target);
}

void printArray(char *str, int* array)  {
  int i;

  if (str != NULL) TM_PRINTF("%s", str);

  for (i = 0; i < ARRAY_LENGTH; i++) {
    TM_PRINTF("%d ", array[i]);
  }

  TM_PRINTF("\n", NULL);
}

int main() {

  int array[ARRAY_LENGTH] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int tam = 10;

  printArray("Original Array: ", array);

  TM_PRINTF("[search] Looking for 11, returned: %d\n", binary_search(array,0, tam,  11));
  TM_PRINTF("[search] Looking for 1, returned: %d\n", binary_search(array,0, tam,  1));
  TM_PRINTF("[search] Looking for 10, returned: %d\n", binary_search(array,0, tam,  10));
  TM_PRINTF("[search] Looking for 9, returned: %d\n", binary_search(array,0, tam,  9));

  return 0;
}
