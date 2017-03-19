#include <stdio.h>

#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"

#define ROWS 5
#define COLS 5

#define TM_PRINTF(f_, ...) printf((f_), __VA_ARGS__)

void printa_matriz(int dados[ROWS][COLS], int x, int y) {
  int i, j;

  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++) {
      if (x != 0 && x == i && y != 0 && y == j ) TM_PRINTF(" %s%d%s ", RED, dados[i][j], RESET);
      else TM_PRINTF(" %d ", dados[i][j]);
    }
    TM_PRINTF("\n", NULL);
  }

  TM_PRINTF("----------------\n", NULL);
}

void printa(int m[ROWS][COLS], int i, int j, int cor, int fundo) {

  // TM_PRINTF("Received i[%d] j[%d] cor[%d] fundo[%d] \n", i, j, cor, fundo);

  printa_matriz(m, i, j);

  m[i][j] = cor;

  // cima
  if (i > 0 && m[i-1][j] == fundo) printa(m, i - 1, j, cor, fundo);
  // dir
  if (j < (COLS - 1) && m[i][j+1] == fundo) printa(m, i, j + 1, cor, fundo);
  // baixo
  if (j < (ROWS + 1) && m[i+1][j] == fundo) printa(m, i + 1, j, cor, fundo);
  // esq
  if (j < (COLS + 1) && m[i][j-1] == fundo) printa(m, i, j - 1, cor, fundo);
}


int main() {

  int a[ROWS][COLS] = {
    {0, 0, 2, 1, 1},
    {1, 0, 2, 0, 0},
    {1, 0, 0, 0, 2},
    {1, 0, 2, 0, 2},
    {1, 0, 0, 0, 1}
  };

  printa(a, 1, 1, 5, 0);

  return 0;
}
