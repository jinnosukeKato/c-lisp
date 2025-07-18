#include <stdio.h>

#include "lisp.h"

int stack[100] = {0};
int sp = 0;

void push(int i) { stack[sp++] = i; }

int pop(void) { return stack[--sp]; }

char INPUT[] = "(add (5 5))";

int main(void) {
  printf("input: %s\n", INPUT);
  Token *token = tokenize(INPUT);
  Cons *head = parse(token);
  printf("parse complete\n");

  // パース結果を出力
  print_cons(head);

  return 0;
}
