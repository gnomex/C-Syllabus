#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 4
#define ROWS 4

int posix_reader(char *str)  {
  int number;

  printf("Digit the %s: ", str);
  fflush(stdout); //wait for the prompt to be written on the screen
  scanf("%d",&number);

  return number;
}

void show_multi_array(int matrix[ROWS][COLUMNS]) {
  int i = 0;
  for (; i < ROWS; i++)  {
    int j = 0;

    for ( ; j < COLUMNS; j++)  {
      printf("[Row: %i][Column: %i] -> {%d} \n", i, j, matrix[i][j] );
    }
  }
}

void show_multi_array_ptr(int *matrix) {
  int i = 0;
  for (; i < ROWS; i++)  {
    int j = 0;

    for ( ; j < COLUMNS; j++)  {
      printf("[Row: %i][Column: %i] -> {%d} \n", i, j, matrix[i*COLUMNS +j] );
    }
  }
}

/* @Returns:
  0 for false
  1 to true
*/
int check_if_win(int *valid, int *to_compare) {
  int i = 0;

  for (; i < ROWS; i++)  {
    int j = 0;

    for ( ; j < COLUMNS; j++)  {

      if (to_compare[i*COLUMNS +j] != valid[i*COLUMNS +j])  {
        return 0;
      }
    }
  }
  return 1;
}

int main(int argc, char const *argv[])  {
  int valid_puzzle[ROWS][COLUMNS] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,0} };
  int puzzle[ROWS][COLUMNS];

  // show_multi_array(valid_puzzle);

  // show_multi_array_ptr(&valid_puzzle);

  return 0;
}
