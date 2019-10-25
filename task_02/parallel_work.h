#ifndef __PARALLEL_WORK__H__
#define __PARALLEL_WORK__H__

#define PART_SIZE 26214400
#define ERROR_CREATE_THREAD -7
#define ERROR_JOIN_THREAD -8

typedef struct task_args{
  int len;
  int i;
  char *part1;
  char *part2;
  char *part3;
  char *part4;
  char *part_betw;
  char *str;
  int result;
} task_args;

task_args mult_threaded(char part1[], char part2[], char part3[],
                        char part4[], char part_betw[], char string[], int len_str);
void *thread_func(void *args);
void free_args(task_args res);
#endif