#include <stdio.h>
#include "scanner.h"

int main() {
    Token token;
    token.type = LEFTBR;
    token.lexeme = "(";
    token.literal = "(";
    printf("%s\n", token.lexeme);

    return 0;
}
