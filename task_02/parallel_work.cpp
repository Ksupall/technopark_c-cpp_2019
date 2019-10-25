#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "err_codes.h"
#include "parallel_work.h"
#include <pthread.h>

#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr) __builtin_expect(!!(expr), 1)

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
                        char *part4, char *part_betw, char *string, int len_str) {
  pthread_t *threads = (pthread_t *)calloc(4, sizeof(pthread_t)); // 4 потока, так как компьютер имеет 4 ядра
  int status;
  int status_addr;
  task_args args;
  int err_code = 0;
  args.part1 = (char *)calloc(PART_SIZE, sizeof(char));
  if (unlikely(!part1)) {
    err_code = MEM_ERR;
    err_message(MEM_ERR);
    return err_code;
  }
  args.part2 = (char *)calloc(PART_SIZE, sizeof(char));
  if (unlikely(!part1)) {
    free(part1);
    err_code = MEM_ERR;
    err_message(MEM_ERR);
    return err_code;
  }
  args.part3 = (char *)calloc(PART_SIZE, sizeof(char));
  if (unlikely(!part3)) {
    free(part1);
    free(part2);
    err_code = MEM_ERR;
    err_message(MEM_ERR);
    return err_code;
  }
  args.part4 = (char *)calloc(PART_SIZE, sizeof(char));
  if (unlikely(!part1)) {
    free(part1);
    free(part2);
    free(part3);
    err_code = MEM_ERR;
    err_message(MEM_ERR);
    return err_code;
  }
  args.part_betw = (char *)calloc((len_str-1) * 6, sizeof(char));
  if (unlikely(!part_betw)) {
    free(part1);
    free(part2);
    free(part3);
    free(part4);
    err_code = MEM_ERR;
    err_message(MEM_ERR);
    return err_code;
  }
  for (int i = 0; i < PART_SIZE; i++) {
    args.part1[i] = part1[i];
    args.part2[i] = part2[i];
    args.part3[i] = part3[i];
    args.part4[i] = part4[i];
  }
  for (int i = 0; i < (len_str-1) * 6; i++)
    part_betw[i] = part_betw[i];
  args.str = (char *)calloc(len_str, sizeof(char));
  if (unlikely(!part_betw)) {
    free(part1);
    free(part2);
    free(part3);
    free(part4);
    free(part_betw);
    err_code = MEM_ERR;
    err_message(MEM_ERR);
    return err_code;
  }
  for (int i = 0; i < len_str; i++)
    args.str[i] = string[i];
  args.i = 0;
  args.result = 0;
  args.len = PART_SIZE;

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