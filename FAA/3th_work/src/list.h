#ifndef LIST
#define LIST

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdio_ext.h>

#define LIST_VERSION "0.1.1"  // Library version
#define STRING_MAX 255        //
#define AIRPORT_STRING_LENGTH 3

/*
  list_t iterator direction.
*/
typedef enum {
    LIST_HEAD
  , LIST_TAIL
} list_direction_t;

/*
  Airport node
*/
typedef struct _airport {
  char *airport_name;
  struct _airport *next;
  struct _airport *previous;
  struct _flights *flights_list;
} airport;

/*
  Flight node
*/
typedef struct _flight {
  unsigned int flight_number;
  char *company_name;
  char *to;
  struct _flight *next;
  struct _flight *previous;
} flight;

/*
  Airports and flights list
*/
typedef struct {
  airport *head;
  airport *tail;
  unsigned int length;
  int (*match)(void *, void *b);
} airports;

/*
  Flights list
*/
typedef struct _flights {
  flight *head;
  flight *tail;
  unsigned int length;
  int (*match)(void *, void *b);
} flights;

/*
  Airports Iterator
*/
typedef struct {
  airport *next;
  list_direction_t direction;
} airport_iterator;


/*
  Fligths Iterator
*/
typedef struct {
  flight *next;
  list_direction_t direction;
} flight_iterator;


/**
  Functions prototype
*/
//Iterator
airport_iterator* list_airport_iterator_new(airports *self, list_direction_t direction);
airport_iterator* list_airport_iterator_from_node(airport *node, list_direction_t direction);
airport* list_iterator_next_airport(airport_iterator *self);
void list_airport_iterator_destroy(airport_iterator *self);
flight_iterator* list_flight_iterator_new(flights *self, list_direction_t direction);
flight_iterator* list_flight_iterator_from_node(flight *node, list_direction_t direction);
flight* list_iterator_next_flight(flight_iterator *self);
void list_flight_iterator_destroy(flight_iterator *self);
//Airport list
int airport_match(airport *a, airport *b);
airports* airports_list_new();
airport* airport_node_new(const char *airport_name);
airport* list_airport_rpush(airports *self, airport *node);
airport* list_airport_rpop(airports *self);
airport* list_airport_lpush(airports *self, airport *node);
airport* list_airport_lpop(airports *self);
airport* list_airport_find(airports *self, airport *compare_to);
airport* list_airport_at(airports *self, int index);
void list_airport_node_remove(airports *self, airport *node);
//Flight list
int flight_match(flight *a, flight *b);
flights* flights_list_new();
flight* flight_node_new(const int uid, const char *company_name);
flight* list_flight_rpush(flights *self, flight *node);
flight* list_flight_rpop(flights *self);
flight* list_flight_lpush(flights *self, flight *node);
flight* list_flight_lpop(flights *self);
flight* list_flight_find(flights *self, flight *compare_to);
flight* list_flight_at(flights *self, int index);
void list_flight_remove(flights *self, flight *node);
//list
void destroy_airports_list(airports *self);
void destroy_flight_list(flights *self);
//Worker
char* reader( char *message );
void remove_carriage_return_from_string(char *str);
int num_reader( char *message );


airport* find_airport_by_name(airports *self);

#endif /* END_OF_LIST_H */
