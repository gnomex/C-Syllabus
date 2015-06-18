#include "list.h"

head_t*
list_new() {
  head_t *self = NULL;
  if (!(self = (head_t *) malloc (sizeof (head_t))))
    return NULL;
  self->head = NULL;
  self->tail = NULL;
  self->match = NULL;
  self->length = 0;
  return self;
}

void
list_destroyer(head_t *list)  {
  unsigned int len = list->length;
  node_t *next = NULL;
  node_t *curr = list->head;

  while (len--) {
    next = curr->next;
    free(curr);
    curr = next;
  }
  free(list);
}

/*
  Append the given node to the end of list
*/
void
list_rpush(head_t *list, node_t *node)  {
  if (!node) return NULL;

  if (list->length) {
    node->prev = list->tail;
    list->tail->next = node;
    list->tail       = node;
  } else {
    list->head = list->tail = node;
  }
}

/*
  Remove the node last node of list
*/
node_t*
list_rpop(head_t *list)  {
  if (!list->length) return NULL;

  node_t *node = list->tail;

  if(--list->length)  {
    (list->tail = node->prev)->next = NULL;
  } else {
    list->tail = list->head = NULL;
  }

  node->next = node->prev = NULL;
  return node;
}

/*
  Append the given node to the start of list
*/
void
list_lpush(head_t *list, node_t *node)  {
  if (!node) return NULL;

  if (list->length) {
    node->next = list->head;
    list->head->prev = node;
    list->head       = node;
  } else {
    list->head = list->tail = node;
  }
}

/*
  Remove the node first node of list
*/
node_t*
list_lpop(head_t *list)  {
  if (!list->length) return NULL;

  node_t *node = list->head;

  if(--list->length)  {
    (list->head = node->next)->prev = NULL;
  } else {
    list->tail = list->head = NULL;
  }

  node->next = node->prev = NULL;
  return node;
}
