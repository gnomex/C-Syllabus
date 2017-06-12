#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  int *plays;
} tplayed;

void reset_colours_histogram(tcor *cores) {
  int i;

  for (i = 0; i < cores->quantidade; i++ )
    cores->cores[i] = 0;
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

  for (i = 0; i < cores->quantidade; i++ )
    printf("%d ", cores->cores[i] );
}

void gera_mapa(tmapa *m, int semente) {
  int i, j;

  if(semente < 0)
    srand(time(NULL));
  else
    srand(semente);

  m->mapa = (int**) malloc(m->nlinhas * sizeof(int*));

  for(i = 0; i < m->nlinhas; i++) {
    m->mapa[i] = (int*) malloc(m->ncolunas * sizeof(int));

    for(j = 0; j < m->ncolunas; j++)
      m->mapa[i][j] = 1 + rand() % m->ncores;
  }
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

  printf("%d %d %d\n", m->nlinhas, m->ncolunas, m->ncores);

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

  printf("%d %d %d\n", m->nlinhas, m->ncolunas, m->ncores);

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
  if (cor >= 0 && cor < stats->quantidade)
    ++(stats->cores[cor]); // todo: it's right?
}

/*
primeiros 30% -> busca apenas nas bordas
60% -> busca com dois níveis
10% -> busca cega

*/
void procura_vizinhos(tmapa *m, tcor *s, int l, int c, int fundo) {

  if (m->mapa[l][c] != fundo)
    update_stats_for(m->mapa[l][c], s);

  if(l < m->nlinhas - 1 && m->mapa[l+1][c] == fundo)
    procura_vizinhos(m, s, l+1, c, fundo);

  if(c < m->ncolunas - 1 && m->mapa[l][c+1] == fundo)
    procura_vizinhos(m, s, l, c+1, fundo);

  if(l > 0 && m->mapa[l-1][c] == fundo)
    procura_vizinhos(m, s, l-1, c, fundo);

  if(c > 0 && m->mapa[l][c-1] == fundo)
    procura_vizinhos(m, s, l, c-1, fundo);
}

void pinta(tmapa *m, int l, int c, int fundo, int cor) {
  m->mapa[l][c] = cor;

  //
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

int rank_best_color_to_play(tcor *cores) {
  int i, j;

  j = 0; // first element

  // get highest colour frequency
  for (i = 1; i < cores->quantidade; i++ ) {
    if (cores->cores[j] < cores->cores[i]) {
      j = i;
    }
  }

  return j;
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
  int i;

  for (i = 0; i < plays->max_plays; i++ ) {
    if (plays->plays[i] != -1) {
      plays->plays[i] = cor;
      return;
    }
  }

  exit(5);
}

int main(int argc, char **argv) {
  int cor, r, semente;
  tmapa m;
  tcor cores;
  tplayed plays;

  if(argc < 4 || argc > 5) {
    printf("uso: %s <numero_de_linhas> <numero_de_colunas> <numero_de_cores> [<semente_aleatoria>]\n", argv[0]);
    exit(1);
  }

  m.nlinhas = atoi(argv[1]);
  m.ncolunas = atoi(argv[2]);
  m.ncores = atoi(argv[3]);
  plays.max_plays = 255;

  if(argc == 5)
    semente = atoi(argv[4]);
  else
    semente = -1;

  cores.quantidade = m.ncores;
  inicializa_cores(&cores);
  initialize_game_play(&plays);

  imprime_cores(&cores);

  gera_mapa(&m, semente);
  mostra_mapa_cor(&m);

  // faz histograma das bordas, candidato com mais cores tem preferencia
  // r = scanf("%d", &cor);
  // void procura_vizinhos(tmapa *m, tcor *s, int l, int c, int fundo, int cor) {
  procura_vizinhos(&m, &cores, 0,0, m.mapa[0][0]);
  // elege_melhor_cor
  r = rank_best_color_to_play(&cores);
  add_step(&plays, r);
  reset_colours_histogram(&cores);

  while (not_done_yet(&m)) {
    procura_vizinhos(&m, &cores, 0,0, m.mapa[0][0]);
    // elege_melhor_cor
    r = rank_best_color_to_play(&cores);
    add_step(&plays, r);
    reset_colours_histogram(&cores);

    pinta_mapa(&m, r);
    // mostra_mapa_cor(&m); // para mostrar sem cores use mostra_mapa(&m);
    mostra_mapa(&m);
  }

  // enquanto houverem cores diferentes
  // for (i=1; ainda_nao_terminou; i++)
  // while(cor > 0 && cor <= m.ncores) {
  //   pinta_mapa(&m, cor);
  //   mostra_mapa_cor(&m); // para mostrar sem cores use mostra_mapa(&m);

  //   // procura_vizinhos
  //   // elege_melhor_cor
  //   // registra cores e quantidade de movimentos
  //   r = scanf("%d", &cor);
  // }

  return 0;
}
