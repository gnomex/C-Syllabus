#include "list.h"

void
destroy_airports_list(airports *self) {
  unsigned int length = self->length;

  airport *current = self->head;
  airport *next    = NULL;

  flights *current_list = current->fligths_list;

  while(length--) {
    next = current->next;

    destroy_fligth_list(current->flights_list);
    free(current->airport_name);
    free(current);
    current = next;
  }
  free(self);
}

void
destroy_fligth_list(flights *self)  {

}


flight *list_rpush(airports *self, flight *node) {
  if(!node) return NULL;

  if(self->length) {
    node->previous = self->tail;
    node->next = NULL;
    self->tail->next = node;
    self->tail = node;
  } else {
    self->head = self->tail = node;
    node->previous = node->next = NULL;
  }
  ++self->length;
  return node;
}

flight *list_rpop(airports *self) {
  if(!self->length) return NULL;

  flight *node = self->tail;

  if(--self->length) {
    (self->tail = node->previous)->next = NULL;
  } else {
    self->tail = self->head = NULL;
  }
  node->next = node->previous = NULL;
  return node;
}

flight *list_lpop(airports *self) {
  if(!self->length) return NULL;

  flight *node = self->head;
  if(--self->length) {
    (self->head = node->next)->previous = NULL;
  } else {
    self->head = self->tail = NULL;
  }
  node->next = node->previous = NULL;
  return node;
}

flight *list_lpush(airports *self, flight *node) {
  if(!node) return NULL;
  if(self->length) {
    node->next = self->head;
    node->previous = NULL;
    self->head->previous = node;
    self->head = node;
  } else {
    self->head = self->tail = node;
    node->previous = node->next = NULL;
  }
  ++self->length;
  return node;
}

flight *list_find(airports *self, void *value) {
  iterator *it = list_iterator_new(self, list_head);
  flight *node;
  while((node = list_iterator_next(it))) {
    if(self->match) {
      if(self->match(value, node->value)) {
        list_iterator_destroy(it);
        return node;
      }
    } else {
      if(value == node->value) {
        list_iterator_destroy(it);
        return node;
      }
    }
  }
  list_iterator_destroy(it);
  return NULL;
}

flight *list_at(airports *self, int index) {
  list_direction direction = list_head;
  if(index < 0) {
    direction = list_tail;
    index = ~index;
  }

  if((unsigned)index < self->length) {
    iterator *it = list_iterator_new(self, direction);
    flight *node = list_iterator_next(it);
    while(index--) node = list_iterator_next(it);
    list_iterator_destroy(it);
    return node;
  }
  return NULL;
}

void list_remove(airports *self, flight *node) {
  node->previous
    ? (node->previous->next = node->next)
    : (self->tail = node->previous);

  node->next
    ? (node->next->previous = node->previous)
    : (self->head = node->next);

  if(self->free) self->free(node->value);
  free(node);
  --self->length;
}
