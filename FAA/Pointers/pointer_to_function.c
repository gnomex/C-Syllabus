/**
  FROM: http://stackoverflow.com/questions/1350376/function-pointer-as-a-member-of-a-c-struct
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct pstring_t {
        char * chars;
        int (* length)();
} PString;

int length(PString * self) {
    return strlen(self->chars);
}
PString * initializeString(int n)
{
    PString *str=(PString*)malloc(sizeof(PString));
    str->chars=(char *)malloc(sizeof(char)*n);
    str->length = length;
    return str;
}
int main()
{
  PString *p=initializeString(30);
  strcpy(p->chars,"Hello bro!");
  printf("\n%d",p->length(p));
 return 0;
}
