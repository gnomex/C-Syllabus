#include "lru.h"

int
buffer_equal(unsigned int *a, unsigned int *b) {
  return (a == b) ? 1 : 0;
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

  int i = 0;
  for (; i < list->len ; ++i) {
    unsigned char cast = a->val;

    printf("[%d] ASCII code: %d\n", i, cast);
    printf("[%d] ASCII char: %c\n", i, cast);
    a = list_iterator_next(it);;
  }

  list_iterator_destroy(it);
}

int
include(list_t *list, list_node_t *node)  {
  list_iterator_t *it = list_iterator_new(list, LIST_HEAD);
  list_node_t *a = list_iterator_next(it);;

  int i = 0;
  for (; i < list->len ; ++i) {
    if (a->val == node->val) {
      list_iterator_destroy(it);
      return 1;
    }
  }

  list_iterator_destroy(it);
  return 0;
}

void
add_to_buffer(list_t *buffer, list_node_t *content, stats_t *stats) {
  list_node_t *element = list_find(buffer, content->val);
  // int exists = include(buffer, content);

  ++stats->shots;

  if ( element != NULL ) {
  // if ( exists )  {
    ++stats->hits;
    // list_lpop(buffer);
    list_remove(buffer, element);
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
  printf("# Hits:%d\n# Miss: %d \n -> %d shots\n", stats->hits, stats->miss, stats->shots);
}

void
engine_yard(const char *phrase, list_t *list, stats_t *stats) {
  int i = 0;
  const int size = strlen(phrase);
  for (; i < size; ++i)  {
    unsigned int ch = phrase[i];
    add_to_buffer(list, list_node_new( ch ), stats);
  }
}


int
main(int argc, char const *argv[])
{
  list_t *list    = list_new();
  list_t *buffer  = list_new_with_limit(10);

  // list->match = buffer_equal;
  // buffer->match = buffer_equal;

  stats_t *buffer_stats = NULL;
  buffer_stats = (stats_t *) malloc (sizeof (stats_t));


  populate_static_list(list);
  // show_list(list);
  printf("## INFO\n");
  printf("list len: %d, list size: %d \n", list->len, list->max_size);
  printf("buffer len: %d, buffer size: %d \n", buffer->len, buffer->max_size);
  printf("## BYE\n");

  int option = 1;
  while (option){
    // system("clear");
    printf("##                              ##\n");
    printf("              MENU                \n");
    printf("1 - Enter a new phrase\n");
    printf("2 - Show current buffer\n");
    printf("3 - Resize buffer\n");
    printf("0 - Exit\n\n");

    option = num_reader();

    switch(option){
      case 1:
      {
        engine_yard(
            reader( "Hey Dude, type a phrase: " ),
            buffer,
            buffer_stats
          );

        show_stats(buffer_stats);

        wait_a_time();
        break;
      }
      case 2:
      {
        printf("buffer [now] len: %d, buffer size: %d \n", buffer->len, buffer->max_size);
        show_list(buffer);
        wait_a_time();
        break;
      }
      case 3:
      {
        break;
      }
    }
  }

  // populate_buffer(buffer, buffer_stats);

  // show_stats(buffer_stats);

  // printf("buffer [now] len: %d, buffer size: %d \n", buffer->len, buffer->max_size);
  // printf("list len: %d, list size: %d \n", list->len, list->max_size);

  list_destroy(list);
  list_destroy(buffer);

  return 0;
}


