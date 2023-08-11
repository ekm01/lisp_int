#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

void inorderTraversal(SyntaxTree *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%s\n", root->token);
        inorderTraversal(root->right);
    }
}

int main() {
    char program[] = "(begin (define r 10) (* pi (* r r)))";
    char* sprogram = pretokenize(program);
    unsigned int length = strlen(sprogram) / 2;
    TokenList tokenlist = tokenize(sprogram, length);
     
    for(int i = 0; i < tokenlist.len; i++) {
        printf("Token: %s\n", tokenlist.list[i]);
    }

    SyntaxTree* leftSubtree = constructST(tokenlist.list, tokenlist.len, 0, NULL);
    SyntaxTree* rightSubtree = constructST(tokenlist.list, tokenlist.len, leftSubtree->i, NULL);
    
    leftSubtree->right = rightSubtree;
    
    inorderTraversal(leftSubtree);
    

    // freeing sprogram
    free(sprogram);
    
    // freeing tokenlist
    for (int i = 0; i < length; i++){
        free(tokenlist.list[i]);
    }
    free(tokenlist.list);
    
    return 0;
}
