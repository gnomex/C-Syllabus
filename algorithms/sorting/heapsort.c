#include <stdio.h>

#define ARRAY_LENGTH 10
#define TM_PRINTF(f_, ...) printf((f_), __VA_ARGS__)


int pai(int i) {
  return (i-1)/2;
}

int esq(int i) {
  return 2*i + 1;
}

int dir(int i) {
  return 2*i + 2;
}

void troca(int *h, int i, int j) {
  int swap = h[i];
  h[i] = h[j];
  h[j] = swap;
}

void sobe(int *h, int tam) {
  int p, i = tam - 1;

  while ( h[i] > h[ p = pai(i) ]) {
    troca(h, i, p);
    i = p;
  }
}

void desce(int *h, int tam) {
  int i,e,d;

  i = 0;

  while ( h[i] > h[e = esq(i)] ) {

  }
}

void remove_da_heap(int *h, int tam) {
  int x;

  if (!tam) return -1;

  // arrumar ponteiros
  x = h[0];
  h[0] = h[--tam];

  desce(h, tam);
}


void insere_heap(int *h, int tam, int x) {
  //teste se tem espaço e insere no final
  if (tam < ARRAY_LENGTH) h[tam++] = x;

  sobe(h, tam);
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

  int a[ARRAY_LENGTH] = {0};

  printArray("Original Array a: ", a);

  return 0;
}
