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
            printf("level %d: %f, param_size: %d\n", level, st->token.val.numVal, st->params_size);
        } 
        level++;
        while (*st->params != NULL) {
            printST(*st->params, level);
            st->params++;
        }
    }
}

int main() {
    HashMap* hm = init();
    insert(hm, "+", add_o);

    char program[] = "(+ (+ 4 6) (+ -3.43 2))";
    ParseRet pt = parse(program);
    FuncRet res = evaluate(pt.st, hm);
    if (res.type == FLOAT) {
        printf("result: %f\n", (float)*(double*)res.val);
    }
    else {
        printf("result: %d\n", (int)*(double*)res.val);
    }
    free(pt.sprogram);
    free(pt.tokenlist);

    return 0;
}
