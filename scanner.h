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

char* pretokenize(char* program); // insert spaces around parentheses and operators

char** tokenize(char* program, unsigned int length); // tokenizes the program text
