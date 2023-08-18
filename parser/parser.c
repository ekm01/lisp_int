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
    
    unsigned int y = 0;
    unsigned int partrack = 0;

    char* token = strtok(program, delim);
    
    if (strcmp(token, ")") == 0) {
        fprintf(stderr, "Syntax Error occured!\n");
        exit(1);
    }

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
        
        if (strcmp(token, "(") == 0) {
            y++;
            partrack++;
        }
        else if (strcmp(token, ")") == 0) {
            y++;
            partrack--;
        }

        if (partrack < 0) {
            fprintf(stderr, "Syntax Error occured!\n");
            exit(1);
        }

        token = strtok(NULL, delim);
        i++;
    }
    
    if (partrack != 0) {
            fprintf(stderr, "Syntax Error occured!\n");
            exit(1);
    }

    tokenlist.len_par = i;
    tokenlist.len = i - y;
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

SyntaxTree* createNode(char* token, unsigned int len) {
    SyntaxTree* newNode = (SyntaxTree*) malloc(sizeof(SyntaxTree));
    if (newNode != NULL) {
        if(isInt(token) != 0) {
            newNode->token.val.intVal = isInt(token); 
            newNode->token.type = NUMBER_INT;
        }
        else if (isFloat(token) != 0) {
            newNode->token.val.dobVal = isFloat(token); 
            newNode->token.type = NUMBER_FLOAT;
        }
        else {
            newNode->token.val.symVal = token;
            newNode->token.type = SYMBOL;
        }
        newNode->params = (SyntaxTree**) malloc(len * sizeof(SyntaxTree*));
        return newNode;
    }
   fprintf(stderr, "Memory cannot be allocated!\n");
   exit(1);
}

SyntaxTree* constructST(TokenList tokenlist, SyntaxTree* root, unsigned int* i) {

    if (strcmp(tokenlist.list[*i], "(") == 0) {
       (*i)++;
       while (strcmp(tokenlist.list[*i], ")") != 0 && *i < tokenlist.len_par) {
           if (root == NULL) {
               root = createNode(tokenlist.list[*i], tokenlist.len);
               (*i)++;
           }
           
           unsigned int y = 0;
           while (root->params[y] != NULL) {
               y++;
           }
           root->params[y] = constructST(tokenlist, root->params[y], i);
           root->params_size = y + 1;
           (*i)++;
       }
       return root;
    }
    else {
        return createNode(tokenlist.list[*i], tokenlist.len);
    }
    return NULL;
}

ParseRet parse(char* program) {
    char* sprogram = pretokenize(program);
    unsigned int length = strlen(sprogram) / 2;
    TokenList tokenlist = tokenize(sprogram, length);
    
    unsigned int i = 0;
    SyntaxTree* st = constructST(tokenlist, NULL, &i);
    
    ParseRet pt;
    pt.st = st;
    pt.sprogram = sprogram;
    pt.tokenlist = tokenlist.list;
    return pt;
}
