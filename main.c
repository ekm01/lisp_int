#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"

int main() {
    char program[] = "(begin (define r 10) (* pi (* r r)))";
    char* sprogram = pretokenize(program);
    unsigned int length = strlen(sprogram)/2;
    char** tokens = tokenize(sprogram, length);
    
    for(int i = 0; i < length; i++) {
        printf("Token: %s\n", tokens[i]);
    }
    // freeing sprogram
    free(sprogram);

    // freeing the allocated tokens
    for(int i = 0; i < length; i++) {
        free(tokens[i]);
    }
    free(tokens);
    return 0;
}
