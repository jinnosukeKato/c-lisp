#include "lisp.h"

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
