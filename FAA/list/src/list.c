#include "list.h"

static int
node_match(node_t *a, node_t *b)  {
  return strncmp(a->data, b->data, STRING_MAX);
}

head_t*
list_new() {
  head_t *self = NULL;
  if (!(self = (head_t *) malloc (sizeof (head_t))))
    return NULL;
  self->head = NULL;
  self->tail = NULL;
  self->match = node_match;
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
  ++list->length;
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
  ++list->length;
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


void
list_insert_at(head_t *list, node_t *node, const int index)  {
  if ( !node ) return NULL;
  if ( index > list->length ) return NULL;

  // First
  if ( !index ){
    list_lpush(list, node);
    return;
  }
  // Last
  if( index == list->length )  {
    list_rpush(list, node);
    return;
  }
  //Middle
  node_t *iterator = list->head;
  int idx = 0;

  while ( idx < index )  {
    iterator = iterator->next;
    ++idx;
  }

  node->next = iterator->next;
  node->prev = iterator;
  iterator->next = iterator->next->prev = node;
  ++list->length;
}

void
list_ordened_push(head_t *list, node_t *node)  {
  if (!node) return NULL;

  node_t *iterator = list->head;
  int index = 0;

  while ( index <= list->length ) {
    if( list->match(iterator, node) ){
      break;
    }

    iterator = iterator->next;
    ++index;
  }

  list_insert_at(list, node, index);
}

node_t*
list_find(head_t *list, const char *value)  {
  node_t *iterator = list->head;
  node_t *compare_to; compare_to = list_node_new();
  assign_data_to_node(compare_to, value);

  while ( iterator ) {
    if( list->match(iterator, compare_to) ){
      return iterator;
    }
    iterator = iterator->next;
  }
  return NULL;
}
