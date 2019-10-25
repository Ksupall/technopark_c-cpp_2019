#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "err_codes.h"
#include "serial_work.h"

#define SIZE 104857600
#define MIN_SIZE 10

void err_message(int code) {
  switch (code) {
    case NO_FILENAME:
      printf("No filename!\n");
      break;
    case ERR_FILE:
      printf("Couldn't open file!\n");
      break;
    case MEM_ERR:
      printf("Memory allocation error!\n");
      break;
    case ZERO_LINE:
      printf("String where we find substring has zero length!\n");
      break;
    case ZERO_STR:
      printf("Substring has zero length!\n");
  default:
      printf("Error!\n");
  } 
}

int main (int argc, char *argv[]) {
  setbuf(stdout, NULL);
  int err_code = 0;
  if (argc < 2) {
    err_code = NO_FILENAME;
    err_message(err_code);
    return err_code;
  }
  printf("Enter string you want to find in file: ");
  char *str = (char *)calloc(MIN_SIZE, sizeof(char));
  if (!str) {
    err_code = MEM_ERR;
    err_message(err_code);
    return err_code;
  }
  int len_str = MIN_SIZE;
  int rc = read_string(&str, &len_str);
  if (rc != OK) {
    free(str);
    err_message(rc);
    return rc;
  }
  FILE *f;
  f = fopen(argv[1], "r");
  if (!f) {
    err_code = ERR_FILE;
    err_message(err_code);
    return err_code;
  }
  char *string = (char *)calloc(SIZE, sizeof(char));
  if (!string) {
    err_code = MEM_ERR;
    err_message(err_code);
    return err_code;
  }
  for (int i = 0; i < SIZE; i++)
    fscanf(f, "%c", &(string[i]));
  fclose(f);
  int result = find_matchings(string, str);
  printf("Result = %d\n", result);
  free(str);
  return 0;
}
