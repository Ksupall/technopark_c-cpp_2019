#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "err_codes.h"
#include "serial_work.h"
#include "parallel_work.h"

#define SIZE 104857600 //столько символов в файле 100Мб
#define PART_SIZE 26214400 //разбила все эти символы на 4 потока
#define MIN_SIZE 10

#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr) __builtin_expect(!!(expr), 1)

// функция, которая составляет строку из кусочков строк, берет значения на границе,
//чтобы ничего не упустить
char *between_parts(int len_str, char *part1, char *part2, char *part3, char *part4)
{
  char *part_between = (char *)calloc((len_str - 1) * 6, sizeof(char));
  if (unlikely(!part_between))
    return NULL;
  int j = 0;
  // конец первой части
  for (int i = PART_SIZE - len_str + 1; i < PART_SIZE; i++)
    part_between[j++] = part1[i];
  // начало и конец второй части
  for (int i = 0; i < len_str - 1; i++)
    part_between[j++] = part2[i];
  for (int i = PART_SIZE + 1 - len_str; i < PART_SIZE; i++)
    part_between[j++] = part2[i];
  // начало и конец третьей части
  for (int i = 0; i < len_str - 1; i++)
    part_between[j++] = part3[i];
  for (int i = PART_SIZE + 1 - len_str; i < PART_SIZE; i++)
    part_between[j++] = part3[i];
  // начало четвертой части
  for (int i = 0; i < len_str - 1; i++)
    part_between[j++] = part4[i];
  return part_between;
}

int serial(char *argv[], char *substr, int len_substr) {
  int err_code = 0;
  FILE *f;
  f = fopen(argv[1], "r");
  if (unlikely(!f)) {
    err_code = ERR_FILE;
    err_message(err_code);
    return err_code;
  }
  char *mainstr = (char *)calloc(SIZE, sizeof(char));
  if (unlikely(!mainstr)) {
    err_code = MEM_ERR;
    err_message(err_code);
    return err_code;
  }
  for (int i = 0; i < SIZE; i++)
    fscanf(f, "%c", &(mainstr[i]));
  fclose(f);
  int result = find_matchings(mainstr, substr, SIZE, len_substr);
  printf("Serial result = %d\n", result);  
  free(mainstr);
  return 0;
}

int parallel(char *argv[], char *substr, int len_substr) {
  int err_code = 0;
  FILE *f;
  f = fopen(argv[1], "r");
  if (unlikely(!f)) {
    err_code = ERR_FILE;
    err_message(err_code);
    return err_code;
  }
  char *part1 = (char *)calloc(PART_SIZE, sizeof(char));
  if (unlikely(!part1)) {
    err_code = MEM_ERR;
    err_message(MEM_ERR);
    return err_code;
  }
  char *part2 = (char *)calloc(PART_SIZE, sizeof(char));
  if (unlikely(!part1)) {
    free(part1);
    err_code = MEM_ERR;
    err_message(MEM_ERR);
    return err_code;
  }
  char *part3 = (char *)calloc(PART_SIZE, sizeof(char));
  if (unlikely(!part3)) {
    free(part1);
    free(part2);
    err_code = MEM_ERR;
    err_message(MEM_ERR);
    return err_code;
  }
  char *part4 = (char *)calloc(PART_SIZE, sizeof(char));
  if (unlikely(!part1)) {
    free(part1);
    free(part2);
    free(part3);
    err_code = MEM_ERR;
    err_message(MEM_ERR);
    return err_code;
  }
  for (int j = 0; j < PART_SIZE; j++)
    fscanf(f, "%c", &(part1[j]));
  for (int j = 0; j < PART_SIZE; j++)
    fscanf(f, "%c", &(part2[j]));
  for (int j = 0; j < PART_SIZE; j++)
    fscanf(f, "%c", &(part3[j]));
  for (int j = 0; j < PART_SIZE; j++)
    fscanf(f, "%c", &(part4[j]));
  fclose(f);

  char *part_between = between_parts(len_substr, part1, part2, part3, part4);
  
  task_args res = mult_threaded(part1, part2, part3, part4, part_between,
                               substr, len_substr);
  printf("Parallel result = %d", res.result);
  free_args(res);

  free(part1);
  free(part2);
  free(part3);
  free(part4);
  free(part_between);
  return 0;
}

int main (int argc, char *argv[]) {
  setbuf(stdout, NULL);
  int err_code = 0;
  if (argc < 2) {
    err_code = NO_FILENAME;
    err_message(err_code);
    return err_code;
  }
  printf("Enter substring you want to find in file: ");
  char *substr = (char *)calloc(MIN_SIZE, sizeof(char));
  if (unlikely(!substr)) {
    err_code = MEM_ERR;
    err_message(err_code);
    return err_code;
  }
  int len_substr = MIN_SIZE;
  int rc = read_string(&substr, &len_substr);
  if (unlikely(rc != OK)) {
    free(substr);
    err_message(rc);
    return rc;
  }

  serial(argv, substr, len_substr);
  parallel(argv, substr, len_substr);

  free(substr);
  return 0;
}
