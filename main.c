#include "evaluator/evaluator.h"
#include "parser/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeST(SyntaxTree *st) {
  if (st != NULL) {
    unsigned int i = 0;
    unsigned int size = st->params_size;
    while (i < size) {
      freeST(st->params[i]);
      i++;
    }
    free(st);
  }
}

void printST(SyntaxTree *st, unsigned int level) {
  if (st != NULL) {
    if (st->token.type == SYMBOL) {
      printf("level %d: %s, param_size: %d\n", level, st->token.val.symVal,
             st->params_size);
    } else {
      printf("level %d: %f, param_size: %d\n", level, st->token.val.numVal,
             st->params_size);
    }
    level++;
    while (*st->params != NULL) {
      printST(*st->params, level);
      st->params++;
    }
  }
}

void repl() {
  HashMap *hm = init();
  initOpMap(hm);
  while (1) {
    printf("lisp_int>> ");
    char program[1000];
    fgets(program, sizeof(program), stdin);
    program[strcspn(program, "\n")] = '\0';

    ParseRet pt = parse(program);
    FuncRet res = evaluate(pt.st, hm);
    if (res.type == FLOAT) {
      printf("%f\n", (float)*(double *)res.val);
    } else if (res.type == INT) {
      printf("%d\n", (int)*(double *)res.val);
    } else if (res.type == STRING) {
      printf("%s\n", (char *)res.val);
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
