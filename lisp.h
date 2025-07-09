// lexer
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

Token next_token(char *input, int *pos);
