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

void repl() {
    while (1) {
        printf("lisp_int>>  ");
        char program[1000];
        fgets(program, sizeof(program), stdin);
        program[strcspn(program, "\n")] = '\0';
        HashMap* hm = init();
        initOpMap(hm);
        ParseRet pt = parse(program);
        FuncRet res = evaluate(pt.st, hm);
        if (res.type == FLOAT) {
            printf("%f\n", (float)*(double*)res.val);
        }
        else {
            printf("%d\n", (int)*(double*)res.val);
        }
        free(pt.sprogram);
        free(pt.tokenlist);
        free(res.val);
    }
}

int main() {
    repl();
    //printST(pt.st, 0);
    return 0;
}
