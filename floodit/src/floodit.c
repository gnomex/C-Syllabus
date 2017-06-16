#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOG(f_, ...) printf((f_), __VA_ARGS__)

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
  Most important method
*/
void procura_vizinhos(tmapa *m, tcor *s, int l, int c, int fundo) {

  if (!(l == 0 && c == 0) && m->mapa[l][c] != fundo) {
    update_stats_for(m->mapa[l][c], s);
    return;
  }

  // right
  if(c < m->ncolunas - 1)
    procura_vizinhos(m, s, l, c+1, fundo);

  // down
  if(l < m->nlinhas - 1)
    procura_vizinhos(m, s, l+1, c, fundo);
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
}

int rank_best_color_to_play(tcor *cores) {
  int i, j;

  j = 0; // first element

  // get highest colour frequency
  for (i = 0; i < cores->quantidade; i++ ) {
    if (cores->cores[i] > cores->cores[j]) {
      j = i;
    }
  }

  return j + 1; // MUST return 1..n
}

// return false when ended, otherwise true
int not_done_yet(tmapa *map) {
  int i, j, c;

  c = map->mapa[0][0];

  for(i = 0; i < map->nlinhas; i++) {
    for(j = 0; j < map->ncolunas; j++) {
      if (map->mapa[i][j] != c)
        return 1;
    }
  }

  return 0;
}

void add_step(tplayed *plays, int cor) {
  // LOG("next color is %d\n", cor);
  plays->plays[plays->last_index++] = cor;
}

int main(int argc, char **argv) {
  int cor;
  tmapa m;
  tcor cores;
  tplayed plays;

  carrega_mapa(&m);

  cores.quantidade = m.ncores;
  plays.max_plays = 1024;
  plays.last_index = 0;

  inicializa_cores(&cores);
  initialize_game_play(&plays);

  // already done
  if (!not_done_yet(&m)) {
    printf("0\n");
    return;
  }

  procura_vizinhos(&m, &cores, 0,0, m.mapa[0][0]);
  // elege_melhor_cor
  cor = rank_best_color_to_play(&cores);

  add_step(&plays, cor);

  reset_colours_histogram(&cores);

  while (not_done_yet(&m)) {
    pinta_mapa(&m, cor);
    // mostra_mapa_cor(&m);

    procura_vizinhos(&m, &cores, 0,0, m.mapa[0][0]);
    // elege_melhor_cor
    // não precisa se já terminou!
    cor = rank_best_color_to_play(&cores);

    add_step(&plays, cor);
    reset_colours_histogram(&cores);
  }

  print_played_game(&plays);

  free(m.mapa);
  free(plays.plays);
  free(cores.cores);

  return 0;
}
