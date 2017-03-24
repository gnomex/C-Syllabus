#include <stdio.h>

/*
  T(1) = 1, if n <= 1
  T(n) = 1 + T(n-1) + T(n-2)
  O(n^2)
*/
long long int fibonacci(long long int n) { return n <= 1 ? 1 : fibonacci(n - 1) + fibonacci(n - 2); }


int main() {

  printf("fibonacci of 0 is %llu\n", fibonacci(0));
  printf("fibonacci of 1 is %llu\n", fibonacci(1));
  printf("fibonacci of 2 is %llu\n", fibonacci(2));
  printf("fibonacci of 3 is %llu\n", fibonacci(3));
  printf("fibonacci of 4 is %llu\n", fibonacci(4));
  printf("fibonacci of 5 is %llu\n", fibonacci(5));
  printf("fibonacci of 6 is %llu\n", fibonacci(6));
  printf("fibonacci of 10 is %llu\n", fibonacci(10));
  printf("fibonacci of 20 is %llu\n", fibonacci(20));
  printf("fibonacci of 30 is %llu\n", fibonacci(30));

  return 0;
}
