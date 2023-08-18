#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
               else if (strcmp(st->token.val.symVal, "-") == 0) {
                   if (st->params_size == 1) {
                       return evaluate(*st->params) * (-1);
                   }
                   return evaluate(*st->params) - evaluate(*(st->params + 1));
               }
               else if (strcmp(st->token.val.symVal, "*") == 0) {
                   long int a = evaluate(*st->params);
                   st->params++;
                   long int b = evaluate(*st->params);
                   return a * b;
               }
               else if (strcmp(st->token.val.symVal, "/") == 0) {
                   long int a = evaluate(*st->params);
                   st->params++;
                   long int b = evaluate(*st->params);
                   if (b == 0) {
                       fprintf(stderr, "Division by zero!\n");
                       exit(1);
                   }
                   return a / b;
               }
               else if (strcmp(st->token.val.symVal, "<") == 0) {
                   long int a = evaluate(*st->params);
                   st->params++;
                   long int b = evaluate(*st->params);
                   if (a < b) {
                       return true;
                   }
                   return false;
               }
               else if (strcmp(st->token.val.symVal, "<=") == 0) {
                   long int a = evaluate(*st->params);
                   st->params++;
                   long int b = evaluate(*st->params);
                   if (a <= b) {
                       return true;
                   }
                   return false;
               }
               else if (strcmp(st->token.val.symVal, ">") == 0) {
                   long int a = evaluate(*st->params);
                   st->params++;
                   long int b = evaluate(*st->params);
                   if (a > b) {
                       return true;
                   }
                   return false;
               }
               else if (strcmp(st->token.val.symVal, ">=") == 0) {
                   long int a = evaluate(*st->params);
                   st->params++;
                   long int b = evaluate(*st->params);
                   if (a >= b) {
                       return true;
                   }
                   return false;
               }
               else if (strcmp(st->token.val.symVal, "=") == 0) {
                   long int a = evaluate(*st->params);
                   st->params++;
                   long int b = evaluate(*st->params);
                   if (a == b) {
                       return true;
                   }
                   return false;
               }
               else if (strcmp(st->token.val.symVal, "if") == 0) {
                   bool a = evaluate(*st->params);
                   st->params++;
                   if (a == true) {
                       return evaluate(*st->params);
                   }
                   st->params++;
                   return evaluate(*st->params);
               }
               else if (strcmp(st->token.val.symVal, "abs") == 0) {
                   long int a = evaluate(*st->params);
                   if (a < 0) {
                       return a * (-1);
                   }
                   return a;
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

