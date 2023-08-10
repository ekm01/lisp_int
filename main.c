#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

int main() {
    char program[] = "(begin (define r 10) (* pi (* r r)))";
    char* sprogram = pretokenize(program);
    unsigned int length = strlen(sprogram)/2;
    TokenList tokenlist = tokenize(sprogram, length);
    
    for(int i = 0; i < tokenlist.len; i++) {
        printf("Token: %s\n", tokenlist.list[i]);
    }

    // freeing sprogram
    free(sprogram);
    
    // freeing tokenlist
    for (int i = 0; i < length; i++){
        free(tokenlist.list[i]);
    }
    free(tokenlist.list);
    
    return 0;
}
