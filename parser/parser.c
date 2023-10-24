#include "parser.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *pretokenize(char *program) {
  // allocate memory of length, which is 3 * program in worst case
  char *sprogram = (char *)calloc((3 * strlen(program)) + 1, sizeof(char));

  if (sprogram == NULL) {
    fprintf(stderr, "Memory cannot be allocated!\n");
    exit(1);
  }

  unsigned int i = 0;

  // add spaces around each operation and parentheses
  while (*program != '\0') {
    if (*program == '(' || *program == ')' || *program == '+' ||
        *program == '*' || *program == '/') {
      sprogram[i] = ' ';
      sprogram[i + 1] = *program;
      sprogram[i + 2] = ' ';
      i += 3;
    } else {
      sprogram[i] = *program;
      i++;
    }
    program++;
  }
  return sprogram;
}

TokenList tokenize(char *program, unsigned int length) {
  // length must be half of the program length according to worst case due to
  // pretokenize()

  // strtok() to tokenize the items separated by space
  const char *delim = " ";

  unsigned int y = 0;
  unsigned int partrack = 0;

  char *token = strtok(program, delim);

  if (strcmp(token, ")") == 0) {
    fprintf(stderr, "Syntax Error occured!\n");
    exit(1);
  }

  TokenList tokenlist;
  tokenlist.list = (char **)malloc(length * sizeof(char *));

  if (tokenlist.list == NULL) {
    fprintf(stderr, "Memory cannot be allocated!\n");
    exit(1);
  }

  // further tokenization and creating token list
  unsigned int i = 0;
  while (token != NULL) {
    tokenlist.list[i] = token;

    if (strcmp(token, "(") == 0) {
      y++;
      partrack++;
    } else if (strcmp(token, ")") == 0) {
      y++;
      partrack--;
    }

    if (partrack < 0) {
      fprintf(stderr, "Syntax Error occured!\n");
      exit(1);
    }

    token = strtok(NULL, delim);
    i++;
  }

  if (partrack != 0) {
    fprintf(stderr, "Syntax Error occured!\n");
    exit(1);
  }

  tokenlist.len_par = i;
  tokenlist.len = i - y;
  return tokenlist;
}

IsIntRet isInt(char *token) {
  char *end;
  errno = 0;
  long int val = strtol(token, &end, 10);
  IsIntRet res;

  if (errno == 0 && *end == '\0') {
    res.isInt = 1;
    res.val = val;
    return res;
  }
  res.isInt = 0;
  return res;
}

IsFloatRet isFloat(char *token) {
  char *end;
  errno = 0;
  double val = strtod(token, &end);
  IsFloatRet res;

  if (errno == 0 && *end == '\0') {
    res.isFloat = 1;
    res.val = val;
    return res;
  }
  res.isFloat = 0;
  return res;
}

IsStringRet isString(char *token) {
  IsStringRet res;
  int tokenLen = strlen(token);
  if (tokenLen > 2) {
    if (token[0] == '"' && token[tokenLen - 1] == '"') {
      res.isString = 1;
      res.val = (char *)calloc(tokenLen - 1, sizeof(char));
      strncpy(res.val, token + 1, tokenLen - 2);
      return res;
    }
    res.isString = 0;
    return res;
  } else if (tokenLen == 2) {
    if (token[0] == '"' && token[tokenLen - 1] == '"') {
      res.isString = 1;
      res.val = (char *)calloc(tokenLen - 1, sizeof(char));
      return res;
    }
    res.isString = 0;
    return res;
  } else {
    res.isString = 0;
    return res;
  }
}

SyntaxTree *createNode(char *token, unsigned int len) {
  SyntaxTree *newNode = (SyntaxTree *)malloc(sizeof(SyntaxTree));
  if (newNode != NULL) {
    if (isInt(token).isInt != 0) {
      newNode->token.val.numVal = isInt(token).val;
      newNode->token.type = INT;
    } else if (isFloat(token).isFloat != 0) {
      newNode->token.val.numVal = isFloat(token).val;
      newNode->token.type = FLOAT;
    } else if (isString(token).isString != 0) {
      newNode->token.val.symVal = isString(token).val;
      newNode->token.type = STRING;
    } else {
      newNode->token.val.symVal = token;
      newNode->token.type = SYMBOL;
    }
    newNode->params = (SyntaxTree **)malloc(len * sizeof(SyntaxTree *));
    for (int i = 0; i < len; i++) {
      newNode->params[i] = NULL;
    }
    return newNode;
  }
  fprintf(stderr, "Memory cannot be allocated!\n");
  exit(1);
}

SyntaxTree *constructST(TokenList tokenlist, SyntaxTree *root,
                        unsigned int *i) {
  if (strcmp(tokenlist.list[*i], "(") == 0) {
    (*i)++;
    while (strcmp(tokenlist.list[*i], ")") != 0 && *i < tokenlist.len_par) {
      if (root == NULL) {
        root = createNode(tokenlist.list[*i], tokenlist.len);
        (*i)++;
      }

      if (strcmp(tokenlist.list[*i], ")") == 0) {
        break;
      }

      unsigned int y = 0;
      while (root->params[y] != NULL) {
        y++;
      }
      root->params[y] = constructST(tokenlist, root->params[y], i);
      root->params_size = y + 1;
      (*i)++;
    }
    return root;
  } else {
    return createNode(tokenlist.list[*i], tokenlist.len);
  }
  return NULL;
}

ParseRet parse(char *program) {
  char *sprogram = pretokenize(program);
  unsigned int length = strlen(sprogram) / 2;
  TokenList tokenlist = tokenize(sprogram, length);
  unsigned int i = 0;
  SyntaxTree *st = constructST(tokenlist, NULL, &i);
  ParseRet pt;
  pt.st = st;
  pt.sprogram = sprogram;
  pt.tokenlist = tokenlist.list;

  return pt;
}
