#ifndef __SERIAL__WORK__H__
#define __SERIAL__WORK__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int serial(char *argv, char *substr, int len_mainstr, int len_substr);
int read_string(char **str, int *len);
int find_matchings(char *line, char *str, int mainstr, int len_substr);

#endif