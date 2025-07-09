#include <stdio.h>

#include "lisp.h"

int stack[100] = {0};
int sp = 0;

void push(int i) { stack[sp++] = i; }

int pop(void) { return stack[--sp]; }

char INPUT[] = "(add 5 5)";

int main(void) {
  Token *token = tokenize(INPUT);

  while (token->type != TOKEN_EOF) {
    switch (token->type) {
      case TOKEN_LPAREN:
        printf("左括弧\n");
        break;
      case TOKEN_RPAREN:
        printf("右括弧\n");
        break;
      case TOKEN_NUMBER:
        printf("数値 %d\n", token->value.number);
        break;
      case TOKEN_SYMBOL:
        printf("シンボル %s\n", token->value.symbol);
        break;

      default:
        break;
    }

    token = token->next;
  }
  return 0;
}
