#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serial_work.h"

int read_string(char **str, int *len) {
  char temp = 0;
  int rc = 0;
  int i = 0;
  do {
    rc = scanf("%c", &temp);
    if (rc != 1)
      return ERR;
    if (temp == '\n')
      break;
    if (i >= *len)
    {
      char *t = (char *)realloc(*str, (*len + 1) * sizeof(char));
      if (!t)
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
    if (!t)
      return MEM_ERR;
    *str = t;
    *len = i;
  }
  return OK;
}


int find_matchings(char *line, char *str) {
  int len_line, len_str;
  len_line = strlen(line);
  len_str = strlen(str);
  int amount = 0;
  if (len_line == 0)
    return ZERO_LINE;
  else if (len_str == 0)
    return ZERO_STR;
  else
  for (int i = 0; i < len_line - len_str + 1; i++)
    for (int j = 0; j < len_str; j++) {
      if (str[j] != line[i+j])
        break;
      else if (j == len_str - 1){
        amount++;
    }
  }
  return amount;
}

void print_string(char *str) {
	for (int i = 0; i < strlen(str); i++)
		printf("%c", str[i]);
}