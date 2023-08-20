#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "evaluator.h"

FuncRet evaluate(SyntaxTree* st, HashMap* hashmap) {
    if (st != NULL) {
       if (st->token.type == SYMBOL) {
           Func f = get(hashmap, st->token.val.symVal);
           return f(st, hashmap);
       }
       else {
           FuncRet res;
           if (st->token.type == NUMBER_INT) {
               res.type = INT;
               res.val = malloc(sizeof(int));
               *(int*)res.val = st->token.val.intVal;
           }
           else {
               res.type = FLOAT;
               res.val = malloc(sizeof(float));
               *(float*)res.val = st->token.val.dobVal;
           }
           return res;
       }

    }
    fprintf(stderr, "Unidentified expression!\n");
    exit(1);
}

FuncRet add_o(void* args, void* hashmap) {
    SyntaxTree* st = (SyntaxTree*) args;
    HashMap* map = (HashMap*) hashmap;

    if (st->params_size == 2) {
        FuncRet first = evaluate(st->params[0], map);
        FuncRet second = evaluate(st->params[1], map);
        FuncRet res;
        if (first.type == FLOAT || second.type == FLOAT) {
            printf("first: %f, second: %d\n",*(float*)first.val, *(int*)second.val);
            res.val = malloc(sizeof(float));
            *(float*)res.val = *(float*)first.val + *(float*)second.val;
        }
        else {
            res.type = INT;
            res.val = malloc(sizeof(int));
            *(int*)res.val = *(int*)first.val + *(int*)second.val;
        }
        
        free(first.val);
        free(second.val);
        return res;
        
    }
    else {
        fprintf(stderr, "Expected number of params 2, but was %d\n", st->params_size);
        exit(1);
    }
}

unsigned int hash(char* key) {
    unsigned int hash = 0;
    while (*key != '\0') {
        hash = (hash * 33) + (*key);
        key++;
    }
    return hash % MAX_HASHMAP_SIZE;
}

HashMap* init() {
    HashMap* map = (HashMap*) malloc(sizeof(HashMap));
    if (map == NULL) {
        fprintf(stderr, "Memory cannot be allocated!\n");
        exit(1);
    }
    return map;
}

void insert(HashMap* map, char* key, Func func) {
    unsigned int index = hash(key);
    HashEntry* entry = (HashEntry*) malloc(sizeof(HashEntry));
    if (entry == NULL) {
        fprintf(stderr, "Memory cannot be allocated!\n");
        exit(1);
    }
    entry->key = key;
    entry->value = func;
    map->map[index] = entry;
}

Func get(HashMap* map, char* key) {
    unsigned int index = hash(key);
    HashEntry* entry = map->map[index];

    if (entry == NULL) {
        fprintf(stderr, "Unidentified expression!\n");
        exit(1);
    }
    return entry->value;
}


