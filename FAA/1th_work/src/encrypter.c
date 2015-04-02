#include "encrypter.h"

void remove_carriage_return_from_string(char *str)  {
  char *pos;
  if ((pos=strchr(str, '\n')) != NULL) *pos = '\0';
}

char* reader( char *message )  {
  char *str = NULL;
  char aux[BUFFER_LIMIT];

  printf("%s: ", message);
  __fpurge(stdin);
  fgets(aux, BUFFER_LIMIT, stdin);

  remove_carriage_return_from_string(aux);

  str = malloc(sizeof(char) * strlen(aux));

  strcpy(str, aux);

  return str;
}

int num_reader()  {
  int number;

  printf("Choose one: ");
  __fpurge(stdin); //wait for the prompt to be written on the screen
  scanf("%d",&number);

  return number;
}

int menu(){
  system("clear");
  printf("%s \n", greetings);
  printf("##                              ##\n");
  printf("              MENU                \n");
  printf("1 - Encrypt a file\n");
  printf("2 - Decrypt a file\n");
  printf("0 - Exit\n\n");

  return num_reader();
}

t_buffer* get_passwd()  {
  char *passwd = NULL;
  passwd = reader("Type the password");

  t_buffer *password = give_me_a_buffer( strlen(passwd) );
  assign_data_to_buffer( password, passwd );

  return password;
}

f_descriptors* get_files( )  {
  f_descriptors *files = NULL;
  files = give_me_a_f_descriptor( BUFFER_LIMIT );

  assign_fin( files, reader("Type the name of input file"));
  assign_fout( files, reader("Type the name of output file"));

  return files;
}

int main(int argc, char const *argv[])  {
  f_descriptors *files = NULL;
  t_buffer *password = NULL;
  int option = 1;

  while (option){
    option = menu();

    switch(option){
      case 1: {
        files = get_files();
        password = get_passwd();
        crypt_engine( files, password, ENCRYPT );

        // pause();
        break;
      }
      case 2: {

        files = get_files();
        password = get_passwd();
        crypt_engine( files, password, DECRYPT );

        // pause();
        break;
      }
    }
  }

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
  // char a = 'z';
  // char b= 'Z';

  // printf("%c\n", a);

  // unsigned char lol = rotate_carry_left_of_char(a, b);

  // printf("LEFT: %c | %d \n", lol, lol );

  // unsigned char olo = rotate_carry_rigth_of_char(lol, b);

  // printf("RIGTH: %c | %d \n", olo, olo );

  // int my_flag = 0;

  // t_buffer *a = give_me_a_chunk_from_file( "lol", 0, 1, &my_flag );

  // printf("# Data is: %s\n", a->data);

  // printf("Length of data is: %d \n", strlen(a->data));
  // printf("Associated length is: %d\n", a->current_legth);
  // printf("Allocated buffer size is: %d\n", a->allocated_size);

  // printf("The flag: %d\n", my_flag);

  // a = give_me_a_chunk_from_file( "lol", 3100, 3200, &my_flag );

  // printf("\n\n # Data is: %s\n", a->data);

  // printf("Length of data is: %d \n", strlen(a->data));
  // printf("Associated length is: %d\n", a->current_legth);
  // printf("Allocated buffer size is: %d\n", a->allocated_size);

  // printf("The flag: %d\n", my_flag);

  printf("Bye. See you son\n");

  return 0;
}
