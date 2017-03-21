#include <stdio.h>

#define ARRAY_LENGTH 20

#define TM_PRINTF(f_, ...) printf((f_), __VA_ARGS__)

/*
  Insert at the end and calls a sort algorithm
  O(n^2)
*/
int append_and_sort(int *array, int *tam, int element) {
  if (*tam >= ARRAY_LENGTH ) return -1;

  array[(*tam)++] = element;

  insertion_sort_partial_array(array, *tam);

  return 1;
}

/*
  Insertion sort starting from tail: open a 'space' and shift right the array. It's the clever strategy
  O(n^2)
*/
int insertion_sort_from_tail(int *array, int *tam, int element) {
  int i;

  if (*tam >= ARRAY_LENGTH - 1) return -1; // ensure enough space

  // empty array
  if (*tam == 0) {
    array[(*tam)++] = element;
    return 1;
  }

  for( i = *tam; i && (element < array[i - 1]); i--) array[i] = array[i - 1];

  array[i] = element;
  (*tam)++;

  return 1;
}

/*
  Classic insertion sort: find the element position and shift right the array
  O(n^2)
*/
void insertion_sort_from_front(int *array, int *tam, int element) {
  int i, j;

  if (*tam >= ARRAY_LENGTH - 1) return -1; // ensure enough space

  // empty array
  if (*tam == 0) {
    array[(*tam)++] = element;
    return 1;
  }

  // find the insertion position
  for (i = 0; array[i] < element && i < *tam; i++);

  // open a 'space' shifting right the array
  for (j = i; j < *tam; j++) array[j + 1] = array[j];

  // assign
  array[i] = element;
  (*tam)++;
  return 1;
}

/*
  remove an element without blank space, by shifting left the remaining elements
  O(n^2)
*/
int remove_element(int *array, int *tam, int element) {
  int i, j;

  // find the element
  for (i = 0; array[i] != element && i < *tam; i++);

  // shift left, replacing the element
  for (j = i; j < *tam; j++) array[j] = array[j+1];

  array[j+1] = NULL;
  (*tam)--;
  return i;
}

/*
  O(n^2)
*/
void insertion_sort_full_array(int array[ARRAY_LENGTH]) {
  int i, j, key;

  for (j = 1; j < ARRAY_LENGTH; j++) {
    key = array[j];
    i = j - 1;

    while (i >= 0 && array[i] > key) array[i + 1] = array[i--];

    array[i+1] = key;
  }
}

/*
  O(n^2)
*/
void insertion_sort_partial_array(int array[ARRAY_LENGTH], int length) {
  int i, j, key;

  if (length > ARRAY_LENGTH) return;

  for (j = 1; j < length; j++) {
    key = array[j];
    i = j - 1;

    while (i >= 0 && array[i] > key) array[i + 1] = array[i--];

    array[i+1] = key;
  }
}

/*
  O(n)
*/
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
  int array2[ARRAY_LENGTH] = { 19, 18, 15, 13, 20, 1, 3, 4, 7, 8, 9, 10 };
  int tam = 12;

  printArray("[full] Original Array: ", array);
  insertion_sort_full_array(array);
  printArray("[full] sorted Array: ", array);

  printArray("[partial] Original Array: ", array2);
  insertion_sort_partial_array(array2, tam);
  printArray("[partial] sorted Array: ", array2);

  append_and_sort(&array2, &tam, 99);
  printArray("added 99 to Array: ", array2);

  insertion_sort_from_tail(&array2, &tam, 0);
  printArray("added 0 to Array: ", array2);

  insertion_sort_from_front(&array2, &tam, 100);
  printArray("added 100 to Array: ", array2);

  TM_PRINTF("Removed 0 from i[%d]", remove_element(&array2, &tam, 0));
  printArray("Removed 0 from Array: ", array2);


  return 0;
}
