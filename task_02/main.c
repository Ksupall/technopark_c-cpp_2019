#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_work.h"

#define SIZE 100
#define MIN_SIZE 10

void err_message(int code)
{
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
	default:
      printf("Error!\n");
  } 
}

int find_matchings(char *line, char *str) {
  int len_line, len_str;
  len_line = strlen(line);
  len_str = strlen(str);
  int amount = 0;
  if (len_line == 0) 
    printf("Wrong line!\n"); 
  else if (len_str == 0) 
    printf("Wrong str!\n"); 
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

int main (int argc, char *argv[]) {
  setbuf(stdout, NULL);
  int err_code = 0;
  if (argc < 2)
  {
    err_code = NO_FILENAME;
    err_message(err_code);
    return err_code;
  }
  printf("Enter string you want to find in file: ");
  char *str = (char *)calloc(MIN_SIZE, sizeof(char));
  if (!str)
  {
    err_code = MEM_ERR;
    err_message(err_code);
    return err_code;
  }
  int len_str = MIN_SIZE;
  int rc = read_string(&str, &len_str);
  if (rc != OK)
  {
    free(str);
    err_message(rc);
    return rc;
  }
  FILE *f;
  f = fopen(argv[1], "r");
  if (!f)
  {
    err_code = ERR_FILE;
    err_message(err_code);
    return err_code;
  }
  char *string = (char *)calloc(SIZE, sizeof(char));
  if (!string)
  {
    err_code = MEM_ERR;
    err_message(err_code);
    return err_code;
  }
  for (int i = 0; i < SIZE; i++)
    fscanf(f, "%c", &(string[i]));
  fclose(f); 
  int res = find_matchings(string, str);
  printf("Result = %d\n", res);
  free(str);
  return 0;
}
