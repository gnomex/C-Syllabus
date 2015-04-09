#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void do_nothing(double value)  {
  double brazilian_current[12] = { 100.0, 50.0, 20.0, 10.0, 5.0, 2.0, 1.0, 0.50, 0.25, 0.10, 0.05, 0.01};
  int array_size = 12;

  printf("Calculating cash notes, amount: %.3f\n", value);

  int i = 0;
  for (; i < array_size; ++i)  {
    double base = brazilian_current[i];
    double quotient = trunc(value / base);

    printf("Real value: %.2f, we'll give you %.0f cash notes\n", base, quotient);
    value = fmod(value, base);
    // printf("%.3f\n", value);
  }

  if (value > 0.001)  {
    printf("\nOw no, missed %.2f cents... Do you accept a lollipop?\n\n", value);
  }
}

int main(int argc, char const *argv[]) {

  do_nothing(99.60);

  return 0;
}
