#ifndef LIST
#define LIST

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

// Library version

#define LIST_VERSION "0.0.1"

// Memory management macros
#ifndef LIST_MALLOC
#define LIST_MALLOC malloc
#endif

#ifndef LIST_FREE
#define LIST_FREE free
#endif

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

typedef struct _airpot  {
  char *airport_name;
  struct _flight *flights;
  struct _airport *prev;
  struct _airport *next;
} airpot_t;

/*
  Flight node
*/

typedef struct _flight  {
  unsigned int flight_number;
  char *company_name;
  airpot_t *to;
  struct _flight *next;
  struct _flight *prev;
} flight_t;

/*
  Airports and flights list
*/

typedef struct {
  airpot_t *head;
  airpot_t *tail;
  unsigned int len;
  void (*free)(void *val);
  int (*match)(void *a, void *b);
} airports_t;

/*
  Airport Iterator
*/

typedef struct {
  airpot_t *next;
  list_direction_t direction;
} list_iterator_t;

#ifdef __cplusplus
}
#endif

#endif /* END_OF_LIST_H */
