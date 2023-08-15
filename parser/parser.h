#include <stdio.h>

typedef struct TokenList {
    char** list;
    unsigned int len;
} TokenList;

typedef enum TokenType {
    SYMBOL,
    NUMBER,
} TokenType;

typedef union Value {
   char* symVal; // value of a symbol token
   long int intVal; // actual value of a number token
   double dobVal;
} Value;

typedef struct Token {
   TokenType type;
   Value val;
} Token;

typedef struct SyntaxTree {
    Token token;
    struct SyntaxTree** params;
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

long int isInt(char* token); // check if str = int

double isFloat(char* token); // check if str = float

SyntaxTree* createNode(char* token);

ParseRet parse(char* program);
