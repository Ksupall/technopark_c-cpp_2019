#ifndef __STRUCT__IO__H
#define __STRUCT__IO__H
#include "struct.h"

int read_from_file(FILE **fin, product_t **p, int *amount);
void output(product_t *prod, int amount);
void print_products(product_t *prod, int amount);

#endif