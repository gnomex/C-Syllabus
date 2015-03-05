#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLUMNS 4
#define ROWS 4

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

char posix_reader() {
  char str;

  fflush(stdout); //wait for the prompt to be written on the screen
  scanf("%c",&str);

  return str;
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

  printf("__________________\n");

  for (; i < ROWS; i++)  {
    int j = 0;
    printf("|");
    for ( ; j < COLUMNS; j++)  {
      int e = matrix[i*COLUMNS +j];

      if (e == 0) {
        printf("  # ");
      } else if (e < 10){
        printf("  %d ", e );
      } else {
        printf(" %d ", e );
      }
    }
    printf("|\n");
  }

  printf("------------------\n");
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

int on_puzzle(int x, int y) {
    // Board limits: 0,0 | 4,0 | 0,4 | 4,4
  if ( (x >= 0) && (x < 4) && (y >= 0) && (y < 4) ) {
    return 1;
  }

  return 0;
}

void swap_on_puzzle(int *matrix, int x, int y, int new_x, int new_y)  {
  // aux = m[x1,y1]
  int aux = matrix[x*COLUMNS + y];
  // m[x1,y1] = m[x2,y2]
  matrix[x*COLUMNS + y] = matrix[new_x*COLUMNS + new_y];
  // m[x2,y2] = aux
  matrix[new_x*COLUMNS + new_y] = aux;
}

/* @Params
  *matrix - the puzzle
  arrow - the key pressed
  x,y - The location of # on puzzle

  @Return
  -1: Ilegal movment - Do nothing
  0: Out of the puzzle
  1: Ok - moved
*/
int make_movement_on_puzzle(int *matrix, int arrow, int x, int y) {

  if (on_puzzle(x,y)) {
    int is_valid = 0;
    int new_x = 0;
    int new_y = 0;

    switch(arrow){
    case UP :
      new_x = x - 1;
      new_y = y;
      is_valid = on_puzzle(new_x, new_y);
      break;
    case DOWN :
      new_x = x + 1;
      new_y = y;
      is_valid = on_puzzle(new_x, new_y);
      break;
    case RIGHT :
      new_x = x;
      new_y = y + 1;
      is_valid = on_puzzle(new_x, new_y);
      break;
    case LEFT :
      new_x = x;
      new_y = y - 1;
      is_valid = on_puzzle(new_x, new_y);
      break;
    }

    if (!is_valid)  {
      return -1;
    }

    swap_on_puzzle(matrix, x, y, new_x, new_y);

    return 1;
  }

  return 0;
}

int find_pivot(int *matrix, int *i_x, int *i_y) {
  int i = 0;

  for (; i < ROWS; i++)  {
    int j = 0;
    for ( ; j < COLUMNS; j++)  {
      if (matrix[i*COLUMNS +j] == 0)  {
        // printf("Found at: %i %i\n", i, j);
        *i_x = i;
        *i_y = j;

        return 1;
      }
    }
  }

  return 0;
}

// int insert(int number, int *array)  {
//   int i = 0;
//   int aux = 0;
//   int limit = COLUMNS * ROWS;

//   for ( ; i < limit; ++i)  {
//     aux = array[i * COLUMNS];

//     if (aux == number){
//       return 0;
//     }
//     if(aux == -1) {
//       aux = number;
//       return 1;
//     }
//   }
//   return 2;
// }


// void generate_random_array(int *sorted)  {
//   int aux = 0;

//   srand(time(NULL));

//   do{
//     aux = rand() % 15;
//   } while( insert(aux, sorted) != 2 ) ;
// }

// void sort_puzzle(int *puzzle) {
//   int i = 0;
// }

// int main(int argc, char const *argv[])
// {
//   int sorted[COLUMNS * ROWS];

//   int i = 0;
//   for (; i < 16; ++i) {
//     sorted[i] = -1;
//   }

//   generate_random_array(sorted);

//   i = 0;
//   for (; i < 16; ++i) {
//     printf("%i,", sorted[i]);
//   }

//   return 0;
// }


int main(int argc, char const *argv[])  {
  int valid_puzzle[ROWS][COLUMNS] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,0} };
  int puzzle[ROWS][COLUMNS] = { {5,6,7,0}, {9,10,11,12}, {1,2,3,4}, {13,14,15,8} };

  // show_multi_array(valid_puzzle);
  show_multi_array_ptr(&puzzle);

  char ch;
  int pivot_x = 0;
  int pivot_y = 0;

  // find_pivot(&puzzle, &pivot_x, &pivot_y);
  // show_multi_array_ptr(&puzzle);
  // printf("%i %i\n", pivot_x, pivot_y);

  do{
    find_pivot(&puzzle, &pivot_x, &pivot_y);

    ch = posix_reader();

    switch(ch){
    case 65 :
      make_movement_on_puzzle(&puzzle, UP, pivot_x, pivot_y); // ARGH!!! Check the return value!
      break;
    case 66 :
      make_movement_on_puzzle(&puzzle, DOWN, pivot_x, pivot_y);
      break;
    case 67 :
      make_movement_on_puzzle(&puzzle, RIGHT, pivot_x, pivot_y);
      break;
    case 68 :
      make_movement_on_puzzle(&puzzle, LEFT, pivot_x, pivot_y);
      break;
    case 'e' :
      return 0;
      break;
    }

    show_multi_array_ptr(&puzzle);

  } while ( !check_if_win(&valid_puzzle, &puzzle) );

  return 0;
}
