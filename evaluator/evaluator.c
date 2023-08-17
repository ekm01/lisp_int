#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "evaluator.h"

long int evaluate(SyntaxTree* st) {
    if (st != NULL) {
       if (st->token.type == SYMBOL) {
           while (*st->params != NULL) {
               if (strcmp(st->token.val.symVal, "+") == 0) {
                   long int a = evaluate(*st->params);
                   st->params++;
                   long int b = evaluate(*st->params);
                   return a + b;
               }
               else {
                   long int a = evaluate(*st->params);
                   st->params++;
                   long int b = evaluate(*st->params);
                   return a - b;
               }
               st->params++;
           }
       }
       else {
           return st->token.val.intVal;
       }

    }

    return -1;
}

