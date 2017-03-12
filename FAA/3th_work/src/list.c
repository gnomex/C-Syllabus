#include "list.h"

void
destroy_airports_list(airports *self) {
  unsigned int length = self->length;

  airport *current = self->head;
  airport *next    = NULL;

  flights *current_flight_list = current->flights_list;

  while(length--) {
    next = current->next;
    destroy_flight_list(current_flight_list);
    free(current->airport_name);
    free(current);
    current = next;
  }
  free(self);
}

void
destroy_flight_list(flights *self)  {
  unsigned int length = self->length;

  flight *current = self->head;
  flight *next    = NULL;

  while(length--){
    next = current->next;
    free(current->company_name);
    free(current->to);
    free(current);
    current = next;
  }
  free(self);
}

//generate a randon number for flight number
int
uuid()  {
  int limit = 30000;
  int divisor = RAND_MAX/(limit+1);
  int retval;

  do {
      retval = rand() / divisor;
  } while (retval > limit);

  return retval;
}

