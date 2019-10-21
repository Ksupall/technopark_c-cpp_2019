#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.hpp"
#include <time.h>

void error_message(int code) {
switch (code) {
  case NO_FILENAME:
    printf("No filename!\n");
    break;
  case ERR_FILE:
    printf("Couldn't open file!\n");
    break;
  case EMPTY_FILE:
    printf("File is empty!\n");
    break;
  case WRONG_FILE:
    printf("File has wrong construction!\n");
    break;
  case WRONG_YEAR:
    printf("Wrong year!\n");
    break;
  case WRONG_MONTH:
    printf("Wrong month!\n");
    break;
  case WRONG_DAY:
    printf("Wrong day!\n");
    break;
  case FUTURE_DATE:
    printf("Future date!\n");
    break;
  case WRONG_DATE:
    printf("Date is wrong!\n");
    break;
  case ERR_MEMORY:
    printf("Memory allocation error!\n");
    break;
  default:
    printf("Error!\n");
}
}

int main() {
  int err_code = 0;
  setbuf(stdout, NULL);
  char filename[20] = "in_0.txt";
  FILE *fin = fopen(filename, "r");
  if (!fin) {
    err_code = ERR_FILE;
    error_message(err_code);
    return err_code;
  }
  int amount;
  product_t *prod = NULL;
  err_code = read_from_file(&fin, &prod, &amount);
  if (err_code != OK) {
    error_message(err_code);
    fclose(fin);
    free(prod);
    return err_code;
  }
  fclose(fin);
  int *key = (int *)calloc(amount, sizeof(int));
  if (!key) {
    free(prod);
    return ERR_MEMORY;
  }
  for (int i = 0; i < amount; i++)
    key[i] = i;
  sort_by_key(prod, amount, key);
  output(prod, amount, key);
  free(prod);
  free(key);
  return 0;
}