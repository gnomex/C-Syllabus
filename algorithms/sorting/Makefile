CC=gcc
CFLAGS=-g -std=c99 -Wall -Wextra -O3 -fstack-protector -fstack-usage -ggdb -o

bubble: bubble_sort.c
	$(CC) $< $(CFLAGS) bubble.run

merge: mergesort.c
	$(CC) $< $(CFLAGS) merge_sort.run

heap: heapsort.c
	$(CC) $< $(CFLAGS) heap_sort.run

selection: selection_sort.c
	$(CC) $< $(CFLAGS) selection_sort.run

insertion: insertion_sort.c
	$(CC) $< $(CFLAGS) insertion_sort.run

quick: quick_sort.c
	$(CC) $< $(CFLAGS) quick_sort.run


all:

clean:
	rm -rf *.run *.su
