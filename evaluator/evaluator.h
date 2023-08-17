#define MAX_HASHMAP_SIZE 9

typedef long int (*IntFunc) ();

typedef double (*DobFunc) ();

typedef struct FuncType {
    IntFunc intfunc;
    DobFunc dobfunc;
} FuncType;

typedef struct HashEntry {
    char* key;
    FuncType functype;
} HashEntry;

typedef struct HashMap {
    HashEntry map[MAX_HASHMAP_SIZE];
    unsigned int size;
} HashMap;
