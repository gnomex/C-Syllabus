#include "list.h"

/*
 * Allocates a new flight_t. NULL on failure.
 * @param uid: The flight UID
 * @param company_name: the company name
 */
flight*
list_flight_new(const int uid, const char *company_name)
{
  flight_t *self = NULL;
  if (!(self = (flight*) malloc( sizeof(flight) )))
    return NULL;

  self->flight_number = uid;
  size_t name_length  = strlen(company_name);
  self->company_name  =  (char *) malloc(sizeof(char) * name_length);

  strncpy(self->company_name, company_name, name_length);

  self->to    = NULL;
  self->next  = NULL;
  self->prev  = NULL;
  return self;
}
