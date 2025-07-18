#include "lisp.h"

void print_node(Node *node) {
  switch (node->type) {
    case NODE_SYMBOL:
      printf("symbol: %s\n", node->value.symbol);
      break;

    case NODE_NUMBER:
      printf("number: %d\n", node->value.number);
      break;

    case NODE_CONS:
      printf("nested list start\n");
      print_cons(node->value.cons);
      printf("nested list end\n");
      break;

    case NODE_NIL:
      printf("nil\n");
      break;

    default:
      printf("print node error. why you can see this message?\n");
      break;
  }
}

void print_cons(Cons *head) {
  Cons *cur = head;
  while (cur) {
    print_node(cur->car);

    switch (cur->cdr->type) {
      case NODE_NIL:
        printf("list tail nil\n");
        cur = NULL;
        break;

      case NODE_CONS:
        cur = cur->cdr->value.cons;
        break;

      default:
        print_node(cur->cdr);
        cur = NULL;
        break;
    }
  }
}
