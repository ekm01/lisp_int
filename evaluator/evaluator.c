#include "evaluator.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FuncRet evaluate(SyntaxTree *st, HashMap *hashmap) {
  if (st != NULL) {
    if (st->token.type == SYMBOL) {
      GetRet res = get(hashmap, st->token.val.symVal);
      if (res.type == INT || res.type == FLOAT) {
        return evaluate(res.val, hashmap);
      } else if (res.type == STRING) {
        FuncRet ret;
        size_t len = strlen((char *)res.val) + 1;
        ret.val = malloc(len * sizeof(char));
        strncpy(ret.val, (char *)res.val, len);
        ret.type = STRING;
        return ret;
      } else {
        Func f = res.val;
        return f(st, hashmap);
      }
    } else {
      FuncRet res;
      if (st->token.type == INT) {
        res.type = INT;
      } else {
        res.type = FLOAT;
      }
      res.val = malloc(sizeof(double));
      *(double *)res.val = st->token.val.numVal;
      return res;
    }
  }
  fprintf(stderr, "Unidentified expression!\n");
  exit(1);
}

FuncRet add_o(void *args, void *hashmap) {
  SyntaxTree *st = (SyntaxTree *)args;
  HashMap *map = (HashMap *)hashmap;

  if (st->params_size == 2) {
    FuncRet first = evaluate(st->params[0], map);
    FuncRet second = evaluate(st->params[1], map);
    FuncRet res;
    if (first.type == INT && second.type == INT) {
      res.type = INT;
    } else {
      res.type = FLOAT;
    }
    res.val = malloc(sizeof(double));
    *(double *)res.val = *(double *)first.val + *(double *)second.val;

    free(first.val);
    free(second.val);
    return res;
  } else {
    fprintf(stderr, "Expected number of params 2, but was %d\n",
            st->params_size);
    exit(1);
  }
}

FuncRet sub_o(void *args, void *hashmap) {
  SyntaxTree *st = (SyntaxTree *)args;
  HashMap *map = (HashMap *)hashmap;

  if (st->params_size == 2) {
    FuncRet first = evaluate(st->params[0], map);
    FuncRet second = evaluate(st->params[1], map);
    FuncRet res;
    if (first.type == INT && second.type == INT) {
      res.type = INT;
    } else {
      res.type = FLOAT;
    }
    res.val = malloc(sizeof(double));
    *(double *)res.val = (*(double *)first.val) - (*(double *)second.val);

    free(first.val);
    free(second.val);
    return res;
  } else if (st->params_size == 1) {
    FuncRet first = evaluate(st->params[0], map);
    FuncRet res;
    if (first.type == INT) {
      res.type = INT;
    } else {
      res.type = FLOAT;
    }
    res.val = malloc(sizeof(double));
    *(double *)res.val = (*(double *)first.val) * (-1);

    free(first.val);
    return res;
  } else {
    fprintf(stderr, "Expected number of params 1 or 2, but was %d\n",
            st->params_size);
    exit(1);
  }
}

FuncRet mul_o(void *args, void *hashmap) {
  SyntaxTree *st = (SyntaxTree *)args;
  HashMap *map = (HashMap *)hashmap;

  if (st->params_size == 2) {
    FuncRet first = evaluate(st->params[0], map);
    FuncRet second = evaluate(st->params[1], map);
    FuncRet res;
    if (first.type == INT && second.type == INT) {
      res.type = INT;
    } else {
      res.type = FLOAT;
    }
    res.val = malloc(sizeof(double));
    *(double *)res.val = (*(double *)first.val) * (*(double *)second.val);

    free(first.val);
    free(second.val);
    return res;
  } else {
    fprintf(stderr, "Expected number of params 2, but was %d\n",
            st->params_size);
    exit(1);
  }
}

FuncRet div_o(void *args, void *hashmap) {
  SyntaxTree *st = (SyntaxTree *)args;
  HashMap *map = (HashMap *)hashmap;

  if (st->params_size == 2) {
    FuncRet second = evaluate(st->params[1], map);

    if (*(double *)second.val == 0.0) {
      fprintf(stderr, "Division by zero!\n");
      exit(1);
    }

    FuncRet first = evaluate(st->params[0], map);
    FuncRet res;
    res.val = malloc(sizeof(double));

    if (first.type == INT && second.type == INT) {
      res.type = INT;
      *(double *)res.val =
          (int)(*(double *)first.val) / (int)(*(double *)second.val);

    } else {
      res.type = FLOAT;
      *(double *)res.val = (*(double *)first.val) / (*(double *)second.val);
    }

    free(first.val);
    free(second.val);
    return res;
  } else {
    fprintf(stderr, "Expected number of params 2, but was %d\n",
            st->params_size);
    exit(1);
  }
}

FuncRet l_o(void *args, void *hashmap) {
  SyntaxTree *st = (SyntaxTree *)args;
  HashMap *map = (HashMap *)hashmap;

  if (st->params_size == 2) {
    FuncRet first = evaluate(st->params[0], map);
    FuncRet second = evaluate(st->params[1], map);
    FuncRet res;

    res.val = malloc(sizeof(double));
    res.type = INT;
    double firstVal = *(double *)first.val;
    double secondVal = *(double *)second.val;

    if (firstVal < secondVal) {
      *(double *)res.val = 1.0;
    } else {
      *(double *)res.val = 0.0;
    }

    free(first.val);
    free(second.val);
    return res;
  } else {
    fprintf(stderr, "Expected number of params 2, but was %d\n",
            st->params_size);
    exit(1);
  }
}

FuncRet le_o(void *args, void *hashmap) {
  SyntaxTree *st = (SyntaxTree *)args;
  HashMap *map = (HashMap *)hashmap;

  if (st->params_size == 2) {
    FuncRet first = evaluate(st->params[0], map);
    FuncRet second = evaluate(st->params[1], map);
    FuncRet res;

    res.val = malloc(sizeof(double));
    res.type = INT;
    double firstVal = *(double *)first.val;
    double secondVal = *(double *)second.val;

    if (firstVal <= secondVal) {
      *(double *)res.val = 1.0;
    } else {
      *(double *)res.val = 0.0;
    }

    free(first.val);
    free(second.val);
    return res;
  } else {
    fprintf(stderr, "Expected number of params 2, but was %d\n",
            st->params_size);
    exit(1);
  }
}

FuncRet g_o(void *args, void *hashmap) {
  SyntaxTree *st = (SyntaxTree *)args;
  HashMap *map = (HashMap *)hashmap;

  if (st->params_size == 2) {
    FuncRet first = evaluate(st->params[0], map);
    FuncRet second = evaluate(st->params[1], map);
    FuncRet res;

    res.val = malloc(sizeof(double));
    res.type = INT;
    double firstVal = *(double *)first.val;
    double secondVal = *(double *)second.val;

    if (firstVal > secondVal) {
      *(double *)res.val = 1.0;
    } else {
      *(double *)res.val = 0.0;
    }

    free(first.val);
    free(second.val);
    return res;
  } else {
    fprintf(stderr, "Expected number of params 2, but was %d\n",
            st->params_size);
    exit(1);
  }
}

FuncRet ge_o(void *args, void *hashmap) {
  SyntaxTree *st = (SyntaxTree *)args;
  HashMap *map = (HashMap *)hashmap;

  if (st->params_size == 2) {
    FuncRet first = evaluate(st->params[0], map);
    FuncRet second = evaluate(st->params[1], map);
    FuncRet res;

    res.val = malloc(sizeof(double));
    res.type = INT;
    double firstVal = *(double *)first.val;
    double secondVal = *(double *)second.val;

    if (firstVal >= secondVal) {
      *(double *)res.val = 1.0;
    } else {
      *(double *)res.val = 0.0;
    }

    free(first.val);
    free(second.val);
    return res;
  } else {
    fprintf(stderr, "Expected number of params 2, but was %d\n",
            st->params_size);
    exit(1);
  }
}

FuncRet e_o(void *args, void *hashmap) {
  SyntaxTree *st = (SyntaxTree *)args;
  HashMap *map = (HashMap *)hashmap;

  if (st->params_size == 2) {
    FuncRet first = evaluate(st->params[0], map);
    FuncRet second = evaluate(st->params[1], map);
    FuncRet res;

    res.val = malloc(sizeof(double));
    res.type = INT;
    double firstVal = *(double *)first.val;
    double secondVal = *(double *)second.val;

    if (firstVal == secondVal) {
      *(double *)res.val = 1.0;
    } else {
      *(double *)res.val = 0.0;
    }

    free(first.val);
    free(second.val);
    return res;
  } else {
    fprintf(stderr, "Expected number of params 2, but was %d\n",
            st->params_size);
    exit(1);
  }
}

FuncRet if_o(void *args, void *hashmap) {
  SyntaxTree *st = (SyntaxTree *)args;
  HashMap *map = (HashMap *)hashmap;
  if (st->params_size == 2) {
    FuncRet cond = evaluate(st->params[0], map);
    if (cond.type == INT) {
      double condVal = *(double *)cond.val;

      if (condVal == 1.0) {
        free(cond.val);
        return evaluate(st->params[1], map);
      } else if (condVal == 0.0) {
        FuncRet res;
        res.type = INT;
        res.val = malloc(sizeof(int));
        *(int *)res.val = condVal;
        free(cond.val);
        return res;
      }
      free(cond.val);
      return evaluate(st->params[1], map);
    }

    free(cond.val);
    return evaluate(st->params[1], map);
  } else if (st->params_size == 3) {
    FuncRet cond = evaluate(st->params[0], map);
    if (cond.type == INT) {
      double condVal = *(double *)cond.val;

      if (condVal == 1.0) {
        free(cond.val);
        return evaluate(st->params[1], map);
      } else if (condVal == 0.0) {
        free(cond.val);
        return evaluate(st->params[2], map);
      }
      free(cond.val);
      return evaluate(st->params[1], map);
    }

    free(cond.val);
    return evaluate(st->params[1], map);
  } else {
    fprintf(stderr, "Expected number of params 2 or 3, but was %d\n",
            st->params_size);
    exit(1);
  }
}

FuncRet abs_o(void *args, void *hashmap) {
  SyntaxTree *st = (SyntaxTree *)args;
  HashMap *map = (HashMap *)hashmap;
  if (st->params_size == 1) {
    FuncRet first = evaluate(st->params[0], map);
    FuncRet res;
    if (first.type == INT) {
      res.type = INT;
    } else {
      res.type = FLOAT;
    }
    res.val = malloc(sizeof(double));
    *(double *)res.val = fabs(*(double *)first.val);
    free(first.val);
    return res;
  } else {
    fprintf(stderr, "Expected number of params 1, but was %d\n",
            st->params_size);
    exit(1);
  }
}

FuncRet begin(void *args, void *hashmap) {
  SyntaxTree *st = (SyntaxTree *)args;
  HashMap *map = (HashMap *)hashmap;
  if (st->params_size == 0) {
    fprintf(stderr, "Expected number of params > 0, but was %d\n",
            st->params_size);
    exit(1);
  }
  FuncRet res;
  unsigned int i = 0;
  while (i < st->params_size - 1) {
    res = evaluate(st->params[i], map);
    free(res.val);
    i++;
  }
  res = evaluate(st->params[i], map);
  return res;
}

FuncRet define(void *args, void *hashmap) {
  SyntaxTree *st = (SyntaxTree *)args;
  HashMap *map = (HashMap *)hashmap;
  if (st->params_size == 2) {
    char *key = st->params[0]->token.val.symVal;
    insert(map, key, st->params[1], st->params[1]->token.type);
    FuncRet res;
    res.val = NULL;
    res.type = FUNC_VOID;
    return res;
  } else {
    fprintf(stderr, "Expected number of params 2, but was %d\n",
            st->params_size);
    exit(1);
  }
}

unsigned int hash(char *key) {
  unsigned int hash = 0;
  while (*key != '\0') {
    hash = (hash * 33) + (*key);
    key++;
  }
  return hash % MAX_HASHMAP_SIZE;
}

HashMap *init() {
  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  if (map == NULL) {
    fprintf(stderr, "Memory cannot be allocated!\n");
    exit(1);
  }
  return map;
}

void insert(HashMap *map, char *key, void *value, TokenType type) {
  unsigned int index = hash(key);
  HashEntry *entry = (HashEntry *)malloc(sizeof(HashEntry));
  if (entry == NULL) {
    fprintf(stderr, "Memory cannot be allocated!\n");
    exit(1);
  }
  if (type == STRING) {
    size_t keylen = strlen(key) + 1;
    char *val = ((SyntaxTree *)value)->token.val.symVal;
    size_t valuelen = strlen(val) + 1;
    entry->key = (char *)malloc(keylen * sizeof(char));
    strncpy(entry->key, key, keylen);
    entry->value = (char *)malloc(valuelen * sizeof(char));
    strncpy((char *)entry->value, val, valuelen);
  } else {
    entry->key = key;
    entry->value = value;
  }

  entry->type = type;
  map->map[index] = entry;
}

GetRet get(HashMap *map, char *key) {
  unsigned int index = hash(key);
  HashEntry *entry = map->map[index];
  if (entry == NULL) {
    fprintf(stderr, "Unidentified expression!\n");
    exit(1);
  }

  GetRet res;
  res.type = entry->type;
  res.val = entry->value;
  return res;
}

void initOpMap(HashMap *map) {
  insert(map, "+", add_o, FUNC_GEN);
  insert(map, "-", sub_o, FUNC_NUM);
  insert(map, "*", mul_o, FUNC_NUM);
  insert(map, "/", div_o, FUNC_NUM);
  insert(map, "<", l_o, FUNC_GEN);
  insert(map, "<=", le_o, FUNC_GEN);
  insert(map, ">", g_o, FUNC_GEN);
  insert(map, ">=", ge_o, FUNC_GEN);
  insert(map, "=", e_o, FUNC_GEN);
  insert(map, "if", if_o, FUNC_GEN);
  insert(map, "abs", abs_o, FUNC_NUM);
  insert(map, "begin", begin, FUNC_GEN);
  insert(map, "define", define, FUNC_VOID);
}
