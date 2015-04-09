#include <stdio.h>
#include <ctype.h>

// Stores the trimmed input string into the given output buffer, which must be
// large enough to store the result.  If it is too small, the output is
// truncated.
// From: http://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
size_t
trimwhitespace(
  char *out,
  size_t len,
  const char *str)
{
  if(len == 0)
    return 0;

  const char *end;
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
  memcpy(out, str, out_size);
  out[out_size] = 0;

  return out_size;
}

/**
  From: http://stackoverflow.com/questions/18368712/since-we-have-snprintf-why-we-dont-have-a-snscanf/18371445#18371445
*/
#define safe_scanf(fmt, maxb, ...) { \
    char buffer[maxb+1] = { [maxb - 1] = '\0' }; \
    fgets(buffer, maxb+1, stdin); \
    if ((buffer[maxb - 1] != '\0') && (buffer[maxb - 1] != '\n')) \
        while(getchar() != '\n') \
           ; \
    sscanf(buffer, fmt, __VA_ARGS__); \
  }
#define MAXBUFF 255

int main(void) {
  int x; float f;
  safe_scanf("%d %g", MAXBUFF+1, &x, &f);
  printf("Your input was: x == %d\t\t f == %g",  x, f);
  return 0;
}
