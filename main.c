#include <stdio.h>

#include "lisp.h"

int stack[100] = {0};
int sp = 0;

void push(int i) { stack[sp++] = i; }

int pop(void) { return stack[--sp]; }

char INPUT[] = "(add 5 5)";

int main(void) {
  Token *token = tokenize(INPUT);
  parse(token);
  printf("parse complete\n");

  return 0;
}
