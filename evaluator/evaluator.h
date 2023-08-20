#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "../parser/parser.h"

// hashmap for tracking tokens
#define MAX_HASHMAP_SIZE 100000

typedef enum ValType {
    INT,
    FLOAT,
    FUNCTION,
    LIST,
} ValType; 

typedef struct FuncRet {
    void* val;
    ValType type;
} FuncRet;


typedef FuncRet (*Func) (void*);

typedef struct HashEntry {
    char* key;
    Func value;
} HashEntry;

typedef struct HashMap {
    HashEntry* map[MAX_HASHMAP_SIZE];
} HashMap;

unsigned int hash(char* key);

HashMap* init();

void insert(HashMap* map, char* key, Func func);

Func get(HashMap* map, char* key);

// evaluates the syntax tree
long int evaluate(SyntaxTree* st);

// integer-only operations
int* addInt(SyntaxTree* args);
int* subInt(SyntaxTree* args);
int* mulInt(SyntaxTree* args);
int* divInt(SyntaxTree* args);
int* lInt(SyntaxTree* args); // less than
int* leInt(SyntaxTree* args); // less equals
int* gInt(SyntaxTree* args); // greater than
int* geInt(SyntaxTree* args); // greater equals
int* eInt(SyntaxTree* args); // equals

// float-only operations
double addF(SyntaxTree* args);
double subF(SyntaxTree* args);
double mulF(SyntaxTree* args);
double divF(SyntaxTree* args);
int lF(SyntaxTree* args); // less than
int leF(SyntaxTree* args); // less equals
int gF(SyntaxTree* args); // greater than
int geF(SyntaxTree* args); // greater equals
int eF(SyntaxTree* args); // equals

// operations for both
void* abso(SyntaxTree* args);

// fundamental operations

#endif
