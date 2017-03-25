#include <stdio.h>

#define TM_PRINTF(f_, ...) printf((f_), __VA_ARGS__)

int partition(int *A, int p, int r){
  int i, j;
  i = p - 1;
  int x = A[r];

  for(j = p; j < r; j++){
    if(A[j] <= x){
      i++;
      int aux = A[i];
      A[i] = A[j];
      A[j] = aux;
    }
  }

  A[r] = A[i + 1];
  A[i + 1] = x;

  return i + 1;
}

void quick_sort(int *A, int p, int r){
  if(p < r){
    int q = partition(A,p,r);
    quick_sort(A,p, q - 1);
    quick_sort(A,q + 1,r);
  }
}

void printArray(char *str, int* array, int size)  {
  int i;

  if (str != NULL) TM_PRINTF("%s", str);

  for (i = 0; i < size; i++) TM_PRINTF("%d ", array[i]);

  TM_PRINTF("\n", NULL);
}


int main() {

  int A[] = {9, 2, 1, 4, 8, 6, 7, 2, 3, 5, 6, 2, 3, 1, 9, 10, 15, 13, 12, 17, 0, 99, 20};

  int numberOfElements = sizeof(A)/sizeof(A[0]);

  printArray("Original array: ", A, numberOfElements);

  quick_sort(A, 0, numberOfElements - 1);

  printArray("Sorted array: ", A, numberOfElements);

  return 0;
}
