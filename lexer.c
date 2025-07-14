#include "lisp.h"

char *token_type_to_str(TokenType type) {
  switch (type) {
    case TOKEN_LPAREN:
      return "TOKEN_LPAREN";
    case TOKEN_RPAREN:
      return "TOKEN_RPAREN";
    case TOKEN_NUMBER:
      return "TOKEN_NUMBER";
    case TOKEN_SYMBOL:
      return "TOKEN_SYMBOL";
    case TOKEN_EOF:
      return "TOKEN_EOF";
    default:
      return "UNKNOWN";
  }
}

void expect(TokenType expect) {
  if (current_token->type != expect) {
    error("Expect token type: %s, but got %s", token_type_to_str(expect),
          token_type_to_str(current_token->type));
    return;  // never reached
  }

  current_token = current_token->next;
}

int expect_number() {
  if (current_token->type != TOKEN_NUMBER) {
    error("Expect number, but got %s", token_type_to_str(current_token->type));
  }

  int val = current_token->value.number;
  current_token = current_token->next;

  return val;
}

Token *consume_if_symbol() {
  if (current_token->type != TOKEN_SYMBOL) return NULL;
  Token *cur = current_token;
  current_token = current_token->next;
  return cur;
}

Token *new_token(TokenType type, Token *current) {
  Token *token = calloc(1, sizeof(Token));
  token->type = type;

  current->next = token;  // 現在のトークンのケツに新しいトークンをつける

  return token;
}

Token *tokenize(char *input) {
  char *p = input;
  Token head;
  head.next = NULL;
  Token *cur = &head;  // 現在のトークン

  while (*p) {
    if (isspace(*p)) {
      p++;
      continue;
    }

    if (*p == '(') {
      cur = new_token(TOKEN_LPAREN, cur);
      p += 1;
      continue;
    }

    if (*p == ')') {
      cur = new_token(TOKEN_RPAREN, cur);
      p += 1;
      continue;
    }

    if (isdigit(*p)) {
      cur = new_token(TOKEN_NUMBER, cur);
      // strtolによってpが適切にインクリメントされる
      cur->value.number = strtol(p, &p, 10);
      continue;
    }

    if (isalpha(*p)) {
      cur = new_token(TOKEN_SYMBOL, cur);
      int i = 0;
      while (isalnum(*p) && i < 31) {
        cur->value.symbol[i] = *p;
        i++;
        p++;
      }
      cur->value.symbol[i] = '\0';
      continue;
    }
  }

  new_token(TOKEN_EOF, cur);
  return head.next;  // headの次を返すことでheadを無視
}
