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

