#include "lisp.h"

Node *new_node_number(int num) {
  Node *node = calloc(1, sizeof(Node));
  node->type = NODE_NUMBER;
  node->value.number = num;
  return node;
}

void node_list_add(Node *list, Node *elem) {
  int n = list->value.list.len;
  list->value.list.elements =
      realloc(list->value.list.elements, sizeof(Node *) * (n + 1));
  list->value.list.elements[n] = elem;
  list->value.list.len++;
}

Token *current_token;

Node *parse(Token *token) {
  current_token = token;

  expect(TOKEN_LPAREN);

  Node *node = calloc(1, sizeof(Node));
  node->type = NODE_LIST;
  node->value.list.elements = NULL;
  node->value.list.len = 0;

  Token *symbol = consume_if_symbol();
  if (symbol) {
    Node *symbol_node = calloc(1, sizeof(Node));
    symbol_node->type = NODE_SYMBOL;
    strcpy(symbol_node->value.symbol, symbol->value.symbol);

    node_list_add(node, symbol_node);
    node_list_add(node, new_node_number(expect_number()));  // lhs
    node_list_add(node, new_node_number(expect_number()));  // rhs
  } else {
    error("Expect symbol, but got %s", token_type_to_str(token->type));
  }

  expect(TOKEN_RPAREN);

  return node;
}
