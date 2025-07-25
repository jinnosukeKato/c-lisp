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

Node *new_node_tail(NodeType type) {
  Node *car = calloc(1, sizeof(Node));
  car->type = type;

  Cons *cons = new_cons(car, new_node_nil());
  return new_node_cons(cons);
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

  switch (current_token->type) {
    case TOKEN_SYMBOL:
      car = new_node_symbol(current_token->value.symbol);
      consume(TOKEN_SYMBOL);
      break;

    case TOKEN_NUMBER:
      car = new_node_number(current_token->value.number);
      consume(TOKEN_NUMBER);
      break;

    case TOKEN_LPAREN:
      car = new_node_cons(parse_cons());
      break;

    default:
      printf("\n-- parse error car. got %s --\n",
             token_type_to_str(current_token->type));
      break;
  }

  Node *cdr;
  switch (current_token->type) {
    case TOKEN_NUMBER:
      cdr = new_node_tail(NODE_NUMBER);
      // かなり力技的実装
      // carをパースしても残っているトークンを処理すればいいだけなのでもっといい実装できそう
      cdr->value.cons->car->value.number = current_token->value.number;
      consume(TOKEN_NUMBER);
      break;

    case TOKEN_LPAREN:
      cdr = new_node_cons(parse_cons());
      break;

    default:
      printf("\n-- parse error cdr. got %s --\n",
             token_type_to_str(current_token->type));
      break;
  }

  expect(TOKEN_RPAREN);

  Cons *cons = calloc(1, sizeof(Cons));
  cons->car = car;
  cons->cdr = cdr;
  return cons;
}

Cons *parse(Token *token) {
  current_token = token;
  return parse_cons();
}
