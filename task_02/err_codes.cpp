#include <stdio.h>

#include "err_codes.h"

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
    case ZERO_MAINSTR:
      printf("String where we find substring has zero length!\n");
      break;
    case ZERO_SUBSTR:
      printf("Substring has zero length!\n");
  default:
      printf("Error!\n");
  } 
}