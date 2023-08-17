#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "evaluator.h"

// binary arithmetic operators

long int addInt(long int a, long int b) {
    return a + b;
}

long int subInt(long int a, long int b) {
    return a - b;
}

long int mulInt(long int a, long int b) {
    return a * b;
}

long int divInt(long int a, long int b) {
    return a / b;
}

double addDob(double a, double b) {
    return a + b;
}
  
double subDob(double a, double b) {
    return a - b;
}
 
double mulDob(double a, double b) {
    return a * b;
}

double divDob(double a, double b) {
    return a / b;
}

// binary comparison operator

long int eInt(long int a, long int b) {
    if (a == b) {
        return 1;
    }
    return 0;
}

long int gInt(long int a, long int b) {
    if (a > b) {
        return 1;
    }
    return 0;
}

long int geInt(long int a, long int b) {
    if (a >= b) {
        return 1;
    }
    return 0;
}

long int lInt(long int a, long int b) {
    if (a < b) {
        return 1;
    }
    return 0;
}

long int leInt(long int a, long int b) {
    if (a <= b) {
        return 1;
    }
    return 0;
}

long int eDob(double a, double b) {
    if (a == b) {
        return 1;
    }
    return 0;
}

long int gDob(double a, double b) {
    if (a > b) {
        return 1;
    }
    return 0;
}

long int geDob(double a, double b) {
    if (a >= b) {
        return 1;
    }
    return 0;
}

long int lDob(double a, double b) {
    if (a < b) {
        return 1;
    }
    return 0;
}

long int leDob(double a, double b) {
    if (a <= b) {
        return 1;
    }
    return 0;
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

void insert(HashMap* map, char* key, FuncType func) {
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

FuncType get(HashMap* map, char* key) {
    unsigned int index = hash(key);
    HashEntry* entry = map->map[index];
    
    if (entry == NULL) {
        fprintf(stderr, "No such entry!\n");
        exit(1);
    }
    return entry->value;
}
