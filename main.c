#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser/parser.h"
#include "evaluator/evaluator.h"

void freeST(SyntaxTree* st) {
    if (st != NULL) {
        unsigned int i = 0;
        while (st->params[i] != NULL) {
            freeST(st->params[i]);
            i++;
        }
        free(st->params[i]);
    }
}

void repl() {
    HashMap* hm = init();
    initOpMap(hm);
    while (1) {
        printf("lisp_int>>  ");
        char program[1000];
        fgets(program, sizeof(program), stdin);
        program[strcspn(program, "\n")] = '\0';

        ParseRet pt = parse(program);
        FuncRet res = evaluate(pt.st, hm);
        if (res.type == FLOAT) {
            printf("%f\n", (float)*(double*)res.val);
        }
        else if (res.type == INT) {
            printf("%d\n", (int)*(double*)res.val);
        }
        free(pt.sprogram);
        free(pt.tokenlist);
        free(res.val);
        freeST(pt.st);
    }
}

int main() {
    repl();
    
    return 0;
}
