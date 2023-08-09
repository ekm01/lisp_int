#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"

char** tokenize(char* program, unsigned int length) {
    
    // strtok() to tokenize the items separated by space
    const char* delim = " ";
    char* token = strtok(program, delim);

    char** result = (char**) malloc(length * sizeof(char*));
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
