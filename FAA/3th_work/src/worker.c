#include "list.h"
#include "file_util.h"

void
remove_carriage_return_from_string(char *str)  {
  char *pos = NULL;
  if ( (pos = strchr( str, '\n' )) != NULL ) *pos = '\0';
}

/**
  Read a string from stdin
  @param message: a message to display for a user
*/
char*
reader( char *message )  {
  char *str = NULL;
  char aux[STRING_MAX];

  printf("%s: ", message);
  __fpurge(stdin);
  fgets(aux, STRING_MAX, stdin);

  remove_carriage_return_from_string(aux);

  size_t str_lenght = strlen(aux);
  str = malloc(sizeof(char) * str_lenght);

  strncpy(str, aux, str_lenght);
  return str;
}

/**
  Read a number (formated string) from stdin
  @param message: a message to display for a user
*/
int
num_reader( char *message )  {
  int number;

  printf("%s: ", message);
  __fpurge(stdin); //wait for the prompt to be written on the screen
  scanf("%d",&number);
  return number;
}

static int
display(void) {
  printf(":=============================================================:\n"
         "| ANAC - Airports management and air control system.          |\n"
         "| 1 - Register airport.                                       |\n"
         "| 2 - Remove airport.                                         |\n"
         "| 3 - List all registered airports.                           |\n"
         "| 4 - Register flight.                                        |\n"
         "| 5 - Delete flight.                                          |\n"
         "| 6 - Interactive travel.                                     |\n"
         "| 7 - Export file.                                            |\n"
         "| 8 - Import flie.                                            |\n"
         "| 0 - Exit.                                                   |\n"
         ":=============================================================:\n");
  printf("$ ");
  return num_reader("Type an option: ");
}

int
main(int argc, char const *argv[]) {
  airports *airports_list = airports_list_new();
  char *filename = NULL;

   int option = 1;

   while(option) {
     option = display();
     switch(option) {
       case 1:
         collect_airport_data(airports_list);
         break;

       case 2:
        remove_airport_data(airports_list);
        break;

      case 3:
        list_and_show_airports_with_flights(airports_list);
        break;

      case 4:
        find_airport_and_create_a_fligth(airports_list);
        break;

      case 5:
        remove_a_flight_from_airport_get_uuid(airports_list);
        break;

      case 6:
        if(airports_list->length == 0){
          printf("No airports\n" );
          break;
        }

        interactive_travel(airports_list);

        break;

      case 7:
        list_to_stream(airports_list);
        break;

      case 8:
          filename = reader( "Type the file name: " );
          import_from_file(filename, airports_list);
        break;
      }
   }

  destroy_airports_list(airports_list);

  return 0;
}
