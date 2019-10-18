#ifndef __SRUCT__H__
#define __SRUCT__H__

#define OK 0
#define NO_FILENAME -1
#define ERR_FILE -2
#define EMPTY_FILE -3
#define WRONG_FILE -4
#define WRONG_DATE -5
#define WRONG_YEAR -6
#define WRONG_MONTH -7
#define WRONG_DAY -8
#define FUTURE_DATE -9
#define ERR_MEMORY -10

#define NAME_LEN 50
#define CLASS_LEN 80
#define VERSION_LEN 10

typedef struct {
	int day;
	int month;
	int year;
} date_t;

typedef struct {
	char name[NAME_LEN];
	char class_name[CLASS_LEN];
	char version[VERSION_LEN];
	date_t install_date;
	date_t update_date;
} product_t;

int check_date(int d, int m, int y);
int read_from_file(FILE **fin, product_t **p, int *amount);
void output(product_t *prod, int amount);
int sort_by_key(product_t *prod, int amount);
void print_products(product_t *prod, int amount);

#endif