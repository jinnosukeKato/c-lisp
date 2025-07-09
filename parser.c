#include "lisp.h"

Token *current_token;

void parse(Token *token) {
  current_token = token;

  expect(TOKEN_LPAREN);

  Token *symbol = consume_if_symbol();
  if (!symbol)
    error("Expect symbol, but got %s", token_type_to_str(token->type));
  Node *node = calloc(1, sizeof(Node));
  node->type = NODE_SYMBOL;
  strcpy(node->value.symbol, symbol->value.symbol);

  expect(TOKEN_NUMBER);
  expect(TOKEN_NUMBER);

  expect(TOKEN_RPAREN);
}
