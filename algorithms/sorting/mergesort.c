/* Merge sort in C from https://gist.github.com/mycodeschool/9678029 */
#include <stdio.h>
#include <stdlib.h>

// #define ARRAY_LENGTH 10
#define TM_PRINTF(f_, ...) printf((f_), __VA_ARGS__)

// void merge(int *array, int a1, int b1, int a2, int b2) {
//   int i,j,k;
//   i = a1;
//   j = a2;
//   // TM_PRINTF("merging a1[%d] b1[%d] a2[%d] b2[%d]\n", a1, b1, a2, b2);
//   printArray("merging: ", array);
//   for( k = 0; k <= b2; k++){
//     if (i > b1) {
//       // TM_PRINTF("replace k[%d] : ak[%d] -> aj[%d] \n", k, array[k], array[j]);
//       array[k] = array[j++];
//     } else if (j > b2) {
//       // TM_PRINTF("replace k[%d] : ak[%d] -> ai[%d] \n", k, array[k], array[i]);
//       array[k] = array[i++];
//     }
//     if (array[i] <= array[j])
//       array[k] = array[i++];
//     else
//       array[k] = array[j++];
//   }
// }
// void merge_sort(int *array, int start, int end) {
//   int m;
//   if (start >= end) return;
//   m = (start + end)/2;
//   merge_sort(array, start, m);
//   merge_sort(array, m+1, end);
//   merge(array, start, m, m+1, end);
// }



// Function to Merge Arrays L and R into A.
// lefCount = number of elements in L
// rightCount = number of elements in R.
void Merge(int *A, int *L, int leftCount, int *R, int rightCount) {
  int i,j,k;

  // i - to mark the index of left aubarray (L)
  // j - to mark the index of right sub-raay (R)
  // k - to mark the index of merged subarray (A)
  i = 0; j = 0; k =0;

  while(i<leftCount && j< rightCount) {
    if(L[i]  < R[j]) A[k++] = L[i++];
    else A[k++] = R[j++];
  }
  while(i < leftCount) A[k++] = L[i++];
  while(j < rightCount) A[k++] = R[j++];
}

// Recursive function to sort an array of integers.
void MergeSort(int *A, int n) {
  int mid, i, *L, *R;

  if( n < 2 ) return; // base condition. If the array has less than two element, do nothing.

  mid = n / 2;  // find the mid index.

  // create left and right subarrays
  // mid elements (from index 0 till mid-1) should be part of left sub-array
  // and (n-mid) elements (from mid to n-1) will be part of right sub-array
  L = (int*) malloc( mid * sizeof(int) );
  R = (int*) malloc( (n - mid) * sizeof(int) );

  for( i = 0; i<mid; i++ ) L[i] = A[i]; // creating left subarray
  for( i = mid; i<n; i++ ) R[i-mid] = A[i]; // creating right subarray

  MergeSort(L,mid);  // sorting the left subarray
  MergeSort(R,n-mid);  // sorting the right subarray
  Merge(A,L,mid,R,n-mid);  // Merging L and R into A as sorted list.

  free(L);
  free(R);
}

void printArray(char *str, int* array, int size)  {
  int i;

  if (str != NULL) TM_PRINTF("%s", str);

  for (i = 0; i < size; i++) TM_PRINTF("%d ", array[i]);

  TM_PRINTF("\n", NULL);
}

int main() {

  int A[] = {9, 2, 1, 4, 8, 6, 7, 2, 3, 5, 6, 2, 3, 1, 9, 10, 15, 13, 12, 17};

  int numberOfElements;

  numberOfElements = sizeof(A)/sizeof(A[0]);

  printArray("Original Array: ", A, numberOfElements);

  MergeSort(A,numberOfElements);

  printArray("sorted Array: ", A, numberOfElements);

  return 0;
}
