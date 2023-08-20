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
    HashMap* hm = init();
    insert(hm, "+", add_o);

    char program[] = "(+ 3 3)";
    ParseRet pt = parse(program);
    FuncRet res = evaluate(pt.st, hm);
    if (res.type == FLOAT) {
        printf("result: %f\n", *(float*)res.val);
    }
    else {
        printf("result: %d\n", *(int*)res.val);
    }
    free(pt.sprogram);
    free(pt.tokenlist);

    return 0;
}
