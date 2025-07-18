#include "lisp.h"

Node *new_node_number(int num) {
  Node *node = calloc(1, sizeof(Node));
  node->type = NODE_NUMBER;
  node->value.number = num;
  return node;
}

Node *new_node_symbol(char *symbol) {
  Node *node = calloc(1, sizeof(Node));
  node->type = NODE_SYMBOL;
  strcpy(node->value.symbol, symbol);
  return node;
}

Node *new_node_cons(Cons *next) {
  Node *node = calloc(1, sizeof(Node));
  node->type = NODE_CONS;
  node->value.cons = next;
  return node;
}

Node *new_node_nil() {
  Node *node = calloc(1, sizeof(Node));
  node->type = NODE_NIL;
  return node;
}

Cons *new_cons(Node *car, Node *cdr) {
  Cons *cons = calloc(1, sizeof(Cons));
  cons->car = car;
  cons->cdr = cdr;
  return cons;
}

Token *current_token;

Cons *parse_cons() {
  Node *car;
  expect(TOKEN_LPAREN);

  if (current_token->type == TOKEN_SYMBOL) {
    car = new_node_symbol(current_token->value.symbol);
    consume(TOKEN_SYMBOL);
  } else if (current_token->type == TOKEN_NUMBER) {
    car = new_node_number(current_token->value.number);
    consume(TOKEN_NUMBER);
  } else if (current_token->type == TOKEN_LPAREN) {
    car = new_node_cons(parse_cons());
  } else if (consume(TOKEN_RPAREN)) {
    car = new_node_nil();
  } else {
    printf("\n-- parse error car. got %s --\n",
           token_type_to_str(current_token->type));
  }

  // todo: cdrの実装間違ってる ケツに必ずnilが来るようにしないといけない
  Node *cdr;
  if (current_token->type == TOKEN_NUMBER) {
    cdr = new_node_number(current_token->value.number);
    consume(TOKEN_NUMBER);
  } else if (current_token->type == TOKEN_LPAREN) {
    cdr = new_node_cons(parse_cons());
  } else if (consume(TOKEN_RPAREN) || consume(TOKEN_EOF)) {
    cdr = new_node_nil();
  } else {
    printf("\n-- parse error cdr. got %s --\n",
           token_type_to_str(current_token->type));
  }

  Cons *cons = calloc(1, sizeof(Cons));
  cons->car = car;
  cons->cdr = cdr;
  return cons;
}

Cons *parse(Token *token) {
  current_token = token;
  printf("parse start\n");
  return parse_cons();
}
