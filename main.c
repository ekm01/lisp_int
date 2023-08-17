#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser/parser.h"
#include "evaluator/evaluator.h"

void printST(SyntaxTree* st, unsigned int level) {
    if (st != NULL) {
        printf("level %d: %s\n", level, st->token.val.symVal);
        level++;
        while (*st->params != NULL) {
            printST(*st->params, level);
            st->params++;
        }
    }
}

int main() {
    /*char program[] = "(begin (define r a) (* pi (* r r)))";
    ParseRet pt = parse(program);
    printST(pt.st, 0); 

    free(pt.sprogram);
    free(pt.tokenlist);*/
    FuncType func;
    func.intfunc = addInt;
    func.dobfunc = addDob;
    
    HashMap* map = init();
    
    insert(map, "+", func);
    FuncType anan = get(map, "+");
    printf("%ld\n", anan.intfunc(2, 5));
    
    return 0;
}
