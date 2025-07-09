#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// lexer
typedef enum TokenType TokenType;
enum TokenType {
  TOKEN_LPAREN,  // (
  TOKEN_RPAREN,  // )
  TOKEN_NUMBER,  // 数値
  TOKEN_SYMBOL,  // シンボル
  TOKEN_EOF,     // EOF
};

typedef struct Token Token;
struct Token {
  TokenType type;
Token *next;  // 次のトークンのポインタ
  union {
    int number;
    char symbol[32];
  } value;
};

/*
新しいトークンを生成し，現在のトークンの後ろに付ける

@param type トークンの種類
@param current 現在のトークンのポインタ
@return 新しいトークン
*/
Token *new_token(TokenType type, Token *current);

/*
入力文字列からトークンの単方向リストを生成

@param input 入力文字列の先頭ポインタ
@return 生成したトークンの単方向リスト
*/
Token *tokenize(char *input);

// parser
enum NodeType {
  NODE_NUMBER,
  NODE_SYMBOL,
};
typedef enum NodeType NodeType;

struct Node {
  NodeType type;
  union {
    int number;       // NODE_NUMBER用
    char symbol[32];  // NODE_SYMBOL用
  } value;
};
typedef struct Node Node;

Node *next_node(Token *token);
