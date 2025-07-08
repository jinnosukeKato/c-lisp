#include <ctype.h>
#include <stdio.h>

int stack[100] = {0};
int sp = 0;

void push(int i) { stack[sp++] = i; }

int pop(void) { return stack[--sp]; }

// Lexer Phase
enum TokenType {
  TOKEN_LPAREN,  // (
  TOKEN_RPAREN,  // )
  TOKEN_NUMBER,  // 数値
  TOKEN_SYMBOL,  // シンボル
  TOKEN_EOF,     // EOF
};
typedef enum TokenType TokenType;

struct Token {
  TokenType type;
  union {
    int number;
    char symbol[32];
  } value;
};
typedef struct Token Token;

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

char INPUT[] = "(add 5 5)";

int main(void) {
  int pos = 0;
  Token token;

  while ((token = next_token(INPUT, &pos)).type != TOKEN_EOF) {
    printf("pos: %d, ", pos);
    switch (token.type) {
      case TOKEN_LPAREN:
        printf("左括弧\n");
        break;
      case TOKEN_RPAREN:
        printf("右括弧\n");
        break;
      case TOKEN_NUMBER:
        printf("数値 %d\n", token.value.number);
        break;
      case TOKEN_SYMBOL:
        printf("シンボル %s\n", token.value.symbol);
        break;

      default:
        break;
    }
  }
  return 0;
}
