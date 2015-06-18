#include "list.h"
#include <string.h>

/*
 * Allocates a new airport_t. NULL on failure.
 * @param airport_name: the name of that airport
 */
airpot_t *
list_airport_new(const char *airport_name)
{
  airpot_t *self = NULL;
  if (!(self = (airpot_t *) LIST_MALLOC( sizeof(airpot_t) )))
    return NULL;
  size_t name_length = strlen(airport_name);
  self->airport_name = (char *) LIST_MALLOC (sizeof(char) * name_length);

  strncpy(self->airport_name, airport_name, name_length);

  self->flights = NULL;
  self->prev    = NULL;
  self->next    = NULL;
  return self;
}

/*
 * Allocates a new flight_t. NULL on failure.
 * @param uid: The flight UID
 * @param company_name: the company name
 */
flight_t *
list_flight_new(const int uid, const char *company_name)
{
  flight_t *self = NULL;
  if (!(self = (flight_t *) LIST_MALLOC( sizeof(flight_t) )))
    return NULL;
  self->flight_number = uid;
  size_t name_length  = strlen(company_name);
  self->company_name  =  (char *) LIST_MALLOC (sizeof(char) * name_length);

  strncpy(self->company_name, company_name, name_length);

  self->to    = NULL;
  self->next  = NULL;
  self->prev  = NULL;
  return self;
}
