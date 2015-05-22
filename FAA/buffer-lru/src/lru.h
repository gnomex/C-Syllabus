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

int buffer_equal(unsigned int *a, unsigned int *b);
void populate_static_list(list_t *list);
void show_list(list_t *list);
int include(list_t *list, list_node_t *node);
void add_to_buffer(list_t *buffer, list_node_t *content, stats_t *stats);
void populate_buffer(list_t *list, stats_t *stats);
void show_stats(const char *message, stats_t *stats);
void lru_engine(
    list_node_t *content,
    list_t  *buffer,
    list_t  *list,
    stats_t *stats,
    stats_t *current_status
  );
void engine_yard(const char *phrase, list_t *buffer, list_t *list, stats_t *stats);

#endif /* END_OF_LRU */
