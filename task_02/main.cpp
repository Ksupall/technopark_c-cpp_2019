#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
#define MIN_SIZE 10
#define OK 0
#define NO_FILENAME -1
#define MEM_ERR -2
#define ERR -3

void err_message(int code)
{
  switch (code) {
    case MEM_ERR:
      printf("Memory allocation error!\n");
	  break;
	default:
      printf("Error!\n");
  } 
}

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
  FILE *f;
  f = fopen("in_2.txt", "r");
  if (!f)
  {
    err_code = ERR_FILE;
    err_message(err_code);
    return err_code;
  }
  char *string = (char *)calloc(SIZE, sizeof(char));
  if (!string)
  {
    err_code = ERR_MEMORY;
    err_message(err_code);
    return err_code;
  }
  for (int i = 0; i < SIZE; i++)
    fscanf(f, "%c", &(line[i]));
  fclose(f); 
  printf("Enter string you want to find in file: ");
  char *str = (char *)calloc(MIN_SIZE, sizeof(char));
  if (!str)
  {
    free(string);
    err_code = ERR_MEMORY;
    err_message(err_code);
    return err_code;
  }
  int rc = read_string(&str, &len);
  int len = MIN_SIZE;
  if (rc != OK)
  {
    free(string);
    free(str);
    err_message(rc);
    return rc;
  }
  int res = find_matchings(string, str);
  printf("Result\n = %d\n", res);
  free(str);
  return 0;
}
