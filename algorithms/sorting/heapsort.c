#include <stdio.h>

#define LENGTH 20
#define TM_PRINTF(f_, ...)  printf((f_), __VA_ARGS__)
#define PARENT(index)       ((index - 1) / 2)
#define LEFT(index)         ((2 *index) + 1)
#define RIGHT(index)        ((2 *index) + 2)

int heapSize;

// void SWAP(int *v, int i, int j) {
//   int x = v[i];
//   v[i] = v[j];
//   v[j] = x;
// }

// void sobe(int *h, int tam) {
//   int p, i = tam - 1;

//   while ( h[i] > h[ p = PARENT(i) ]) {
//     SWAP(h, i, p);
//     i = p;
//   }
// }

// void desce(int *h, int tam) {
//   int i,e,d;

//   i = 0;

//   while ( h[i] > h[e = LEFT(i)] ) {
//     SWAP(h, i, e);
//     i = e;
//   }
// }

// void remove_da_heap(int *h, int *tam) {
//   int x;

//   if (!(*tam)) return;

//   // arrumar ponteiros
//   x = h[0];
//   h[0] = h[--(*tam)];

//   desce(h, (*tam));
// }


// void insere_heap(int *h, int *tam, int x) {
//   //teste se tem espaço e insere no final
//   if (tam < LENGTH) h[(*tam)++] = x;

//   sobe(h, tam);
// }

void Heapify(int* A, int i) {
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  int largest;

  if(l <= heapSize && A[l] > A[i]) largest = l;
  else largest = i;

  if(r <= heapSize && A[r] > A[largest]) largest = r;

  TM_PRINTF("HEAPING heapSize[%d] l[%d] r[%d] largest[%d] \n", heapSize, r, l, largest);

  if(largest != i) {
      int temp = A[i];
      A[i] = A[largest];
      A[largest] = temp;

      Heapify(A, largest);
    }
}

void BuildHeap(int* A) {
  heapSize = LENGTH - 1;
  int i;

  for(i = (LENGTH - 1) / 2; i >= 0; i--)
    Heapify(A, i);
}


void printArray(char *str, int* array)  {
  int i;

  if (str != NULL) TM_PRINTF("%s", str);

  for (i = 0; i < LENGTH; i++) {
    TM_PRINTF("%d ", array[i]);
  }

  TM_PRINTF("\n", NULL);
}

int main() {

  int i;
  int array[LENGTH] = { 19, 18, 17, 16, 15, 14, 13, 12, 11, 20 ,1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  printArray("Original Array a: ", array);

  heapSize = 0;
  BuildHeap(array);

  TM_PRINTF("HEAP SIZE: %d\n", heapSize);

  printArray("full heap: ", array);

  for(i = LENGTH - 1; i > 0; i--) {
      int temp = array[heapSize];
      array[heapSize] = array[0];
      array[0] = temp;
      heapSize--;
      Heapify(array, 0);
  }

  printArray("sorted array: ", array);

  return 0;
}

