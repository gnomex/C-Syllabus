#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int nlinhas;
  int ncolunas;
  int ncores;
  int **mapa;
} tmapa;

typedef struct {
  int quantidade;
  int *cores;
} tcor;

typedef struct {
  int max_plays;
  int last_index;
  int *plays;
} tplayed;

void reset_colours_histogram(tcor *cores) {
  int i;

  for (i = 0; i < cores->quantidade; i++ ){
    cores->cores[i] = 0;
  }
}

void initialize_game_play(tplayed *plays) {
  int i;

  plays->plays = (int*) malloc(plays->max_plays * sizeof(int));

  for (i = 0; i < plays->max_plays; i++ )
    plays->plays[i] = -1;
}

void inicializa_cores(tcor *cores) {
  cores->cores = (int*) malloc(cores->quantidade * sizeof(int));

  reset_colours_histogram(cores);
}

void imprime_cores(tcor *cores) {
  int i;

  for (i = 0; i < cores->quantidade; i++ ) {
    printf("[%d] %d, ", i, cores->cores[i] );
  }

  printf("\n");
}

void carrega_mapa(tmapa *m) {
  int i, j, r;

  r = scanf("%d", &(m->nlinhas));
  r = scanf("%d", &(m->ncolunas));
  r = scanf("%d", &(m->ncores));

  m->mapa = (int**) malloc(m->nlinhas * sizeof(int*));

  for(i = 0; i < m->nlinhas; i++) {
    m->mapa[i] = (int*) malloc(m->ncolunas * sizeof(int));
    for(j = 0; j < m->ncolunas; j++)
      r = scanf("%d", &(m->mapa[i][j]));
  }
}

void mostra_mapa(tmapa *m) {
  int i, j;

  for(i = 0; i < m->nlinhas; i++) {
    for(j = 0; j < m->ncolunas; j++)
      if(m->ncores > 10)
        printf("%02d ", m->mapa[i][j]);
      else
        printf("%d ", m->mapa[i][j]);

    printf("\n");
  }
}

void mostra_mapa_cor(tmapa *m) {
  int i, j;
  char* cor_ansi[] = { "\x1b[0m",
           "\x1b[31m", "\x1b[32m", "\x1b[33m",
           "\x1b[34m", "\x1b[35m", "\x1b[36m",
           "\x1b[37m", "\x1b[30;1m", "\x1b[31;1m",
           "\x1b[32;1m", "\x1b[33;1m", "\x1b[34;1m",
           "\x1b[35;1m", "\x1b[36;1m", "\x1b[37;1m" };

  if(m->ncores > 15) {
    mostra_mapa(m);
    return;
  }

  for(i = 0; i < m->nlinhas; i++) {
    for(j = 0; j < m->ncolunas; j++)
      if(m->ncores > 10)
        printf("%s%02d%s ", cor_ansi[m->mapa[i][j]], m->mapa[i][j], cor_ansi[0]);
      else
        printf("%s%d%s ", cor_ansi[m->mapa[i][j]], m->mapa[i][j], cor_ansi[0]);

    printf("\n");
  }
}

void update_stats_for(int cor, tcor *stats) {
  if (cor > 0 && cor <= stats->quantidade)
    stats->cores[(cor - 1)] += 1; // colour is 1..n, just do n - 1 to fit
}

/*
  Iterate recursively through lines (right and down only), looking for current color border
  When found, increment colour histrogram and return
*/
void heurisctic_right_down(tmapa *m, tcor *s, int l, int c, int fundo) {

  // Found the border
  if (!(l == 0 && c == 0) && m->mapa[l][c] != fundo) {
    update_stats_for(m->mapa[l][c], s); // update colour histogram
    return;
  }

  // right
  if(c < m->ncolunas - 1)
    heurisctic_right_down(m, s, l, c+1, fundo);

  // down
  if(l < m->nlinhas - 1)
    heurisctic_right_down(m, s, l+1, c, fundo);
}

/*
  Iterate through lines, looking for a different color
  if found, paint with it

  it's a keep right strategy, very fast, but makes many steps to finish
*/
void heurisctic_by_line(tmapa *m, tcor *s, int l, int c, int fundo) {
  int keepLooking = 1;
  int line, column;

  line = l;
  column = c;

  while (keepLooking) {
    if (!(line == 0 && column == 0) && m->mapa[line][column] != fundo) {
      update_stats_for(m->mapa[line][column], s);
      keepLooking = 0;
    }

    if ( column < m->ncolunas - 1 ) {
      column++;
    } else {
      if ( line < m->nlinhas - 1 ) {
        column = 0;
        line++;
      } else {
        keepLooking = 0;
      }
    }
  }
}

void pinta(tmapa *m, int l, int c, int fundo, int cor) {
  m->mapa[l][c] = cor;
  if(l < m->nlinhas - 1 && m->mapa[l+1][c] == fundo)
    pinta(m, l+1, c, fundo, cor);
  if(c < m->ncolunas - 1 && m->mapa[l][c+1] == fundo)
    pinta(m, l, c+1, fundo, cor);
  if(l > 0 && m->mapa[l-1][c] == fundo)
    pinta(m, l-1, c, fundo, cor);
  if(c > 0 && m->mapa[l][c-1] == fundo)
    pinta(m, l, c-1, fundo, cor);
}

void pinta_mapa(tmapa *m, int cor) {
  if(cor == m->mapa[0][0])
    return;
  pinta(m, 0, 0, m->mapa[0][0], cor);
}

void print_played_game(tplayed *plays) {
  int i;

  printf("%d\n", plays->last_index);

  for (i = 0; i < plays->max_plays; i++ ){
    if (plays->plays[i] == -1)
      break;

    printf("%d ", plays->plays[i] );
  }

  printf("\n");
}

/*
  Rank the best colour to play, based on color frequency registered on the histogram
*/
int rank_best_color_to_play(tcor *cores) {
  int i, j;

  j = 0; // first element

  // get highest (first) colour frequency
  for (i = 0; i < cores->quantidade; i++ ) {
    if (cores->cores[i] > cores->cores[j]) {
      j = i;
    }
  }

  return j + 1; // MUST return 1..n
}

// return false when ended
int not_yet_done(tmapa *map) {
  int i, j, c;

  c = map->mapa[0][0];

  for(i = 0; i < map->nlinhas; i++) {
    for(j = 0; j < map->ncolunas; j++) {
      if (map->mapa[i][j] != c)
        return 1; // if there is some different color, just return to play again
    }
  }

  return 0; // all board painted with same color
}

void add_step(tplayed *plays, int cor) {
  plays->plays[plays->last_index++] = cor;
}

int choose_strategy(int l_c_total) {
  return l_c_total > 225; // board greater than 15x15
}

int main(int argc, char **argv) {
  int cor;
  tmapa m;
  tcor cores;
  tplayed plays;
  int keepLooking = 1;
  int board_size;

  carrega_mapa(&m);

  cores.quantidade = m.ncores;
  plays.max_plays = 1024;
  plays.last_index = 0;
  board_size = m.ncolunas * m.nlinhas;

  inicializa_cores(&cores);
  initialize_game_play(&plays);

  // already done
  if (!not_yet_done(&m)) {
    printf("0\n");
    return 0;
  }

  if (choose_strategy( board_size )) {
    heurisctic_by_line(&m, &cores, 0,0, m.mapa[0][0]);
  } else {
    heurisctic_right_down(&m, &cores, 0,0, m.mapa[0][0]);
  }

  // rank best color to play
  cor = rank_best_color_to_play(&cores);

  // add "played" step
  add_step(&plays, cor);

  // reset histogram to further usage
  reset_colours_histogram(&cores);

  while (keepLooking) {
    // do the move
    pinta_mapa(&m, cor);

    if (not_yet_done(&m)) { // only if not already done. It's avoid last useless play

      if (choose_strategy( board_size )) {
        heurisctic_by_line(&m, &cores, 0,0, m.mapa[0][0]);
      } else {
        heurisctic_right_down(&m, &cores, 0,0, m.mapa[0][0]);
      }

      cor = rank_best_color_to_play(&cores);

      add_step(&plays, cor);
      reset_colours_histogram(&cores);
    } else {
      keepLooking = 0;
    }
  }

  // show game play statistics
  print_played_game(&plays);

  free(m.mapa);
  free(plays.plays);
  free(cores.cores);

  return 0;
}
