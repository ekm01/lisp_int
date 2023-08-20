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


typedef FuncRet (*Func) (void*, void*);

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
FuncRet evaluate(SyntaxTree* st, HashMap* hashmap);

// arithmetic binary operations
FuncRet add_o(void* args, void* hashmap);
FuncRet sub_o(SyntaxTree* st);
FuncRet mul_o(SyntaxTree* st);
FuncRet div_o(SyntaxTree* st);
FuncRet l_o(SyntaxTree* st); // less than
FuncRet le_o(SyntaxTree* st); // less equals
FuncRet g_o(SyntaxTree* st); // greater than
FuncRet ge_o(SyntaxTree* st); // greater equals
FuncRet e_o(SyntaxTree* st); // equals

// other math operations
FuncRet abso(SyntaxTree* st);

// fundamental operations


#endif
