#include <stdio.h>

#define ARRAY_LENGTH 10
#define TM_PRINTF(f_, ...) printf((f_), __VA_ARGS__)

void merge(int *array, int a1, int b1, int a2, int b2) {
  int i,j,k;

  i = a1;
  j = a2;

  TM_PRINTF("merging a1[%d] b1[%d] a2[%d] b2[%d]\n", a1, b1, a2, b2);
  printArray("merging: ", array);

  for( k = 0; k <= b2; k++){

    if (i > b1) {
      TM_PRINTF("replace k[%d] : ak[%d] -> aj[%d] \n", k, array[k], array[j]);
      array[k] = array[j++];
    }
    else if (j > b2) {
      TM_PRINTF("replace k[%d] : ak[%d] -> ai[%d] \n", k, array[k], array[i]);
      array[k] = array[i++];
    }

    if (array[i] <= array[j])
      array[k] = array[i++];
    else
      array[k] = array[j++];
  }
}

void merge_sort(int *array, int a, int b) {
  int m;

  if (a >= b) {
    array[a] = array[b];
    return;
  }

  m = (a+b)/2;

  TM_PRINTF("M %d \n", m);

  merge_sort(array, a, m);
  merge_sort(array, m+1, b);

  merge(array, a, m, m+1, b);
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

  int a[ARRAY_LENGTH] = {9, 2, 1, 4, 8, 6, 7, 2, 3, 5};

  printArray("Original Array a: ", a);

  merge_sort(a, 0, ARRAY_LENGTH - 1);

  printArray("\n\nsorted a: ", a);

  return 0;
}
