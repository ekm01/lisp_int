#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser/parser.h"

int main() {
    char program[] = "(- (* pi (* r r)) (* pi (* r r)))";
    char* a = "32f";
    SyntaxTree* st = createNode(a);
    printf("type: %d, symVal: %s\n", st->token.type, st->token.val.symVal);

    //ParseRet pt = parse(program);
    
    //free(pt.sprogram);
    //free(pt.tokenlist);
    return 0;
}
