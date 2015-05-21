#include "lru.h"

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


int
main(int argc, char const *argv[])
{
  list_t *list    = list_new();
  list_t *buffer  = list_new_with_limit(10);

  stats_t *buffer_stats = NULL;
  buffer_stats = (stats_t *) malloc (sizeof (stats_t));

  printf("buffer len: %d, buffer size: %d \n", buffer->len, buffer->max_size);
  printf("list len: %d, list size: %d \n", list->len, list->max_size);

  populate_static_list(list);
  // show_list(list);
  list_destroy(list);
  list_destroy(buffer);

  return 0;
}


