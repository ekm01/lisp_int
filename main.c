#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser/parser.h"
#include "evaluator/evaluator.h"

void printST(SyntaxTree* st, unsigned int level) {
    if (st != NULL) {
        if (st->token.type == SYMBOL) {
            printf("level %d: %s, param_size: %d\n", level, st->token.val.symVal, st->params_size);
        }
        else {
            printf("level %d: %ld, param_size: %d\n", level, st->token.val.intVal, st->params_size);
        } 
        level++;
        while (*st->params != NULL) {
            printST(*st->params, level);
            st->params++;
        }
    }
}

int main() {
    char program[] = "(+ (- 5 (* 3 2)) (+ 3 (/ 6 (if (< 5  6) a (- -1)) )))";
    ParseRet pt = parse(program);
    printf("%ld\n", evaluate(pt.st));
    printST(pt.st, 0);
    free(pt.sprogram);
    free(pt.tokenlist);

    return 0;
}
