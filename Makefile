CC=gcc
CFLAGS = -g -Wall -o

1: 1.c
	$(CC) $(CFLAGS) exe1 1.c

2: 2.c
	$(CC) $(CFLAGS) exe2 2.c

3: 3.c
	$(CC) $(CFLAGS) exe3 3.c

4: 4.c
	$(CC) $(CFLAGS) exe4 4.c

5: 5.c
	$(CC) $(CFLAGS) exe5 5.c

6: 6.c
	$(CC) $(CFLAGS) exe6 6.c

7: 7.c
	$(CC) $(CFLAGS) exe7 7.c

8: 8.c
	$(CC) $(CFLAGS) exe8 8.c

9: 9.c
	$(CC) $(CFLAGS) exe9 9.c -lm

10: 10.c
	$(CC) $(CFLAGS) exe10 10.c -lm

11: 11.c
	$(CC) $(CFLAGS) exe11 11.c -lm

teste: teste.c
	$(CC) $(CFLAGS) teste_arrow teste.c

all: 1 2 3 4 5 6 7 8 9 10

clean:
	rm -rf exe*
