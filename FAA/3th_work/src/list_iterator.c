#include "list.h"

// TODO:
// 1 - iterator for airports list
// 2 - iterator for flights list

/**
  Create a new iterator for the airport list
*/
airport_iterator *
list_airport_iterator_new(airports *self, list_direction_t direction) {
  airport *node = direction == LIST_HEAD
    ? self->head
    : self->tail;

  return list_airport_iterator_from_node(node, direction);
}

/**
  Create a new iterator for the airport list
  from a given node
*/
airport_iterator *
list_airport_iterator_from_node(airport *node, list_direction_t direction) {
  airport_iterator *self = NULL;
  if(!(self = (airport_iterator*) malloc( sizeof(airport_iterator) )))
    return NULL;

  self->next = node;
  self->direction = direction;
  return self;
}

/**
  Get the next node
*/
airport *
list_iterator_next_airport(airport_iterator *self) {
  airport *current = self->next;
  if(current) {
    self->next = self->direction == LIST_HEAD
      ? current->next
      : current->previous;
  }
  return current;
}

/**
  Destroy the iterator and free memory
*/
void
list_airport_iterator_destroy(airport_iterator *self) {
  free(self);
  self = NULL;
}

/**
  Create a new iterator for the flights list
*/
flight_iterator *
list_flight_iterator_new(flights *self, list_direction_t direction) {
  flight *node = direction == LIST_HEAD
    ? self->head
    : self->tail;

  return list_flight_iterator_from_node(node, direction);
}

/**
  Create a new iterator for the flight list
  from a given node
*/
flight_iterator *
list_flight_iterator_from_node(flight *node, list_direction_t direction) {
  flight_iterator *self = NULL;
  if(!(self = (flight_iterator*) malloc( sizeof(flight_iterator) )))
    return NULL;

  self->next = node;
  self->direction = direction;
  return self;
}

/**
  Get the next node
*/
flight *
list_iterator_next_flight(flight_iterator *self) {
  flight *current = self->next;
  if(current) {
    self->next = self->direction == LIST_HEAD
      ? current->next
      : current->previous;
  }
  return current;
}

/**
  Destroy the iterator and free memory
*/
void
list_flight_iterator_destroy(flight_iterator *self) {
  free(self);
  self = NULL;
}
