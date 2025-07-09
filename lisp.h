#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// logging utility
/// @brief エラーを報告しexit(1)する
/// @param fmt... エラーの内容
void error(char *fmt, ...);

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

/// @brief 現在着目しているトークン
extern Token *current_token;

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

/// @brief トークンの種類名を文字列で返す．
///@param type トークンの種類
///@return トークンの種類名
char *token_type_to_str(TokenType type);

/// @brief
/// 現在のトークンが期待した種類であれば1つ読み進め，そうでなければエラーを報告してexit(1)する．
/// @param expect 期待するトークンの種類
void expect(TokenType expect);

/// @brief
/// 現在のトークンがsymbolであれば1つ読み進め，与えられたトークンそのものを返す．
/// そうでなければ読み進めないでNULLを返す．
/// @return 与えられたトークン
Token *consume_if_symbol();

// parser
typedef enum NodeType NodeType;
enum NodeType {
  NODE_NUMBER,
  NODE_SYMBOL,
};

typedef struct Node Node;
struct Node {
  NodeType type;
  union {
    int number;       // NODE_NUMBER用
    char symbol[32];  // NODE_SYMBOL用
  } value;
};

/// @brief 与えられたトークンリストをパースする．
/// @param token
void parse(Token *token);
