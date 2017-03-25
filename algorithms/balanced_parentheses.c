#include <stdio.h>
#include <stdlib.h>

#define TM_PRINTF(f_, ...) printf((f_), __VA_ARGS__)

#define MAX 20

char stack[MAX];
int stack_size = 0;

void push(char x) {

  if (is_stack_full()) {
    TM_PRINTF("java.out_of_memory_error", NULL);
    exit(1);
  }

  stack[stack_size++] = x;
}

char pop() {
  return stack[--stack_size];
}

int is_empty_stack() {
  return stack_size <= 0;
}

int is_stack_full() {
  return stack_size >= MAX;
}

void printStack()  {
  int i;

  TM_PRINTF("Current stack: ", NULL);

  for (i = 0; i < stack_size; i++) {
    TM_PRINTF(" %c ", stack[i]);
  }

  TM_PRINTF("\n", NULL);
}

int main() {
  int lenght, i;
  char str[] = "(((a))+(b))(((()()(((()()()))))";
  lenght = strlen(str);

  printStack();

  for(i = 0; i < lenght; i++){

    if(str[i] == '(') {
      push(str[i]);
      printStack();
    } else if(str[i] == ')') {
      pop();
      printStack();
    }
  }

  printStack();

  if (is_empty_stack()) TM_PRINTF("Well done, it was balanced\n", NULL);
  else TM_PRINTF("ooops, stack contains %d elements\n", stack_size);

  return 0;
}
