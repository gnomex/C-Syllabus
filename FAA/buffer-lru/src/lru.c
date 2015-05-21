#include "lru.h"

int
*buffer_equal(buffer_cmp *a, buffer_cmp *b) {
  // return 0 == strncmp(a->name, b->name, 1);
  return 0 == a->data == b->data;
}

void
populate_static_list(list_t *list){
  unsigned int i = ASCIIINIT;
  for (; i <= ASCIILIMIT; ++i) {
    list_rpush(list, list_node_new((int) i));
    // list_rpush(list, list_node_new((char) i));
  }
}

void
show_list(list_t *list) {
  list_iterator_t *it = list_iterator_new(list, LIST_HEAD);
  list_node_t *a = list_iterator_next(it);;

  printf("%i \n", a->val);

  int i = 0;
  for (; i < list->len ; ++i) {
    unsigned char cast = a->val;
    printf("#\ni: %i \n", a->val);
    printf("d: %d\n", cast);
    printf("c: %c\n", cast);
    a = list_iterator_next(it);;
  }

  list_iterator_destroy(it);
}

void
add_to_buffer(list_t *buffer, list_node_t *content, stats_t *stats) {
  list_node_t *element = list_find(buffer, content->val);

  if ( element != NULL ) {
    ++stats->hits;
    list_lpop(buffer);
    list_rpush(buffer, content);

  } else {
    ++stats->miss;

    if ( buffer->len >= buffer->max_size )
      list_lpop(buffer);

    list_rpush(buffer, content);
  }
}

void
populate_buffer(list_t *list, stats_t *stats){
  unsigned int i = 32;
  for (; i <= 50; ++i) {
    add_to_buffer(list, list_node_new((int) i), stats);
  }
}

void
show_stats(stats_t *stats)  {
  printf("# Hits:%d\n # Miss: %d \n\n", stats->hits, stats->miss);
}

int
main(int argc, char const *argv[])
{
  list_t *list    = list_new();
  list_t *buffer  = list_new_with_limit(10);

  // list->match = buffer_cmp;
  // buffer->match = buffer_cmp;

  stats_t *buffer_stats = NULL;
  buffer_stats = (stats_t *) malloc (sizeof (stats_t));


  populate_static_list(list);
  // show_list(list);

  printf("buffer len: %d, buffer size: %d \n", buffer->len, buffer->max_size);
  printf("list len: %d, list size: %d \n", list->len, list->max_size);


  populate_buffer(buffer, buffer_stats);

  show_stats(buffer_stats);

  printf("buffer [now] len: %d, buffer size: %d \n", buffer->len, buffer->max_size);
  printf("list len: %d, list size: %d \n", list->len, list->max_size);

  list_destroy(list);
  list_destroy(buffer);

  return 0;
}


