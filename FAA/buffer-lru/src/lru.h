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
} stats_t;

typedef struct {
  // char *name;
  int data;
} buffer_cmp;




#endif /* END_OF_LRU */
