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
    struct SyntaxTree* left;
    struct SyntaxTree* right;
} SyntaxTree;

char* pretokenize(char* program); // insert spaces around parentheses and operators, returns new program

TokenList tokenize(char* program, unsigned int length); // tokenizes the program text, returns the tokenlist and size

SyntaxTree* constructST(char** tokens, unsigned int tokenNum, unsigned int i, SyntaxTree* root);

SyntaxTree* createNode(char* token);
