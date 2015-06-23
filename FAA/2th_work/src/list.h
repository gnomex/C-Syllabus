#ifndef LIST
#define LIST

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LIST_VERSION "0.0.1"  // Library version
#define STRING_MAX 255        //

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
  flights *flights_list;
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
typedef struct {
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
  fligth *next;
  list_direction_t direction;
} fligth_iterator;


#endif /* END_OF_LIST_H */
