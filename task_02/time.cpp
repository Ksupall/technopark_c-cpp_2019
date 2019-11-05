#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <iostream>

#include "err_codes.h"
#include "parallel_work.h"
#include "serial_work.h"

//  Windows
#ifdef _WIN32

#include <intrin.h>
uint64_t rdtsc() {
  return __rdtsc();
}

//  Linux/GCC
#else

uint64_t rdtsc() 
{
  unsigned int lo, hi;
  __asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
  return ((uint64_t)hi << 32) | lo;
}

#endif

int main () {
  setbuf(stdout, NULL);
  const char *filename[] = {"data/in_1.txt", "data/in_2.txt",
                            "data/in_3.txt", "data/in_4.txt"};
  int len_mainstr[] = {100, 200, 300, 400};
  //int amount_threads[] = {1, 2, 3, 4};
  char *substr = (char *)calloc(4, sizeof(int));
  substr[0] = 'b';
  substr[1] = 'i';
  substr[2] = 'k';
  substr[3] = 'e';
  int len_substr = 4;

  unsigned __int64 average_time_parall[] = {0, 0, 0, 0};
  unsigned __int64 average_time_serial[] = {0, 0, 0, 0};

  for (int i = 0; i < 4; i++) {
    unsigned __int64 startTime = 0, endTime = 0;
    for (int j = 0; j < 100; j++) {
      startTime = rdtsc();
      parallel(filename[i], substr, len_mainstr[i],
                                 len_substr, 4);
      endTime = rdtsc();
      average_time_parall[i] += endTime - startTime;
    }
    average_time_parall[i] /= 100;
  }

  for (int i = 0; i < 4; i++) {
    unsigned __int64 startTime = 0, endTime = 0;
    for (int j = 0; j < 100; j++) {
      startTime = rdtsc();
      serial(filename[i], substr, len_mainstr[i], len_substr);
      endTime = rdtsc();
      average_time_serial[i] += endTime - startTime;
    }
    average_time_serial[i] /= 100;
  }

  for (int i = 0; i < 4; i++) {
    std::cout << (i + 1) * 100 << " " << average_time_serial[i] << " " << average_time_parall[i] << std::endl;
  }
  free(substr);
  return 0;
}