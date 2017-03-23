#include <stdio.h>

/*
  T(1) = 1, if n <= 1
  T(n) = 1 + T(n-1)
  O(n^2)
*/
long long int factorial(long long int n) { return n <= 1 ? 1 : n * factorial(n - 1); }

/*
  T(1) = 1
  T(n) = n + 3
  O(n)
*/
long long int factorial_iterative(int n) {
  long long int res = 1;
  int i;

  for(i = 1; i <= n; i++) {
      res *= i;
  }

  return res;
}



int main() {

  printf("factorial of 0 is %llu\n", factorial(0));
  printf("factorial of 1 is %llu\n", factorial(1));
  printf("factorial of 2 is %llu\n", factorial(2));
  printf("factorial of 3 is %llu\n", factorial(3));
  printf("factorial of 4 is %llu\n", factorial(4));
  printf("factorial of 5 is %llu\n", factorial(5));
  printf("factorial of 6 is %llu\n", factorial(6));
  printf("factorial of 10 is %llu\n", factorial(10));
  printf("factorial of 20 is %llu\n", factorial(20));
  printf("factorial of 30 is %llu\n", factorial(30));

  printf("factorial_iterative of 0 is %llu\n", factorial_iterative(0));
  printf("factorial_iterative of 1 is %llu\n", factorial_iterative(1));
  printf("factorial_iterative of 2 is %llu\n", factorial_iterative(2));
  printf("factorial_iterative of 3 is %llu\n", factorial_iterative(3));
  printf("factorial_iterative of 4 is %llu\n", factorial_iterative(4));
  printf("factorial_iterative of 5 is %llu\n", factorial_iterative(5));
  printf("factorial_iterative of 6 is %llu\n", factorial_iterative(6));
  printf("factorial_iterative of 10 is %llu\n", factorial_iterative(10));
  printf("factorial_iterative of 20 is %llu\n", factorial_iterative(20));
  printf("factorial_iterative of 30 is %llu\n", factorial_iterative(30));

  return 0;
}
