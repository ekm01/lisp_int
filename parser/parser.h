#ifndef PARSER_H
#define PARSER_H

typedef struct TokenList {
    char** list;
    unsigned int len_par; // number of tokens with parentheses
    unsigned int len; // without parentheses
} TokenList;

typedef enum TokenType {
    SYMBOL,
    NUMBER_INT,
    NUMBER_FLOAT,
} TokenType;

typedef union Value {
   char* symVal; // value of a symbol token
   double numVal; // value of a number token
} Value;

typedef struct Token {
   TokenType type;
   Value val;
} Token;

typedef struct SyntaxTree {
    Token token;
    struct SyntaxTree** params;
    unsigned int params_size;
} SyntaxTree;

typedef struct ParseRet {
    SyntaxTree* st;
    char* sprogram;
    char** tokenlist;
} ParseRet;

typedef struct IsIntRet {
    int isInt;
    long int val;
} IsIntRet;

typedef struct IsFloatRet {
    int isFloat;
    double val;
} IsFloatRet;

char* pretokenize(char* program); // insert spaces around parentheses and operators, returns new program

TokenList tokenize(char* program, unsigned int length); // tokenizes the program text, returns the tokenlist and size

// construct a syntax tree according to the token list
SyntaxTree* constructST(TokenList tokenlist, SyntaxTree* root, unsigned int* i);

IsIntRet isInt(char* token); // check if str = int

IsFloatRet isFloat(char* token); // check if str = float

SyntaxTree* createNode(char* token, unsigned int len);

ParseRet parse(char* program);

#endif
