#ifndef __STRUCT__H__
#define __STRUCT__H__

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

int check_date(int d, int m, int y)
{
	struct tm *tim;
	time_t tt = time(NULL);
	tim = localtime(&tt);
	
	if (y < 1990)
		return WRONG_YEAR;
	if (m < 0 || m > 12)
		return WRONG_MONTH;
	if (d < 0 || d > 31)
		return WRONG_DAY;
	if (y > tim->tm_year + 1900)
		return FUTURE_DATE;
	if (y == tim->tm_year + 1900 && m > tim->tm_mon + 1)
		return FUTURE_DATE;
	if (y == tim->tm_year + 1900 && m == tim->tm_mon + 1 && d > tim->tm_mday)
		return FUTURE_DATE;
	if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30)
		return WRONG_DATE;
	if (m == 2 && d > 28)
		return WRONG_DATE;
	return 0;
}

int sort_by_key(product_t *prod, int amount)
{
	printf("%d \n", amount);
	for(int i = 1; i < amount; i++)
        for(int j = 0; j < amount - i; j++)
            if(strcmp(prod[j].class_name, prod[j+1].class_name) > 0)
			{
				product_t str;
                str =  prod[j];
                prod[j] = prod[j+1];
                prod[j+1] = str;
			}
	for(int i = 1; i < amount; i++)
        for(int j = 0; j < amount - i; j++)
            if(strcmp(prod[j].class_name, prod[j+1].class_name) == 0 
				&& strcmp(prod[j].name, prod[j+1].name) > 0)
			{
				product_t str;
                str =  prod[j];
                prod[j] = prod[j+1];
                prod[j+1] = str;
			}
	return 0;
}
#endif