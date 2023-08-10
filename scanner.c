#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"

char* pretokenize(char* program) {
    // allocate memory of length, which is 3 * program in worst case
    char* sprogram = (char*) calloc((3 * strlen(program)) + 1, sizeof(char));
   
    if (sprogram == NULL) {
        fprintf(stderr, "Memory cannot be allocated!");
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



char** tokenize(char* program, unsigned int length) {
    // length must be half of the program length according to worst case due to pretokenize()
    
    // strtok() to tokenize the items separated by space
    const char* delim = " ";
    char* token = strtok(program, delim);

    char** result = (char**) malloc((length) * sizeof(char*));
    if (result == NULL) {
        fprintf(stderr, "Memory cannot be allocated!");
        exit(1);
    }
    
    // further tokenization and creating token list
    unsigned int i = 0;
    while(token != NULL) {
        result[i] = (char*) malloc(strlen(token) + 1);
        if (result[i] == NULL) {
            fprintf(stderr, "Memory cannot be allocated!");
            exit(1);
    }
        strncpy(result[i], token, strlen(token));
        token = strtok(NULL, delim);
        i++;
    }
    return result;
}
