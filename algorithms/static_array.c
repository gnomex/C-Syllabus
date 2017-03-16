#include <stdio.h>

#define ARRAY_LENGTH 20

#define TM_PRINTF(f_, ...) printf((f_), __VA_ARGS__)

/* insertion sort like a bubble */
void insert(int *array, int *tam, int target) {
  int i;

  if (*tam < ARRAY_LENGTH) {
    for( i = *tam; *tam && (target < array[i - 1]); i--) array[i] = array[i - 1];

    array[i] = target;
    (*tam)++;
  }
}

void insert_recursive(int *array, int *tam, int target) {
  if (*tam >= ARRAY_LENGTH) return;

  (*tam)++;
  recursively_insert(array, *tam, target);
}

void recursively_insert(int *array, int tam, int target) {
  if( tam == 1 ) {
    array[0] = target;
    return;
  }

  if (target >= array[tam - 2]) array[tam - 1] = target;
  else {
    array[tam - 1] = array[tam - 2];
    recursively_insert(array, tam - 1, target);
  }
}


/*return the target index if found, otherwise return the list length */
int search(int *array, int tam, int target) {
  int i;

  for (i = 0; i < tam; i++) {
    if (array[i] == target) break;
  }

  return i;
}

int searchR(int *array, int tam, int target) {
  if (!tam) return 0;

  if (array[0] == target) return 0;

  return 1 + searchR(array + 1, tam - 1, target);
}

int search_from_tail(int *array, int tam, int b, int target) {
  if (b < 0) return tam;

  if (array[b] == target) return b;

  return search_from_tail(array, tam, b - 1, target);
}

/* find then remove */
void remove_element_from_list(int *array, int tam, int index) {
  array[index] = array[--tam];
}


void printArray(char *str, int* array)  {
  int i;

  if (str != NULL) TM_PRINTF("%s", str);

  for (i = 0; i < ARRAY_LENGTH; i++) {
    TM_PRINTF("%d ", array[i]);
  }

  TM_PRINTF("\n", NULL);
}

void test_desordered_elements(){
  int array[ARRAY_LENGTH] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int tam = 10;

  printArray("Original Array: ", array);

  TM_PRINTF("[search] Looking for 11, returned: %d\n", search(array, tam,  11));
  TM_PRINTF("[search] Looking for 1, returned: %d\n", search(array, tam,  1));
  TM_PRINTF("[search] Looking for 10, returned: %d\n", search(array, tam,  10));

  TM_PRINTF("[recursive search] Looking for 11, returned: %d\n", searchR(array, tam,  11));
  TM_PRINTF("[recursive search] Looking for 1, returned: %d\n", searchR(array, tam,  1));
  TM_PRINTF("[recursive search] Looking for 10, returned: %d\n", searchR(array, tam,  10));

  TM_PRINTF("[search recursive from tail] Looking for 11, returned: %d\n", search_from_tail(array, tam, tam, 11));
  TM_PRINTF("[search recursive from tail] Looking for 1, returned: %d\n", search_from_tail(array, tam, tam, 1));
  TM_PRINTF("[search recursive from tail] Looking for 10, returned: %d\n", search_from_tail(array, tam, tam, 10));
}

void test_sorted(){
  int array[ARRAY_LENGTH] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 12};
  int tam = 10;

  printArray("Original Array: ", array);

  insert(array, &tam, 11);
  printArray("added 11 to array: ", array);

  insert_recursive(array, &tam, 10);
  printArray("added 10 to array: ", array);

  TM_PRINTF("[search] Looking for 11, returned: %d\n", search(array, tam,  11));
  TM_PRINTF("[search] Looking for 1, returned: %d\n", search(array, tam,  1));
  TM_PRINTF("[search] Looking for 10, returned: %d\n", search(array, tam,  10));

  TM_PRINTF("[recursive search] Looking for 11, returned: %d\n", searchR(array, tam,  11));
  TM_PRINTF("[recursive search] Looking for 1, returned: %d\n", searchR(array, tam,  1));
  TM_PRINTF("[recursive search] Looking for 10, returned: %d\n", searchR(array, tam,  10));

  TM_PRINTF("[search recursive from tail] Looking for 11, returned: %d\n", search_from_tail(array, tam, tam, 11));
  TM_PRINTF("[search recursive from tail] Looking for 1, returned: %d\n", search_from_tail(array, tam, tam, 1));
  TM_PRINTF("[search recursive from tail] Looking for 10, returned: %d\n", search_from_tail(array, tam, tam, 10));
}


int main() {

  test_desordered_elements();

  test_sorted();

  return 0;
}
