#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

int main() {
    char program[] = "(+ (- 3 4) 7)";
    char* sprogram = pretokenize(program);
    unsigned int length = strlen(sprogram) / 2;
    TokenList tokenlist = tokenize(sprogram, length);
    
    for(int i = 0; i < tokenlist.len; i++) {
        printf("Token: %s\n", tokenlist.list[i]);
    }

    SyntaxTree* st = constructST(tokenlist.list, tokenlist.len, 0, NULL);
    printf("%s\n", st->token);
    printf("%s\n", st->left->token);
    printf("%s\n", st->left->left->token);
    printf("%s\n", st->right->token);

    // freeing sprogram
    free(sprogram);
    
    // freeing tokenlist
    for (int i = 0; i < length; i++){
        free(tokenlist.list[i]);
    }
    free(tokenlist.list);
    
    return 0;
}
