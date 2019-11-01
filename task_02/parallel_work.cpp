#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "err_codes.h"
#include "parallel_work.h"

#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr) __builtin_expect(!!(expr), 1)

char **create_parts(int amount_parts, int len_part)
{
  char *data = (char *)calloc(amount_parts * len_part, sizeof(char));
  if (unlikely(!data)) {
    free(data);
    return NULL;
  }
  char **parts = (char **)calloc(amount_parts, sizeof(char *));
  if (unlikely(!parts)) {
    free(data);
    free(parts);
    return NULL;
  }
  for (int i = 0; i < amount_parts; i++)
  	parts[i] = data + i * len_part;
  return parts;
}

void free_parts(char **parts)
{
	free(parts[0]);
	free(parts);
}

// функция, которая составляет строку из кусочков строк, берет значения на границе,
//чтобы ничего не упустить
char *between_parts(int len_mainstr, int len_str, int amount_parts,
					int len_part, char **parts)
{
  char *part_between = (char *)calloc((len_str - 1) * (amount_parts - 1) * 2, sizeof(char));
  if (unlikely(!part_between)) {
    free(part_between);	  
    return NULL;
  }
  int j = 0;
  // конец первой части
  for (int i =  len_mainstr - len_str + 1; i < len_mainstr; i++)
    part_between[j++] = parts[0][i];

  for (int i = 1; i < amount_parts - 1; i++) {
    for (int k = 0; k < len_str - 1; k++)
      part_between[j++] = parts[i][k];
    for (int n = len_mainstr - len_str + 1; n < len_mainstr; n++)
      part_between[j++] = parts[i][n];
  }
  
  // начало последней части
  for (int i = 0; i < len_str - 1; i++)
    part_between[j++] = parts[amount_parts-1][i];
  printf("j = %d k = %d\n", j, (len_str - 1) * (amount_parts - 1) * 2);
  return part_between;
}

int parallel(char *argv, char *substr, int len_mainstr, int len_substr, 
			int amount_parts) {
  int err_code = 0;
  FILE *f = fopen(argv, "r");
  if (unlikely(!f)) {
    err_code = ERR_FILE;
    err_message(err_code);
	fclose(f);
    return err_code;
  }
  int len_part = len_mainstr / amount_parts;
  char **parts = create_parts(amount_parts, len_part);
  if (unlikely(!parts)) {
    err_code = MEM_ERR;
	err_message(err_code);
	fclose(f);
	return err_code;
  }
  for (int i = 0; i < amount_parts; i++)
    for (int j = 0; j < len_part; j++)
      fscanf(f, "%c", &(parts[i][j]));
  fclose(f);
  printf("here!\n");
  char *part_between = between_parts(len_mainstr, len_substr, 
									amount_parts, len_part, parts);
  
  task_args res = mult_threaded(amount_parts, len_part, parts, part_between,
                               substr, len_substr);
  int result = res.result;
  free_args(res);

  free_parts(parts);
  free(part_between);
  return result;
}

void *thread_func(void *args) {
  assert(args);
  task_args *arg = (task_args *) args;
  int len_str = strlen(arg->str);
  int number_part = arg->i;
  arg->i += 1;
  for (int i = 0; i < arg->len - len_str + 1; i++)
    for (int j = 0; j < len_str; j++) {
	  if (arg->str[j] != arg->parts[number_part][i+j])
	    break;
	  else if (j == len_str - 1)
	    arg->result += 1;
    }
  return NULL;
}

task_args mult_threaded(int amount_parts, int len_part, char **parts,
						char *part_betw, char *string, int len_str) {
  pthread_t *threads = (pthread_t *)calloc(amount_parts, sizeof(pthread_t)); // 4 потока, так как компьютер имеет 4 ядра
  int status;
  int status_addr;
  task_args args;
  if (unlikely(len_str == 0)) {
    args.result = ZERO_SUBSTR;
    free(threads);
    return args;
  }
  args.parts = create_parts(amount_parts, len_part);
  if (unlikely(!args.parts))
	  err_message(MEM_ERR);
  args.part_betw = (char *)calloc(((len_str-1) * (amount_parts - 1) * 2), sizeof(char));
  if (unlikely(!part_betw))
    err_message(MEM_ERR);
  for (int i = 0; i < amount_parts; i++)
    for (int j = 0; j < len_part; j++)
		args.parts[i][j] = parts[i][j];
  for (int i = 0; i < ((len_str-1) * (amount_parts - 1) * 2); i++)
    args.part_betw[i] = part_betw[i];
  args.str = (char *)calloc(len_str, sizeof(char));
  if (unlikely(!part_betw))
    err_message(MEM_ERR);
  for (int i = 0; i < len_str; i++)
    args.str[i] = string[i];
  args.i = 0;
  args.result = 0;
  args.len = len_part;
  args.amount_parts = amount_parts;
  args.len_part = len_part;

  for (int i = 0; i < amount_parts; i++) {
    status = pthread_create(&(threads[i]), NULL, thread_func, (void*) &args);
    if (status != OK) {
      printf("main error: can't create thread %d, status = %d\n", i, status);
      exit(ERROR_CREATE_THREAD);
    }
  }
  for (int i = 0; i < amount_parts; i++) {
    status = pthread_join(threads[i], (void**)&status_addr);
    if (status != OK) {
      printf("main error: can't join thread %d, status = %d\n", i, status);
      exit(ERROR_JOIN_THREAD);
    }
  }
  int len_between = (len_str-1) * (amount_parts - 1) * 2;
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
  free_parts(res.parts);
}