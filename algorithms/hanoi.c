#include <stdio.h>


/*
  n: disks quantity
  from: starting tower
  to: final stacked tower
  using: temporary tower
*/
void hanoi(int n, int from, int to, int using) {
  if (n > 0) {
    hanoi(n-1, from, using, to);
    printf ("move %d --> %d\n", from, to);
    hanoi(n-1, using, to, from);
  }
}

int main(void) {

  hanoi(20, 1, 3, 2);

  return 0;
}
