#include "file_util.h"

void
fligth_to_ascii_stream(
    flight *node
  , const char *air_origin
  , const char *filename)
{
  FILE *stream = NULL;
  char *buffer = NULL;
  buffer = (char *) malloc (sizeof(char) * STRING_MAX);

  if( (stream = fopen( filename, "a")) )  {
    fputs(CAD_V, stream);
    sprintf(buffer, " %s ", air_origin);
    fputs(buffer, stream);
    sprintf(buffer, " %s ", node->to);
    fputs(buffer, stream);
    sprintf(buffer, " %d ", (int)node->flight_number);
    fputs(buffer, stream);
    sprintf(buffer, " %s ", node->company_name);
    fputs(buffer, stream);
    fputs("\r", stream);

    fclose(stream);
  }
}

void
airport_to_ascii_stream(airport *node, const char *filename)  {
  FILE *stream = NULL;
  char *buffer = NULL;
  buffer = (char *) malloc (sizeof(char) * STRING_MAX);

  if( (stream = fopen( filename, "a")) )  {
    fputs(CAD_A, stream);
    sprintf(buffer, " %s", node->airport_name);
    fputs(buffer, stream);
    fputs("\r", stream);

    fclose(stream);
  }
}

//import data from text file
void
import_from_file(const char *filename, airports *self)  {
  FILE *stream = NULL;
  char *buffer = NULL;

  if( (stream = fopen( filename, "r")) )  {
    while ( !feof(stream) ) {
      buffer = (char *) malloc (sizeof(char) * STRING_MAX);

      fgets(buffer, STRING_MAX, stream);
      remove_carriage_return_from_string(buffer);
      command_string_processor(buffer, self);

      free(buffer);
      buffer = NULL;
    }

    fclose(stream);
  }
}

// receive a raw string and do something
void
command_string_processor(char *command, airports* self)  {
  char *rest = NULL; // to point to the rest of the string after token extraction.
  char *token = NULL; // to point to the actual token returned.

  token = strtok_r(command, " ", &rest);
  command = rest;

  // trim_whitespace()

  if(strncmp(token, CAD_A, 13) == 0){
    printf("CAD AEROPORTO: %s\n", rest);
    airport* node = NULL;
    node = airport_node_new(rest);
    enqueue_airport(self, node);
    return;
  }

  if(strncmp(token, CAD_V, 7) == 0){
    printf("CAD VOO: %s\n", rest);

    token = strtok_r(command, " ", &rest); //origin
    command = rest;
    // printf("TOKEN[%s] REST[%s]\n", token, rest );

    airport *origin = NULL;
    origin = airport_node_new(token);
    airport *aux = NULL;
    aux = list_airport_find(self, origin);

    token = strtok_r(command, " ", &rest); //to
    command = rest;
    // printf("TOKEN[%s] REST[%s]\n", token, rest );

    char *destiny_airport = NULL;
    destiny_airport = (char *) malloc(sizeof(char) * STRING_MAX);
    strncpy(destiny_airport, token, strlen(token));

    token = strtok_r(command, " ", &rest); //flight number
    command = rest;
    // printf("TOKEN[%s] REST[%s]\n", token, rest );
    // int uuid = atoi(token);
    int uuid = randomized();

    token = strtok_r(command, " ", &rest); //company
    command = rest;
    // printf("TOKEN[%s] REST[%s]\n", token, rest );
    char *company = NULL;
    company = (char *) malloc(sizeof(char) * STRING_MAX);
    strncpy(company, token, strlen(token));

    flight *node = NULL;
    node = flight_node_new(uuid, company);
    assing_flight_to(node, destiny_airport);

    enqueue_flight(aux->flights_list, node);

    return;
  }

  if(strncmp(token, REM_A, 13) == 0){
    // printf("REM AEROPORTO: %s\n", rest);
    airport *node = NULL;
    airport *aux = NULL;
    node = airport_node_new(rest);
    aux = list_airport_find(self, node);
    if (aux != NULL)  {
      remove_a_airport(self, node);
      printf("Removed!\n");
    }
    return;
  }

  if(strncmp(token, REM_V, 7) == 0){
    printf("REM VOO: %s\n", rest);
    token = strtok_r(command, " ", &rest);
    command = rest;

    airport *origin = NULL;
    origin = airport_node_new(token);
    airport *aux = NULL;
    aux = list_airport_find(self, origin);

    token = strtok_r(command, " ", &rest);
    command = rest;

    char *to = NULL;
    to = (char *) malloc(sizeof(char) * STRING_MAX);
    to = token;

    remove_a_flight_from_airport_by_to(origin,token);
    return;
  }

}

// iterate over a list and save each node to_ascii_stream
void
list_to_stream(airports *self)  {
  char *filename = NULL;
  filename = reader( "Type the file name: " );

  airport_iterator *it = list_airport_iterator_new(self, LIST_HEAD);
  airport *node = NULL;

  if ( self->length == 0 )  {
    printf("No airports to write\n");
    return;
  }
  printf("##\nWriting AIRPORTS\n-- Total %d registers\n", self->length );

  while( (node = list_iterator_next_airport(it)) ) {
    airport_to_ascii_stream(node, filename);

    if ( node->flights_list->length != 0 )  {

      flight_iterator *it_fly = list_flight_iterator_new(node->flights_list, LIST_HEAD);
      flight *node_fly = NULL;

      while( (node_fly = list_iterator_next_flight(it_fly)) ) {
        fligth_to_ascii_stream(node_fly, node->airport_name, filename);
      }
      list_flight_iterator_destroy(it);
    }
  }
  list_airport_iterator_destroy(it);

  printf("# DONE\n");
}


// Stores the trimmed input string into the given output buffer, which must be
// large enough to store the result.  If it is too small, the output is
// truncated.
// FROM: http://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
size_t
trim_whitespace(char *out, size_t len, const char *str)  {
  if(len == 0)
    return 0;

  const char *end = NULL;
  size_t out_size;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
  {
    *out = 0;
    return 1;
  }

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;
  end++;

  // Set output size to minimum of trimmed string length and buffer size minus 1
  out_size = (end - str) < len-1 ? (end - str) : len-1;

  // Copy trimmed string and add null terminator
  strncpy(out, str, out_size);
  out[out_size] = 0;

  return out_size;
}

//generate a randon number for flight number
int
randomized()  {
  int limit = 30000;
  int divisor = RAND_MAX/(limit+1);
  int retval;

  do {
      retval = rand() / divisor;
  } while (retval > limit);

  return retval;
}
