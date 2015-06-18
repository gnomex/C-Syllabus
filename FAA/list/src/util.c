#include "list.h"

#define STRING_BUFFER 100

void
to_acsii_stream(node_t *node, const char *filename)  {
  FILE *stream = NULL;
  char *buffer = NULL;
  buffer = (char *) malloc (sizeof(char) * STRING_BUFFER);

  if( (stream = fopen( filename, "a")) )  {
    fputs("[length:", stream);
    sprintf(buffer, "%d", (int)node->length);
    fputs(buffer, stream);
    fputs(", used:", stream);
    sprintf(buffer, "%d", (int)node->used);
    fputs(buffer, stream);
    fputs(", data:", stream);
    fputs(node->data, stream);
    fputs("]\r", stream);

    fclose(stream);
  }
}

void
to_bin_stream(node_t *node, const char *filename)  {
  FILE *stream = NULL;

  if( (stream = fopen( filename, "a+b")) )  {
    fwrite(node, sizeof(node_t) + (sizeof(char) * STRING_MAX), 1, stream);

    fclose(stream);
  }
}

void
save_list_to_stream(head_t *list) {
  node_t *iterator = list->head;

  while ( iterator ) {
    to_acsii_stream(iterator, "list-ascii.stream");
    to_bin_stream(iterator, "list-bin.stream");

    iterator = iterator->next;
  }

}
