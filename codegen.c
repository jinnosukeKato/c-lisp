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

void push_i(int immediate) { printf("  push %d\n", immediate); }

void push(char *source) { printf("  push %s\n", source); }

void pop(char *destination) { printf("  pop %s\n", destination); }

void gen_node(Node *node) {
  switch (node->type) {
    case NODE_NUMBER:
      push_i(node->value.number);
      return;

    case NODE_SYMBOL:
      if (strcmp("add", node->value.symbol) == 0) {
        printf("# add\n");
        pop("rdi");
        pop("rax");
        printf("  add rax, rdi\n");
        push("rax");
      }
      break;
    case NODE_CONS:
      gen_cons(node->value.cons);
      break;

    default:
      break;
  }
}

void gen_cons(Cons *head) {
  Cons *cur = head;

  gen_node(cur->cdr);
  gen_node(cur->car);
}
