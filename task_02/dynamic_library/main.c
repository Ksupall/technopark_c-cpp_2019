#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MIN_SIZE 10

#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr) __builtin_expect(!!(expr), 1)

#define OK 0
#define NO_FILENAME -1
#define ERR_FILE -2
#define MEM_ERR -3
#define ZERO_MAINSTR -4
#define ZERO_SUBSTR -5
#define ERR -6

typedef int (__cdecl *fn_read_string_t)(char **, int *);
typedef int (__cdecl *fn_find_matchings_t)(char *, char *, int , int );
typedef char** (__cdecl *fn_create_parts_t)(int , int );
typedef void (__cdecl *fn_free_parts_t)(char **);
typedef char* (__cdecl *fn_between_parts_t)(int , int , int , int , char **);
typedef int (__cdecl *fn_mult_threaded_t)(int , int , char **,
						char *, char *, int );

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

int serial(const char *argv, char *substr, int len_mainstr, int len_substr) {
  HMODULE hlib;
  fn_find_matchings_t find_matchings;

  hlib = LoadLibrary("lib.dll");
  if (!hlib){
    printf("Cannot open library!\n");
    return ERR;
  }
  find_matchings = (fn_find_matchings_t) GetProcAddress(hlib, "find_matchings");
  if (!find_matchings) {
    printf("Cannot load function find_mathcings!\n");
    return ERR;   
  }

  int err_code = 0;
  FILE *f;
  f = fopen(argv, "r");
  if (unlikely(!f)) {
    err_code = ERR_FILE;
    err_message(err_code);
	fclose(f);
    return err_code;
  }
  char *mainstr = (char *)calloc(len_mainstr, sizeof(char));
  if (unlikely(!mainstr)) {
    err_code = MEM_ERR;
    err_message(err_code);
    free(mainstr);
	fclose(f);
    return err_code;
  }
  for (int i = 0; i < len_mainstr; i++)
    fscanf(f, "%c", &(mainstr[i]));
  fclose(f);
  int result = find_matchings(mainstr, substr, len_mainstr, len_substr); 
  free(mainstr);
  return result;
}

int parallel(const char *argv, char *substr, int len_mainstr, int len_substr, 
			int amount_parts) {
  HMODULE hlib;
  fn_create_parts_t create_parts;
  fn_between_parts_t between_parts;
  fn_mult_threaded_t mult_threaded;
  fn_free_parts_t free_parts;
  fn_read_string_t read_string;
  
  hlib = LoadLibrary("lib.dll");
  if (!hlib){
    printf("Cannot open library!\n");
    return ERR;
  }
  
  create_parts = (fn_create_parts_t) GetProcAddress(hlib, "create_parts");
  between_parts = (fn_between_parts_t) GetProcAddress(hlib, "between_parts");
  mult_threaded = (fn_mult_threaded_t) GetProcAddress(hlib, "mult_threaded");
  free_parts = (fn_free_parts_t) GetProcAddress(hlib, "free_parts");
  read_string = (fn_read_string_t) GetProcAddress(hlib, "read_string");
 
  if (!create_parts || !between_parts || !mult_threaded || !free_parts ||
    !read_string) {
    printf("Cannot load functions for parallel work!\n");
    return ERR;
  }
  
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
  char *part_between = between_parts(len_mainstr, len_substr, 
									amount_parts, len_part, parts);
  
  int result = mult_threaded(amount_parts, len_part, parts, part_between,
                               substr, len_substr);

  free_parts(parts);
  free(part_between);
  return result;
}

int main () {
  HMODULE hlib;
  fn_read_string_t read_string;
  
  hlib = LoadLibrary("lib.dll");
  if (!hlib){
    printf("Cannot open library!\n");
    return ERR;
  }

  read_string = (fn_read_string_t) GetProcAddress(hlib, "read_string");
 
  if (!read_string) {
    printf("Cannot load function read_string!\n");
    return ERR;
  }

  setbuf(stdout, NULL);
  const char *filename[] = {"data/in_2.txt"};
  printf("Enter substring you want to find in file: ");
  char *substr = (char *)calloc(MIN_SIZE, sizeof(char));
  if (unlikely(!substr)) {
    err_message(MEM_ERR);
	free(substr);
    return MEM_ERR;
  }
  int len_substr = MIN_SIZE;
  int rc = read_string(&substr, &len_substr);
  if (unlikely(rc != OK)) {
    free(substr);
    err_message(rc);
    return rc;
  }
  int amount_threads = 0;
  printf("Enter amount of threads: ");
  scanf("%d", &amount_threads);
  int res_ser = serial(filename[0], substr, 200, len_substr);
  printf("Serial result = %d\n", res_ser); 
  int res_parall = parallel(filename[0], substr, 200, len_substr, amount_threads);
  printf("Parallel result = %d", res_parall);

  free(substr);
  return 0;
}
