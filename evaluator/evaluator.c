#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "evaluator.h"

long int evaluate(SyntaxTree* st) {
    if (st != NULL) {
       if (st->token.type == SYMBOL) {
           unsigned int i = 0;
           while (st->params[i] != NULL) {
               if (strcmp(st->token.val.symVal, "+") == 0) {
                   if (st->params_size == 2) {
                       return evaluate(st->params[i]) + evaluate(st->params[i + 1]);
                   }
                   else {
                       fprintf(stderr, "Expected number of params 2, but was %d\n", st->params_size);
                       exit(1);
                   }
               }
               else if (strcmp(st->token.val.symVal, "-") == 0) {
                   if (st->params_size == 1) {
                       return evaluate(st->params[i]) * (-1);
                   }
                   else if (st->params_size == 2) {
                       return evaluate(st->params[i]) - evaluate(st->params[i + 1]);
                   }
                   else {
                       fprintf(stderr, "Expected number of params either 1 or 2, but was %d\n", st->params_size);
                       exit(1);
                   }
               }
               else if (strcmp(st->token.val.symVal, "*") == 0) {
                   if (st->params_size == 2) {
                       return evaluate(st->params[i]) * evaluate(st->params[i + 1]);
                   }
                   else {
                       fprintf(stderr, "Expected number of params 2, but was %d\n", st->params_size);
                       exit(1);
                   }
               }
               else if (strcmp(st->token.val.symVal, "/") == 0) {
                   if (st->params_size == 2) {
                       long int second = evaluate(st->params[i + 1]);
                       if (second == 0) {
                           fprintf(stderr, "Division by zero!\n");
                           exit(1);
                       }
                       return evaluate(st->params[i]) / second;
                   }
                   else {
                       fprintf(stderr, "Expected number of params 2, but was %d\n", st->params_size);
                       exit(1);
                   }
                   
               }
               else if (strcmp(st->token.val.symVal, "<") == 0) {
                   if (st->params_size == 2) {
                       if (evaluate(st->params[i]) < evaluate(st->params[i + 1])) {
                           return true;
                       }
                       return false;
                   }
                   else {
                       fprintf(stderr, "Expected number of params 2, but was %d\n", st->params_size);
                       exit(1);
                   }
                   
               }
               else if (strcmp(st->token.val.symVal, "<=") == 0) {
                   if (st->params_size == 2) {
                       if (evaluate(st->params[i]) <= evaluate(st->params[i + 1])) {
                           return true;
                       }
                       return false;
                   }
                   else {
                       fprintf(stderr, "Expected number of params 2, but was %d\n", st->params_size);
                       exit(1);
                   }
               }
               else if (strcmp(st->token.val.symVal, ">") == 0) {
                   if (st->params_size == 2) {
                       if (evaluate(st->params[i]) > evaluate(st->params[i + 1])) {
                           return true;
                       }
                       return false;
                   }
                   else {
                       fprintf(stderr, "Expected number of params 2, but was %d\n", st->params_size);
                       exit(1);
                   }
               }
               else if (strcmp(st->token.val.symVal, ">=") == 0) {
                   if (st->params_size == 2) {
                       if (evaluate(st->params[i]) >= evaluate(st->params[i + 1])) {
                           return true;
                       }
                       return false;
                   }
                   else {
                       fprintf(stderr, "Expected number of params 2, but was %d\n", st->params_size);
                       exit(1);
                   }
               }
               else if (strcmp(st->token.val.symVal, "=") == 0) {
                   if (st->params_size == 2) {
                       if (evaluate(st->params[i]) == evaluate(st->params[i + 1])) {
                           return true;
                       }
                       return false;
                   }
                   else {
                       fprintf(stderr, "Expected number of params 2, but was %d\n", st->params_size);
                       exit(1);
                   }
               }
               else if (strcmp(st->token.val.symVal, "if") == 0) {
                   if (st->params_size == 3) {
                       bool a = evaluate(st->params[i]);
                       if (a == true) {
                           return evaluate(st->params[i + 1]);
                       }
                       return evaluate(st->params[i + 2]);
                   }
                   else {
                       fprintf(stderr, "Expected number of params 3, but was %d\n", st->params_size);
                       exit(1);                   }
               }
               else if (strcmp(st->token.val.symVal, "abs") == 0) {
                   if (st->params_size == 1) {
                       long int a = evaluate(st->params[i]);
                       if (a < 0) {
                           return a * (-1);
                       }
                       return a;
                   }
                   
               }
                
               i++;
           }
       }
       else {
           return st->token.val.intVal;
       }

    }
    fprintf(stderr, "Unidentified expression!\n");
    exit(1);
}

