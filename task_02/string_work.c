#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_work.h"

int read_string(char **str, int *len)
{
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

void print_string(char *str, int len)
{
	for (int i = 0; i < len; i++)
		printf("%c", str[i]);
	printf("\nlen = %d\n", len);
}