#include "list.h"

node_t*
list_node_new() {
  node_t *self = NULL;
  if (!(self = (node_t *) malloc (sizeof (node_t))))
    return NULL;
  self->data   = (char *) malloc (sizeof(char) * STRING_MAX);
  self->length = STRING_MAX;
  self->used   = strlen(self->data);
  self->next   = NULL;
  self->prev   = NULL;
  return self;
}

void
assign_data_to_node(node_t *src, const char *data)  {
  size_t data_len = strlen(data);
  if ( data_len > STRING_MAX ) { data_len = STRING_MAX; }

  strncpy(src->data, data, data_len);
  src->used = data_len;
}
