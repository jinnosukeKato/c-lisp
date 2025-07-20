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
/// トークンが数値ならその数値を返しトークンを1つ読み進める，そうでなければエラーを報告してexit(1)する．
/// @return トークンのもつ値
int expect_number();

/// @brief
/// 現在のトークンがsymbolであれば1つ読み進め，与えられたトークンそのものを返す．
/// そうでなければ読み進めないでNULLを返す．
/// @return 与えられたトークン
Token *consume_if_symbol();

/// @brief
/// 現在のトークンの種類が引数と一致すれば1つ読み進め，真を返す．そうでなければ何もせず偽を返す．
/// @param type 比較するトークンの種類
/// @return 現在のトークンの種類が引数と一致するか否か
bool consume(TokenType type);

// parser
typedef struct Cons Cons;
typedef struct Node Node;

struct Cons {
  Node *car;
  Node *cdr;
};

typedef enum NodeType NodeType;
enum NodeType {
  NODE_NUMBER,
  NODE_SYMBOL,
  NODE_CONS,
  NODE_NIL,
};

struct Node {
  NodeType type;
  union {
    int number;       // NODE_NUMBER用
    char symbol[32];  // NODE_SYMBOL用
    Cons *cons;       // NODE_CONS用
  } value;
};

/// @brief 与えられた数値を持つ数字ノードを作成して返す．
/// @param num ノードの持つ数値
/// @return 与えられた数値を持つ数字ノード
Node *new_node_number(int num);

/// @brief 与えられたシンボルを持つシンボルノードを作成して返す．
/// @param symbol ノードの持つシンボル
/// @return 与えられたシンボルを持つシンボルノード
Node *new_node_symbol(char *symbol);

/// @brief 与えられたCons *を持つノードを作成して返す．
/// @param next 次につなげるConsのポインタ
/// @return 与えられたCons *を持つノード
Node *new_node_cons(Cons *next);

/// @brief Nilノードを作成して返す．
/// @return Nilノード
Node *new_node_nil();

/// @brief 与えられたcarとcdrを持つconsを作成して返す
/// @param car car
/// @param cdr cdr
/// @return 与えられたcarとcdrを持つcons
Cons *new_cons(Node *car, Node *cdr);

/// @brief 与えられたトークンリストをパースし，先頭のConsを返す．
/// @param token パース対象のトークン
Cons *parse(Token *token);

// code generator

/// @brief 与えられたノードを再帰的にprintする
/// @param node 対象のノード
void print_node(Node *node);

/// @brief 与えられたConsセルを再帰的にprintする
/// @param head 対象のConsセル
void print_cons(Cons *head);

/// @brief 即値をスタックにpushする
/// @param immediate 即値
void push_i(int immediate);

/// @brief スタックに指定されたレジスタをpushする
/// @param source 指定されたレジスタ
void push(char *source);

/// @brief スタックトップからpopする
/// @param destination 格納先のレジスタ名
void pop(char *destination);

/// @brief ノードのアセンブリを再帰的に吐く
/// @param node 対象のノード
void gen_node(Node *node);

/// @brief Consのアセンブリを再帰的に吐く
/// @param head 対象のCons
void gen_cons(Cons *head);
