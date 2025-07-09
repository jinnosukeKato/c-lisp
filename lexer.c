#include <ctype.h>

#include "lisp.h"

Token next_token(char *input, int *pos) {
  while (input[*pos] == ' ') {
    (*pos)++;  // 始めの空白を飛ばす
  }

  char ch = input[*pos];
  Token token;
  if (ch == '\0') {
    token.type = TOKEN_EOF;
  } else if (ch == '(') {
    token.type = TOKEN_LPAREN;
    (*pos)++;
  } else if (ch == ')') {
    token.type = TOKEN_RPAREN;
    (*pos)++;
  } else if (isdigit(ch)) {
    // 数値
    token.type = TOKEN_NUMBER;
    token.value.number = 0;
    while (isdigit(input[*pos])) {
      token.value.number = token.value.number * 10 + (input[*pos] - '0');
      (*pos)++;
    }
  } else {
    // シンボル
    token.type = TOKEN_SYMBOL;
    int i = 0;
    while (input[*pos] != ' ' && input[*pos] != '(' && input[*pos] != ')' &&
           input[*pos] != '\0') {
      token.value.symbol[i++] = input[(*pos)++];
    }
    token.value.symbol[i] = '\0';
  }

  return token;
}
