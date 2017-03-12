#include "list.h"
#include "colors.h"

int
enqueue_flight(flights *self, flight *node)  {
  // flight_iterator *it = list_flight_iterator_new(self, LIST_HEAD);
  // flight *node_it = NULL;

  list_flight_rpush(self, node);
  return 1;

  // if

  // while( (node_it = list_iterator_next_flight(it)) ) {
  //   if( strncmp(node_it->to, node->to, STRING_MAX) == 0 ) {
  //     printf("Same destiny... ");

  //     if(strncmp(node_it->company_name, node->company_name, STRING_MAX) == 0){
  //       list_flight_rpush(self, node);
  //       list_flight_iterator_destroy(it);
  //       return 1;
  //     }
  //   }
  // }
  // list_flight_iterator_destroy(it);
  // printf("%sATTENTION:%s This flight will fly to same airport, You can't!", RED, RESET);
  // return 0;
}

void
list_and_show_flights_from_airport(flights *self) {
  flight_iterator *it = list_flight_iterator_new(self, LIST_HEAD);
  flight *node = NULL;

  if (self->length == 0) {
    printf("[INFO] No flights yet\n");
    return;
  }

  while( (node = list_iterator_next_flight(it)) ) {
    printf("> to %s, number[%d], company %s \n", node->to, node->flight_number, node->company_name);
  }
  list_flight_iterator_destroy(it);
}

void
find_airport_and_create_a_fligth(airports *self)  {
  airport *air = NULL;
  air = find_airport_by_name(self);

  if (air == NULL) {
    printf("Airport not found\n");
    return;
  }

  return collect_flight_data(self, air);
}

int
collect_flight_data(airports *self, airport *origin) {
  char *destiny_airport = NULL;

  destiny_airport = reader("Enter the destiny airport: ");

  while(strlen(destiny_airport) != AIRPORT_STRING_LENGTH) {
    printf("%sATTENTION:%s The airport must be %d characters!\n", RED, RESET, AIRPORT_STRING_LENGTH);
    destiny_airport = reader("Enter the destiny airport: ");
  }

  char *company_name = NULL;
  flight *node = NULL;

  if( flight_to_airport(self, origin, destiny_airport ) != NULL ) {
    company_name = reader("Enter the company name: ");

    node = flight_node_new(uuid(), company_name);
    assing_flight_to(node, destiny_airport);

    printf("Airport found: %s\n", node->to);

    return enqueue_flight(origin->flights_list, node);
  }

  printf("%sATTENTION:%s Airport not found!\n", RED, RESET);
  return 0;
}

int
flight_to_airport(airports *self, airport *origin, char *to)  {
  airport *compare_to = NULL;
  compare_to = airport_node_new(to);

  airport *aux = NULL;
  aux = list_airport_find(self, compare_to);

  return (
    (aux != NULL) &&
    !(airport_match(aux, origin)) )
    ? 1
    : 0;
}

int
register_flight(flights *self, flight *node){
  return enqueue_flight(self, node);
}

/*
 * Compare two flights
 * @param a and b: the flight to match something
 * @rule: compare the flight UID
 * @return int defined by [ 0: "not equal", 1: "equals"]
 */
int
flight_match(flight *a, flight *b)  {
  return (a->flight_number == b->flight_number) ? 1 : 0;
}

int
flight_to_a_given_airport_match(flight *a, char *b){
  return (strncmp(a->to, b, STRING_MAX) == 0) ? 1 : 0;
}

// 0 - mesmo destino e diferentes companhias
// 1 - está ok
int
flight_company_to_same_airport_match(flight *a, flight *b)  {
  return (
    (strncmp(a->to, b->to, STRING_MAX) == 0) &&
    (strncmp(a->company_name, b->company_name, STRING_MAX) != 0) )
    ? 0
    : 1;
}

/*
 * Allocates a new flight. NULL on failure.
 * @param uid: The flight UID
 * @param company_name: the company name
 */
flight *
flight_node_new(const int uid, const char *company_name)  {
  flight *self = NULL;
  if (!(self = (flight*) malloc( sizeof(flight) )))
    return NULL;

  self->flight_number = uid;
  size_t name_length  = strlen(company_name);
  self->company_name  =  (char *) malloc(sizeof(char) * name_length);

  strncpy(self->company_name, company_name, name_length);

  self->to        = (char *) malloc(sizeof(char) * STRING_MAX);
  self->next      = NULL;
  self->previous  = NULL;
  return self;
}

void
assing_flight_to(flight *node, char *airport_name)  {
  strncpy(node->to, airport_name, strlen(airport_name));
}

/*
 * Allocates a new flight list. NULL on failure.
*/
flights *
flights_list_new() {
  flights *self = NULL;
  if(!(self = (flights*) malloc( sizeof(flights) )))
    return NULL;

  self->head   = NULL;
  self->tail   = NULL;
  self->match  = flight_match;
  self->length = 0;
  return self;
}

/*
  Append the given flight node to the end of list
  and return the node, NULL on failure.
*/
flight *
list_flight_rpush(flights *self, flight *node) {
  if(!node) return NULL;

  if(self->length) {
    node->previous   = self->tail;
    self->tail->next = node;
    self->tail       = node;
  } else {
    self->head = self->tail = node;
  }
  ++self->length;
  return node;
}

/*
  Remove the last flight node of the list
  and return the node, NULL on failure.
*/
flight *
list_flight_rpop(flights *self) {
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

/*
  Append the given flight node to the start of list
  and return the node, NULL on failure.
*/
flight *
list_flight_lpush(flights *self, flight *node) {
  if(!node) return NULL;

  if(self->length) {
    node->next           = self->head;
    self->head->previous = node;
    self->head           = node;
  } else {
    self->head = self->tail = node;
  }
  ++self->length;
  return node;
}

/*
  Remove the first flight node of the list
  and return the node, NULL on failure.
*/
flight *
list_flight_lpop(flights *self) {
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

/*
  Find an flight node on the list
  and return the node, NULL on failure.
*/
flight *
list_flight_find(flights *self, flight *compare_to) {
  flight_iterator *it = list_flight_iterator_new(self, LIST_HEAD);
  flight *node = NULL;

  while( (node = list_iterator_next_flight(it)) ) {
    if(self->match(node, compare_to)) {
      list_flight_iterator_destroy(it);
      return node;
    }
  }
  list_flight_iterator_destroy(it);
  return NULL;
}

int
give_a_new_uuid(flights *self)  {
  int number = uuid();

  while (!list_flight_find_uuid(self, number))  {
    number = uuid();
  }
  return number;
}

flight *
list_flight_find_by_uuid(flights *self, int uuid)  {
  flight_iterator *it = list_flight_iterator_new(self, LIST_HEAD);
  flight *node = NULL;

  while( (node = list_iterator_next_flight(it)) ) {
    if( node->flight_number == uuid ) {
      list_flight_iterator_destroy(it);
      return node;
    }
  }
  list_flight_iterator_destroy(it);
  return NULL;
}

int
list_flight_find_uuid(flights *self, int uuid)  {
  flight_iterator *it = list_flight_iterator_new(self, LIST_HEAD);
  flight *node = NULL;

  while( (node = list_iterator_next_flight(it)) ) {
    if( node->flight_number == uuid ) {
      list_flight_iterator_destroy(it);
      return 0;
    }
  }
  list_flight_iterator_destroy(it);
  return 1;
}

/*
  Return the flight node at the given index or NULL
*/
flight *
list_flight_at(flights *self, int index) {
  list_direction_t direction = LIST_HEAD;

  if(index < 0) {
    direction = LIST_TAIL;
    index = ~index;
  }

  if((unsigned)index < self->length) {
    flight_iterator *it = list_flight_iterator_new(self, direction);
    flight *node = list_iterator_next_flight(it);
    while(index--)
      node = list_iterator_next_flight(it);

    list_flight_iterator_destroy(it);
    return node;
  }
  return NULL;
}

void
remove_a_flight_from_airport_get_uuid(airports *self) {
  airport *origin = NULL;
  origin = find_airport_by_name(self);

  int number = num_reader("Type the flight number: ");

  flight *node = NULL;
  node = list_flight_find_by_uuid(origin->flights_list, number);

  if (node == NULL) {
    printf("flight %d not foun\n", number);
    return;
  }

  list_flight_remove(origin->flights_list, node);
}

void
remove_a_flight_from_airport_by_to(airport *self, char *to) {
  flight_iterator *it = list_flight_iterator_new(self->flights_list, LIST_HEAD);
  flight *node = NULL;

  while( (node = list_iterator_next_flight(it)) ) {
    if( strncmp(node->to, to, AIRPORT_STRING_LENGTH) == 0)  {
      list_flight_remove(self->flights_list, node);
      printf("REMOVED\n");
      break;
    }
  }
  list_flight_iterator_destroy(it);
}

void
remove_a_flight_from_airport(airport *self, int flight_number)  {
  flight *node = NULL;
  node = flight_node_new(flight_number, "doesnt matter");

  list_flight_remove_by_uuid(self->flights_list, node);
}

void
list_flight_remove_by_uuid(flights *self, flight *node) {
  flight *fl = NULL;
  fl = list_flight_find(self, node);
  if ( fl != NULL ) {
    list_flight_remove(self, node);
  }
}

/*
  Remove the given flight node of the flights list
*/
void
list_flight_remove(flights *self, flight *node) {
  printf("Removing flight %d\n", node->flight_number);
  node->previous
    ? (node->previous->next = node->next)
    : (self->tail = node->previous);

  node->next
    ? (node->next->previous = node->previous)
    : (self->head = node->next);

  free(node);
  --self->length;
}
