#ifndef __SERIAL__WORK__H__
#define __SERIAL__WORK__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_string(char **str, int *len);
int find_matchings(char *line, char *str);
void print_string(char *str);

#endif