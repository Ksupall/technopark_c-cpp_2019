#ifndef __PARALLEL_WORK__H__
#define __PARALLEL_WORK__H__

#define PART_SIZE 26214400
#define ERROR_CREATE_THREAD -7
#define ERROR_JOIN_THREAD -8

typedef struct task_args{
  int len;
  int i;
  char **parts;
  int amount_parts;
  int len_part;
  char *part_betw;
  char *str;
  int result;
} task_args;

char **create_parts(int amount_parts, int len_part);
void free_parts(char **parts);
char *between_parts(int len_mainstr, int len_str, int amount_parts,
					int len_part, char **parts)
int parallel(char *argv, char *substr, int len_mainstr, int len_substr);
task_args mult_threaded(int amount_parts, int len_part, char **parts,
						char *part_betw, char *string, int len_part,
						int len_str);
void *thread_func(void *args);
void free_args(task_args res);
#endif