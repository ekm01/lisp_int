#include <stdio.h>

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


char** tokenize(char* program); // tokenizes the program text

