#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser/parser.h"

int main() {
    char program[] = "(begin (+ a (/ l c)) (* k (if ( < z g) q w)))";

    
    char* sprogram = pretokenize(program);
    unsigned int length = strlen(sprogram) / 2;
    TokenList tokenlist = tokenize(sprogram, length);
    unsigned int i = 0;
    SyntaxTree* st = constructST(tokenlist, NULL, &i, 0); 
    printf("%s\n", st->params[0]->params[1]->token.val.symVal);
    
    //ParseRet pt = parse(program);
    
    //free(pt.sprogram);
    //free(pt.tokenlist);
    return 0;
}
