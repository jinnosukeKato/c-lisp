#include "lisp.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    error("illegal arguments number\n");
    return 1;
  }

  Token *token = tokenize(argv[1]);

  Cons *head = parse(token);

  // パース結果を出力
  // プロローグ
  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");
  gen_cons(head);
  // エピローグ
  printf("# return\n");
  pop("rax");
  printf("  ret\n");

  return 0;
}
