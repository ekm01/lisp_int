#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "parser.h"

char* pretokenize(char* program) {
    // allocate memory of length, which is 3 * program in worst case
    char* sprogram = (char*) calloc((3 * strlen(program)) + 1, sizeof(char));
   
    if (sprogram == NULL) {
        fprintf(stderr, "Memory cannot be allocated!\n");
        exit(1);
    }

    unsigned int i = 0;

    // add spaces around each operation and parentheses
    while(*program != '\0') {
        if (*program == '(' || *program == ')' || *program == '+' || *program == '-' || *program == '*' || *program == '/') {
            sprogram[i] = ' ';
            sprogram[i + 1] = *program;
            sprogram[i + 2] = ' ';
            i += 3;
        }
        else {
            sprogram[i] = *program;
            i++;
        }
        program++;
    }
    return sprogram;
}

TokenList tokenize(char* program, unsigned int length) {
    // length must be half of the program length according to worst case due to pretokenize()
    
    // strtok() to tokenize the items separated by space
    const char* delim = " ";
    char* token = strtok(program, delim);
    
    TokenList tokenlist;
    tokenlist.list = (char**) malloc(length * sizeof(char*));
    
    if (tokenlist.list == NULL) {
        fprintf(stderr, "Memory cannot be allocated!\n");
        exit(1);
    }
    
    // further tokenization and creating token list
    unsigned int i = 0;
    while(token != NULL) {
        tokenlist.list[i] = token;
        if (tokenlist.list[i] == NULL) {
            fprintf(stderr, "Memory cannot be allocated!\n");
            exit(1);
    }
        token = strtok(NULL, delim);
        i++;
    }
    
    tokenlist.len = i;
    return tokenlist;
}

long int isInt(char* token) {
    char* end;
    errno = 0;
    long int res = strtol(token, &end, 10);
    
    if (errno == 0 && *end == '\0') {
        return res;
    }
    return 0;
}

double isFloat(char* token) {
    char* end;
    errno = 0;
    double res = strtod(token, &end);
    
    if (errno == 0 && *end == '\0') {
        return res;
    }
    return 0.0;
}

SyntaxTree* createNode(char* token) {
    SyntaxTree* newNode = (SyntaxTree*) malloc(sizeof(SyntaxTree));
    if (newNode != NULL) {
        if(isInt(token) != 0) {
            newNode->token.val.intVal = isInt(token); 
            newNode->token.type = NUMBER;
        }
        else if (isFloat(token) != 0) {
            newNode->token.val.dobVal = isFloat(token); 
            newNode->token.type = NUMBER;
        }
        else {
            newNode->token.val.symVal = token;
            newNode->token.type = SYMBOL;
        }
        return newNode;
    }
   fprintf(stderr, "Memory cannot be allocated!\n");
   exit(1);
}

/*SyntaxTree* constructST(char** tokens, unsigned int tokenNum, unsigned int i, SyntaxTree* root) {

    if (strcmp(tokens[i], "(") == 0) {
       i++;
       while (strcmp(tokens[i], ")") != 0 && i < tokenNum) {
           if (root == NULL) {
               root = createNode(tokens[i]);
               i++;
           }
           if (root->left == NULL) {
               root->left = constructST(tokens, tokenNum, i, root->left);
               i++;
           }
           if (root->left != NULL && root->right == NULL) {
               root->right = constructST(tokens, tokenNum, i, root->right);
           }
           i++;
       }
       i++;
       if (root == NULL){
           return NULL;
       }

       root->i = i;
       return root;
    }
    else if (strcmp(tokens[i], ")") == 0) {
        fprintf(stderr, "Syntax Error occured!\n");
        exit(1);
    }
    else {
        return createNode(tokens[i]);
    }
    return NULL;
}

ParseRet parse(char* program) {
    char* sprogram = pretokenize(program);
    unsigned int length = strlen(sprogram) / 2;
    TokenList tokenlist = tokenize(sprogram, length);
    SyntaxTree* leftSubtree = constructST(tokenlist.list, tokenlist.len, 0, NULL);

    ParseRet pt;
    pt.tokenlist = tokenlist.list;
    pt.sprogram = sprogram;

    if (leftSubtree != NULL){
        if (leftSubtree->i > tokenlist.len - 1) {
            pt.st = leftSubtree;
            return pt;
        }
        else {
            SyntaxTree* rightSubtree = constructST(tokenlist.list, tokenlist.len, leftSubtree->i, NULL);
            leftSubtree->right = rightSubtree;
            pt.st = leftSubtree;
            return pt;
        }
    }
    return pt;
}*/
