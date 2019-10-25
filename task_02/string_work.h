#ifndef __STRING__WORK__H__
#define __STRING__WORK__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define NO_FILENAME -1
#define ERR_FILE -2
#define MEM_ERR -3
#define ZERO_LINE -4
#define ZERO_STR -5

int read_string(char **str, int *len);
void print_string(char *str, int len);

#endif