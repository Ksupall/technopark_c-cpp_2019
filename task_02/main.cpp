#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "err_codes.h"
#include "parallel_work.h"
#include "serial_work.h"

#define SIZE 104857600 //столько символов в файле 100Мб
#define PART_SIZE 26214400 //разбила все эти символы на 4 потока
#define MIN_SIZE 10

#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr) __builtin_expect(!!(expr), 1)

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
	free(substr);
    return err_code;
  }
  int len_substr = MIN_SIZE;
  int rc = read_string(&substr, &len_substr);
  if (unlikely(rc != OK)) {
    free(substr);
    err_message(rc);
    return rc;
  }
  int amount_threads = 4;
  printf("Enter amount of threads: ");
  scanf("%d", &amount_threads);
  int res_ser = serial(argv[1], substr, SIZE, len_substr);
  printf("Serial result = %d\n", res_ser); 
  int res_parall = parallel(argv[1], substr, SIZE, len_substr, amount_threads);
  printf("Parallel result = %d", res_parall);

  free(substr);
  return 0;
}
