#include "list.h"

iterator*
list_iterator_new(airports *airports, list_direction_t direction) {
  flight *flight = direction == LIST_HEAD ?
    airports->head : airports->tail;
  return list_iterator_new_form_node(flight, direction);
}

iterator*
list_iterator_new_form_node(flight *node, list_direction_t direction) {
  iterator *self = NULL;
  if(!(self = malloc(sizeof(iterator))))
    return NULL;

  self->next = node;
  self->direction = direction;
  return self;
}

flight*
list_iterator_next(iterator *self) {
  flight *current = self->next;
  if(current) {
    self->next = self->direction == list_head ? current->next : current->previous;
  }
  return current;
}

void
list_iterator_destroy(iterator *self) {
  free(self);
  self = NULL;
}
