#ifndef __PARALLEL_WORK__H__
#define __PARALLEL_WORK__H__

#ifdef ARR_EXPORTS
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

#define ARR_DECL __cdecl

#define PART_SIZE 26214400
#define ERROR_CREATE_THREAD -7
#define ERROR_JOIN_THREAD -8

typedef struct {
  int len;
  int i;
  char **parts;
  int amount_parts;
  int len_part;
  char *part_betw;
  char *str;
  int result;
} task_args;

ARR_DLL char ARR_DECL **create_parts(int amount_parts, int len_part);
ARR_DLL void ARR_DECL free_parts(char **parts);
ARR_DLL char ARR_DECL *between_parts(int len_mainstr, int len_str, int amount_parts,
					int len_part, char **parts);
ARR_DLL int ARR_DECL mult_threaded(int amount_parts, int len_part, char **parts,
						char *part_betw, char *string, int len_str);
ARR_DLL void ARR_DECL *thread_func(void *args);
#endif