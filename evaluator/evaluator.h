#define MAX_HASHMAP_SIZE 9

typedef long int (*IntFunc) (long int, long int);

typedef double (*DobFunc) (double, double);

long int addInt(long int a, long int b);

double addDob(double a, double b);

typedef struct FuncType {
    IntFunc intfunc;
    DobFunc dobfunc;
} FuncType;

typedef struct HashEntry {
    char* key;
    FuncType value;
} HashEntry;

typedef struct HashMap {
    HashEntry* map[MAX_HASHMAP_SIZE];
} HashMap;

unsigned int hash(char* key);

HashMap* init();

void insert(HashMap* map, char* key, FuncType func);

FuncType get(HashMap* map, char* key);
