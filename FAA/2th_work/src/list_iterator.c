#include "list.h"

/*
 * Allocates a new airports_t. NULL on failure.
 */
airports_t *
new_airport_list()
{
  airports_t * self = NULL;
  if (!(self = (airports_t *) LIST_MALLOC(sizeof(airports_t))))
    return NULL;
  self->head  = NULL;
  self->tail  = NULL;
  self->free  = NULL;
  self->match = NULL;
  self->len   = 0;
  return self;
}
