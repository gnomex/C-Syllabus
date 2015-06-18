#ifndef LIST
#define LIST

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define STRING_MAX 255

typedef struct _node {
  char *data;
  size_t length;
  size_t used;
  struct _node *next;
  struct _node *prev;
} node_t;

typedef struct {
  node_t *head;
  node_t *tail;
  int length;
  int (*match)(void *a, void *b);
} head_t;

#endif /* END_OF_LIST_H */
