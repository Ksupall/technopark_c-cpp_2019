#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "err_codes.h"
#include "parallel_work.h"
#include <pthread.h>

#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr) __builtin_expect(!!(expr), 1)

char **create_parts(int amount_parts, int len_part)
{
	char *data = (char *)calloc(amount_parts * len_part, sizeof(char));
	if (unlikely(!data))
		return NULL;
	char **parts = (char **)calloc(amount_parts, sizeof(char *));
	if (unlikely(!parts))
		return NULL;
	for (int i = 0; i < amount_parts; i++)
		parts[i] = data + i * len_part;
	return parts;
}

// функция, которая составляет строку из кусочков строк, берет значения на границе,
//чтобы ничего не упустить
char *between_parts(int len_mainstr, int len_str, int amount_parts,
					int len_part, char **parts)
{
  char *part_between = (char *)calloc((len_str - 1) * (amount_parts - 1) * 2), sizeof(char));
  if (unlikely(!part_between))
    return NULL;
  int j = 0;
  // конец первой части
  for (int i =  len_mainstr - len_str + 1; i <  len_mainstr; i++)
    part_between[j++] = parts[0][i];

  for (int i = 1; i < amount_parts - 1; i++) {
    for (int k = 0; k < len_str - 1; k++)
      part_between[j++] = parts[i][k];
    for (int k =  len_mainstr + 1 - len_str; k <  len_mainstr; k++)
      part_between[j++] = parts[i][k];
  }
  
  // начало последней части
  for (int i = 0; i < len_str - 1; i++)
    part_between[j++] = parts[amount_parts-1][i];
  return part_between;
}

int parallel(char *argv, char *substr, int len_mainstr, int len_substr) {
  int err_code = 0;
  FILE *f = fopen(argv, "r");
  if (unlikely(!f)) {
    err_code = ERR_FILE;
    err_message(err_code);
    return err_code;
  }
  int amount_parts = 4;
  int len_part = len_mainstr / amount_parts;
  char **parts = create_parts(amount_parts, len_part);
  if (unlikely(!parts)) {
    err_code = MEM_ERR;
	err_message(err_code);
	return err_code;
  }
  for (int i = 0; i < amount_parts; i++)
    for (int j = 0; j < len_part; j++)
      fscanf(f, "%c", &(parts[i][j]));
  fclose(f);

  char *part_between = between_parts(len_mainstr, len_substr, 
									amount_parts, len_part, parts);
  
  task_args res = mult_threaded(part1, part2, part3, part4, part_between,
                               substr, len_part, len_substr);
  int result = res.result;
  free_args(res);

  free(part1);
  free(part2);
  free(part3);
  free(part4);
  free(part_between);
  return result;
}

void *thread_func(void *args) {
  task_args *arg = (task_args *) args;
  int len_str = strlen(arg->str);
  arg->i += 1;
  if (arg->i == 1) {
    for (int i = 0; i < arg->len - len_str + 1; i++)
      for (int j = 0; j < len_str; j++) {
        if (arg->str[j] != arg->part1[i+j])
          break;
        else if (j == len_str - 1)
          arg->result += 1;
      }
  }
  else if (arg->i == 2) {
    for (int i = 0; i < arg->len - len_str + 1; i++)
      for (int j = 0; j < len_str; j++) {
        if (arg->str[j] != arg->part2[i+j])
          break;
        else if (j == len_str - 1)
          arg->result += 1;
      }
  }
  else if (arg->i == 3) {
    for (int i = 0; i < arg->len - len_str + 1; i++)
      for (int j = 0; j < len_str; j++) {
        if (arg->str[j] != arg->part3[i+j])
          break;
        else if (j == len_str - 1)
          arg->result += 1;
      }
  }
  else if (arg->i == 4) {
    for (int i = 0; i < arg->len - len_str + 1; i++)
      for (int j = 0; j < len_str; j++) {
        if (arg->str[j] != arg->part4[i+j])
          break;
        else if (j == len_str - 1)
          arg->result += 1;
      }
  }
  return NULL;
}

task_args mult_threaded(char *part1, char *part2, char *part3,
                        char *part4, char *part_betw, char *string,
                        int len_part, int len_str) {
  pthread_t *threads = (pthread_t *)calloc(4, sizeof(pthread_t)); // 4 потока, так как компьютер имеет 4 ядра
  int status;
  int status_addr;
  task_args args;
  if (unlikely(len_str == 0)) {
    args.result = ZERO_SUBSTR;
    return args;
  }
  args.part1 = (char *)calloc(len_part, sizeof(char));
  if (unlikely(!part1))
    err_message(MEM_ERR);
  args.part2 = (char *)calloc(len_part, sizeof(char));
  if (unlikely(!part1))
    err_message(MEM_ERR);
  args.part3 = (char *)calloc(len_part, sizeof(char));
  if (unlikely(!part3))
    err_message(MEM_ERR);
  args.part4 = (char *)calloc(len_part, sizeof(char));
  if (unlikely(!part1))
    err_message(MEM_ERR);
  args.part_betw = (char *)calloc((len_str-1) * 6, sizeof(char));
  if (unlikely(!part_betw))
    err_message(MEM_ERR);
  for (int i = 0; i < len_part; i++) {
    args.part1[i] = part1[i];
    args.part2[i] = part2[i];
    args.part3[i] = part3[i];
    args.part4[i] = part4[i];
  }
  for (int i = 0; i < (len_str-1) * 6; i++)
    part_betw[i] = part_betw[i];
  args.str = (char *)calloc(len_str, sizeof(char));
  if (unlikely(!part_betw))
    err_message(MEM_ERR);
  for (int i = 0; i < len_str; i++)
    args.str[i] = string[i];
  args.i = 0;
  args.result = 0;
  args.len = len_part;

  for (int i = 0; i < 4; i++) {
    status = pthread_create(&(threads[i]), NULL, thread_func, (void*) &args);
    if (status != OK) {
      printf("main error: can't create thread %d, status = %d\n", i, status);
      exit(ERROR_CREATE_THREAD);
    }
  }
  for (int i = 0; i < 4; i++) {
    status = pthread_join(threads[i], (void**)&status_addr);
    if (status != OK) {
      printf("main error: can't join thread %d, status = %d\n", i, status);
      exit(ERROR_JOIN_THREAD);
    }
  }
  int len_between = (len_str - 1) * 6;
  for (int i = 0; i < len_between - len_str + 1; i++)
    for (int j = 0; j < len_str; j++) {
      if (args.str[j] != args.part_betw[i+j])
        break;
      else if (j == len_str - 1)
        args.result += 1;
    }
  free(threads);
  return args;
}

void free_args(task_args res) {
  free(res.str);
  free(res.part_betw);
  free(res.part4);
  free(res.part3);
  free(res.part2);
  free(res.part1);
}