#include <stdio.h>

int
main (void)
{
unsigned short H, M, S; /* hora, minuto e segundo a serem lidos */
int T; /* sinalização do estado de leitura */

  do
    {
    do
      {
        /* leitura da informação horária */
        printf ("Informação horária HH:MM:SS? ");
        T = scanf ("%2hu:%2hu:%2hu", &H, &M, &S);
        scanf ("%*[^\n]");  /* descartar todos os outros caracteres */
        scanf ("%*c");      /* descartar o carácter fim de linha */
      } while (T != 3); /* repetir enquanto houver um erro de formato */

      printf("%d - %dh %dm %ds \n", T, H, M, S);
    } while ((H > 23) || (M > 59) || (S > 59));
  /* repetir enquanto houver valores fora dos limites */

  return 1;
}
