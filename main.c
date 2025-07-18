#include "lisp.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    error("illegal arguments number\n");
    return 1;
  }

  printf("tokenize start\n");
  Token *token = tokenize(argv[1]);
  printf("tokenize complete\n");

  printf("parse start\n");
  Cons *head = parse(token);
  printf("parse complete\n");

  // パース結果を出力
  print_cons(head);

  return 0;
}
