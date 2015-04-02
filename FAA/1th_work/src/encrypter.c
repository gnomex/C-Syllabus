#include "encrypter.h"

int main(int argc, char const *argv[])  {

  // printf("%s\n", greetings);

  // t_buffer *a = give_me_a_buffer(10);

  // assign_data_to_buffer( a, "1234567891");

  // printf("Data is: %s\n", a->data);

  // printf("Length of data is: %d \n", strlen(a->data));
  // printf("Associated length is: %d\n", a->current_legth);
  // printf("Allocated buffer size is: %d\n", a->allocated_size);

  // reverse_me( a->data );

  // printf("Reversed is: %s\n", a->data);

  // reverse_buffer_data(a);

  // printf("Rollback: %s\n", a->data);

  // read_the_file( a, "lol");


  // free(a);

  // unsigned char lol = rotate_carry_left_of_char(0xAF, 0xAF);

  // printf("LEFT: %c | %u \n", lol, lol );

  // unsigned char olo = rotate_carry_rigth_of_char(lol, 0xAF);

  // printf("RIGTH: %c | %u \n", olo, olo );

  int my_flag = 0;

  t_buffer *a = give_me_a_chunk_from_file( "lol", 0, 1, &my_flag );

  printf("# Data is: %s\n", a->data);

  printf("Length of data is: %d \n", strlen(a->data));
  printf("Associated length is: %d\n", a->current_legth);
  printf("Allocated buffer size is: %d\n", a->allocated_size);

  printf("The flag: %d\n", my_flag);

  a = give_me_a_chunk_from_file( "lol", 3100, 3200, &my_flag );

  printf("\n\n # Data is: %s\n", a->data);

  printf("Length of data is: %d \n", strlen(a->data));
  printf("Associated length is: %d\n", a->current_legth);
  printf("Allocated buffer size is: %d\n", a->allocated_size);

  printf("The flag: %d\n", my_flag);

  return 0;
}
