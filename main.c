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

  // パース結果を出力
  Cons *cur = head;
  while (cur) {
    // carの内容を表示
    if (cur->car->type == NODE_SYMBOL) {
      printf("symbol: %s\n", cur->car->value.symbol);
    } else if (cur->car->type == NODE_NUMBER) {
      printf("number: %d\n", cur->car->value.number);
    }

    // cdrをチェックして次に進む
    if (cur->cdr->type == NODE_NIL) {
      break;
    } else if (cur->cdr->type == NODE_CONS) {
      cur = cur->cdr->value.cons;
    } else {
      // cdrが数値やシンボルの場合も表示
      if (cur->cdr->type == NODE_SYMBOL) {
        printf("symbol: %s\n", cur->cdr->value.symbol);
      } else if (cur->cdr->type == NODE_NUMBER) {
        printf("number: %d\n", cur->cdr->value.number);
      }
      break;
    }
  }
  printf("parse complete\n");

  return 0;
}
