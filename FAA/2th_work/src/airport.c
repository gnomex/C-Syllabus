#include "list.h"

static int
airport_match(airport *a, airport *b)  {
  return strncmp(a->airport_name, b->airport_name, STRING_MAX);
}

/*
 * Allocates a new airport. NULL on failure.
 * @param airport_name: the name of that airport
 */
airport*
list_airport_new(const char *airport_name)  {
  airport *self = NULL;
  if(!(self = (airport*) malloc( sizeof(airport) )))
    return NULL;

  size_t name_length = strlen(airport_name);
  self->airport_name = (char*) malloc(sizeof(char) * name_length);

  strncpy(self->airport_name, airport_name, name_length);

  self->flights_list   = NULL;
  self->previous       = NULL;
  self->next           = NULL;
  return self;
}

/*
 * Allocates a new airport list. NULL on failure.
*/
airports*
list_new() {
  airports *self = NULL;
  if(!(self = (airports*) malloc( sizeof(airports) )))
    return NULL;

  self->head   = NULL;
  self->tail   = NULL;
  self->match  = airport_match;
  self->length = 0;
  return self;
}
