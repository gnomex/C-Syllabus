#include "encrypter.h"

int main(int argc, char const *argv[])  {

  t_buffer *a = give_me_a_buffer(10);

  assign_data_to_buffer( a, "1234567891");

  printf("Data is: %s\n", a->data);

  printf("Length of data is: %d \n", strlen(a->data));
  printf("Associated length is: %d\n", a->current_legth);
  printf("Allocated buffer size is: %d\n", a->allocated_size);

  reverse_me( a->data );

  printf("Reversed is: %s\n", a->data);

  reverse_buffer_data(a);

  printf("Rollback: %s\n", a->data);

  free(a);

  return 0;
}
