#ifndef LRU
#define LRU

#include <stdint.h>
#include "list.h"

// ASCII printable symbols 32...127 or the extended to 255
#define ASCIIINIT  32
#define ASCIILIMIT 127

typedef struct {
  int hits;
  int miss;
  int shots;
} stats_t;

extern void remove_carriage_return_from_string(char *str);
extern char* reader( char *message );
extern int num_reader();
extern void wait_a_time();

#endif /* END_OF_LRU */
