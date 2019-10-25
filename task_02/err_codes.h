#ifndef __ERR__CODES__H__
#define __ERR__CODES__H__

#define OK 0
#define NO_FILENAME -1
#define ERR_FILE -2
#define MEM_ERR -3
#define ZERO_MAINSTR -4
#define ZERO_SUBSTR -5
#define ERR -6

void err_message(int code);

#endif