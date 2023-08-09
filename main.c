#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"

int main() {
    char program[] = "(begin (define r 10) (* pi (* r r)))";
    unsigned int length = strlen(program);
    char** tokens = tokenize(program, length);
    
    for(int i = 0; i < length; i++) {
        printf("Token: %s\n", tokens[i]);
    }
    
    // freeing the allocated tokens
    for(int i = 0; i < length; i++) {
        free(tokens[i]);
    }
    free(tokens);
    return 0;
}
