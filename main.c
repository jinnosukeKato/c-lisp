#include <stdio.h>

#include "lisp.h"

int stack[100] = {0};
int sp = 0;

void push(int i) { stack[sp++] = i; }

int pop(void) { return stack[--sp]; }

char INPUT[] = "(add 5 5)";

int main(void) {
  Token *token = tokenize(INPUT);
  Node *node = parse(token);

  // パース結果を出力
  if (node->type == NODE_LIST && node->value.list.len > 0) {
    for (int i = 0; i < node->value.list.len; i++) {
      switch (node->value.list.elements[i]->type) {
        case NODE_SYMBOL:
          printf("%s\n", node->value.list.elements[i]->value.symbol);
          break;

        case NODE_NUMBER:
          printf("%d\n", node->value.list.elements[i]->value.number);
          break;

        default:
          break;
      }
    }
  }
  printf("parse complete\n");

  return 0;
}
