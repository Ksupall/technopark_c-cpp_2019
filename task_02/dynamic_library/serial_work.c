#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "serial_work.h"

#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr) __builtin_expect(!!(expr), 1)

#define OK 0
#define ERR -1
#define MEM_ERR -2
#define ZERO_MAINSTR -3
#define ZERO_SUBSTR -4

ARR_DLL int ARR_DECL read_string(char **str, int *len) {
  char temp = 0;
  int i = 0;
  do {
    int rc = scanf("%c", &temp);
    if (unlikely(rc != 1))
      return ERR;
    if (temp == '\n')
      break;
    if (i >= *len)
    {
      char *t = (char *)realloc(*str, (*len + 1) * sizeof(char));
      if (unlikely(!t))
        return MEM_ERR;
      *str = t;
      *len += 1;
    }
    (*str)[i++] = temp;
  }
  while (1);
  if (*len > i)
  {
    char *t = (char *)realloc(*str, i * sizeof(char));
    if (unlikely(!t))
      return MEM_ERR;
    *str = t;
    *len = i;
  }
  return OK;
}

ARR_DLL int ARR_DECL find_matchings(char *line, char *str, int len_mainstr, int len_substr) {
  int amount = 0;
  if (unlikely(len_mainstr == 0))
    return ZERO_MAINSTR;
  else if (unlikely(len_substr == 0))
    return ZERO_SUBSTR;
  else
  for (int i = 0; i < len_mainstr - len_substr + 1; i++)
    for (int j = 0; j < len_substr; j++) {
      if (str[j] != line[i+j])
        break;
      else if (j == len_substr - 1){
        amount++;
    }
  }
  return amount;
}