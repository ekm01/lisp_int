#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser/parser.h"

void inorderTraversal(SyntaxTree* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%s\n", root->token);
        inorderTraversal(root->right);
    }
}

int main() {
    char program[] = "(begin (define r 10) (* pi (* r r)))";
    ParseRet pt = parse(program);
    inorderTraversal(pt.st);
    
    free(pt.sprogram);
    free(pt.tokenlist);
    return 0;
}
