#include <stdio.h>

typedef struct TokenList {
    char** list;
    unsigned int len;
} TokenList;

typedef enum TokenType {
    LEFTBR,
    RIGHTBR,
    SYMBOL,
    NUMBER,
    STRING,
    BOOL,
    TOK_EOF,
} TokenType;

typedef struct Token {
   TokenType type;
   char* lexeme; // string which appears in code
   char* literal; // actual value of string
} Token;

typedef struct SyntaxTree {
    char* token;
    unsigned int i;
    struct SyntaxTree* left;
    struct SyntaxTree* right;
} SyntaxTree;

typedef struct ParseRet {
    SyntaxTree* st;
    char* sprogram;
    char** tokenlist;
} ParseRet;

char* pretokenize(char* program); // insert spaces around parentheses and operators, returns new program

TokenList tokenize(char* program, unsigned int length); // tokenizes the program text, returns the tokenlist and size

// construct a syntax tree according to the token list
SyntaxTree* constructST(char** tokens, unsigned int tokenNum, unsigned int i, SyntaxTree* root);

SyntaxTree* createNode(char* token);

ParseRet parse(char* program);
