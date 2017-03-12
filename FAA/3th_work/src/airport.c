#include "list.h"
#include "colors.h"
#include <ctype.h>

int
options(void) {
  printf(":=============================================================:\n"
         "| 1: Show available flights                                   :\n"
         "| 2: Select a fligth and travel                               :\n"
         "| 3: Show current airport                                     :\n"
         "| 0: exit                                                     :\n"
         ":=============================================================:\n");
  printf("$ ");
  return num_reader("Type an option: ");
}

void
interactive_travel(airports *self)  {
  list_and_show_airports_with_flights(self);

  airport *current = NULL;
  airport *aux = NULL;

  printf("##Choose the start airport\n\n");
  current = find_airport_by_name(self);

  int current_flight = 0;

  int option = 1;

  while(option) {
    option = options();
     switch(option) {
       case 1:
         list_and_show_flights_from_airport(current->flights_list);
         break;

       case 2:

       if(current->flights_list->length == 0){
        printf("No flights to travel, come back soon\n");
        break;
       }

        current_flight = num_reader("Type the flight number: ");
        aux = list_flight_find_by_uuid(current->flights_list, current_flight);

        if (aux != NULL)  {
          printf("Travelling\n");
          current_flight = aux;
        }

        break;

       case 3:
        printf("AIRPORT %s\n", current->airport_name);
        break;
      }
  }
}

/*
 * Compare two airports
 * @param a and b: the airport to match something
 * @rule: compare the airport name: int defined by [ <0: "a < b", 0: "equals", <0: "b > a" ]
 * @return true[1] or false[0]
 */
int
airport_match(airport *a, airport *b)  {
  return (strncmp(a->airport_name, b->airport_name, STRING_MAX) == 0) ? 1 : 0;
}

void
list_and_show_airports(airports *self) {
  airport_iterator *it = list_airport_iterator_new(self, LIST_HEAD);
  airport *node = NULL;

  printf("##\nSHOW AIPORTS\n-- Total %d registers\n", self->length );

  if ( self->length == 0 )  {
    printf("No airports to show\n");
    return;
  }

  while( (node = list_iterator_next_airport(it)) ) {
    printf("  Name: %s \n", node->airport_name );
  }
  list_airport_iterator_destroy(it);

  printf("##\n");
}

void
list_and_show_airports_with_flights(airports *self) {
  airport_iterator *it = list_airport_iterator_new(self, LIST_HEAD);
  airport *node = NULL;

  printf("##\nSHOW AIPORTS\n-- Total %d registers\n", self->length );

  if ( self->length == 0 )  {
    printf("No airports to show\n");
    return;
  }

  while( (node = list_iterator_next_airport(it)) ) {
    printf("From %s \n", node->airport_name );

    if(node->flights_list != NULL)  {
      list_and_show_flights_from_airport(node->flights_list);
    }
  }
  list_airport_iterator_destroy(it);

  printf("##\n");
}

int
remove_airport_data(airports *self) {
  airport *node = NULL;
  airport *aux = NULL;
  char *airport_name = NULL;
  airport_name = reader( "Enter the airport name" );

  while(strlen(airport_name) != AIRPORT_STRING_LENGTH) {
    printf("%sATTENTION:%s The airport name must be %d characters!\n", RED, RESET, AIRPORT_STRING_LENGTH);
     airport_name = reader( "Enter the airport name");
  }

  node = airport_node_new(airport_name);
  aux = list_airport_find(self, node);
  printf("Airport found: %s\n", node->airport_name );

  if (aux != NULL)  {
    remove_a_airport(self, node);
    printf("Removed!\n");
    return 1;
  }

  printf("Airport not found\n");
  return 0;
}

void
remove_a_airport(airports *self, airport *node)  {
  airport_iterator *it_air = list_airport_iterator_new(self, LIST_HEAD);
  airport *airport_node = NULL;

  while( (airport_node = list_iterator_next_airport(it_air)) ) {
    if(airport_node->flights_list->length != 0) {
      destroy_flight_list(airport_node->flights_list);
    }
  }

  list_airport_iterator_destroy(it_air);
  list_airport_node_remove(self, node);
  printf("[INFO] Airport and related flights removed!\n");
}


int
enqueue_airport(airports *self, airport *node)  {
  printf("Try to add %s\n", node->airport_name );
  if( list_airport_find(self, node) != NULL ) {
    printf("%sATTENTION:%s This airport already exist!", RED, RESET);
    return 0;
  }

  list_airport_rpush(self, node);
  return 1;
}

airport *
find_airport_by_name(airports *self)  {
  airport *node = NULL;
  char *airport_name = NULL;
  airport_name = reader( "Enter the airport name" );

  while(strlen(airport_name) != AIRPORT_STRING_LENGTH) {
    printf("%sATTENTION:%s The airport name must be %d characters!\n", RED, RESET, AIRPORT_STRING_LENGTH);
     airport_name = reader( "Enter the airport name");
  }

  node = airport_node_new(airport_name);

  return list_airport_find(self, node);
}

int
collect_airport_data(airports *self) {
  airport *node = NULL;
  char *airport_name = NULL;
  airport_name = reader( "Enter the airport name" );

  while(strlen(airport_name) != AIRPORT_STRING_LENGTH) {
    printf("%sATTENTION:%s The airport name must be %d characters!\n", RED, RESET, AIRPORT_STRING_LENGTH);
     airport_name = reader( "Enter the airport name");
  }

  node = airport_node_new(airport_name);

  return enqueue_airport(self, node);
}

/*
 * Allocates a new airport. NULL on failure.
 * @param airport_name: the name of that airport
 */
airport *
airport_node_new(const char *airport_name)  {
  airport *self = NULL;
  if(!(self = (airport*) malloc( sizeof(airport) )))
    return NULL;

  size_t name_length = strlen(airport_name);
  self->airport_name = (char*) malloc(sizeof(char) * name_length);

  strncpy(self->airport_name, airport_name, name_length);

  self->flights_list   = flights_list_new(); //Empty list
  self->previous       = NULL;
  self->next           = NULL;
  return self;
}

/*
 * Allocates a new airport list. NULL on failure.
*/
airports *
airports_list_new() {
  airports *self = NULL;
  if(!(self = (airports*) malloc( sizeof(airports) )))
    return NULL;

  self->head   = NULL;
  self->tail   = NULL;
  self->match  = airport_match;
  self->length = 0;
  return self;
}

/*
  Append the given airport node to the end of list
  and return the node, NULL on failure.
*/
airport *
list_airport_rpush(airports *self, airport *node) {
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
  Remove the last airport node of the list
  and return the node, NULL on failure.
*/
airport *
list_airport_rpop(airports *self) {
  if(!self->length) return NULL;

  airport *node = self->tail;

  if(--self->length) {
    (self->tail = node->previous)->next = NULL;
  } else {
    self->tail = self->head = NULL;
  }
  node->next = node->previous = NULL;
  return node;
}

/*
  Append the given airport node to the start of list
  and return the node, NULL on failure.
*/
airport *
list_airport_lpush(airports *self, airport *node) {
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
  Remove the first airport node of the list
  and return the node, NULL on failure.
*/
airport *
list_airport_lpop(airports *self) {
  if(!self->length) return NULL;

  airport *node = self->head;
  if(--self->length) {
    (self->head = node->next)->previous = NULL;
  } else {
    self->head = self->tail = NULL;
  }
  node->next = node->previous = NULL;
  return node;
}

/*
  Find an airport node on the list
  and return the node, NULL on failure.
*/
airport *
list_airport_find(airports *self, airport *compare_to) {
  airport_iterator *it = list_airport_iterator_new(self, LIST_HEAD);
  airport *node = NULL;

  while( (node = list_iterator_next_airport(it)) ) {
    if(self->match(node, compare_to)) {
      list_airport_iterator_destroy(it);
      return node;
    }
  }
  list_airport_iterator_destroy(it);
  return NULL;
}

/*
  Return the airport node at the given index or NULL
*/
airport *
list_airport_at(airports *self, int index) {
  list_direction_t direction = LIST_HEAD;

  if(index < 0) {
    direction = LIST_TAIL;
    index = ~index;
  }

  if((unsigned)index < self->length) {
    airport_iterator *it = list_airport_iterator_new(self, direction);
    airport *node = list_iterator_next_airport(it);
    while(index--)
      node = list_iterator_next_airport(it);

    list_airport_iterator_destroy(it);
    return node;
  }
  return NULL;
}

/*
  Remove the given airport node of the list, freeing the memory
  Only remove the node and assign the list chain
*/
void
list_airport_node_remove(airports *self, airport *node) {
  node->previous
    ? (node->previous->next = node->next)
    : (self->tail = node->previous);

  node->next
    ? (node->next->previous = node->previous)
    : (self->head = node->next);

  free(node);
  --self->length;
}
