#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "../parser/parser.h"

// hashmap for tracking tokens
#define MAX_HASHMAP_SIZE 1000

typedef enum ValTypeFunc {
    INT,
    FLOAT,
    STRING, 
} ValTypeFunc; 

typedef enum ValType {
    FUNCTION,
    VARIABLE,
} ValType;

typedef struct GetRet {
    ValType type;
    void* val;
} GetRet;

typedef struct FuncRet {
    void* val;
    ValTypeFunc type;
} FuncRet;

typedef FuncRet (*Func) (void*, void*);

typedef struct HashEntry {
    char* key;
    void* value;
    ValType type;
} HashEntry;

typedef struct HashMap {
    HashEntry* map[MAX_HASHMAP_SIZE];
} HashMap;

unsigned int hash(char* key);

HashMap* init();

void insert(HashMap* map, char* key, void* value, ValType type);

GetRet get(HashMap* map, char* key);

void initOpMap(HashMap* map);

// evaluates the syntax tree
FuncRet evaluate(SyntaxTree* st, HashMap* hashmap);

// arithmetic binary operations
FuncRet add_o(void* args, void* hashmap);
FuncRet sub_o(void* args, void* hashmap);
FuncRet mul_o(void* args, void* hashmap);
FuncRet div_o(void* args, void* hashmap);
FuncRet l_o(void* args, void* hashmap); // less than
FuncRet le_o(void* args, void* hashmap); // less equals
FuncRet g_o(void* args, void* hashmap); // greater than
FuncRet ge_o(void* args, void* hashmap); // greater equals
FuncRet e_o(void* args, void* hashmap); // equals

// identity function
FuncRet identity(void* args, void* hashmap);

// conditional
FuncRet if_o(void* args, void* hashmap);

// other math operations
FuncRet abs_o(void* args, void* hashmap);

// fundamental operations
FuncRet begin(void* args, void* hashmap);
FuncRet define(void* args, void* hashmap);

#endif
