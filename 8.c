#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float check_discount(float fixed, float unit_price, int quantity)  {
  return fixed + (unit_price * quantity);
}

int main(int argc, char const *argv[]) {

  int quantity = 100;

  float criteria_A = 0.25;
  float fixed_A = 7.50;
  float criteria_B = 0.50;
  float fixed_B = 2.50;

  float A = check_discount(fixed_A, criteria_A, quantity);
  float B = check_discount(fixed_B, criteria_B, quantity);

  if (A == B)
  {
    printf("Both equals, A is %.3f and B is %.3f\n", A, B );
  }
  if(A < B){
    printf("A is the best option, A is %.3f and B is %.3f\n", A, B );
  }
  if (A > B)
  {
    printf("B is the best option, A is %.3f and B is %.3f\n", A, B );
  }

  return 0;
}
