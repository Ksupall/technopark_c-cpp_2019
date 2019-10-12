#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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


int read_from_file(FILE **fin, product_t **p, int *amount)
{
	int a1 = 0, a2 = 0, a3 = 0, am = 0;
	int i = 0, sc, rc;
	char temp;
	int day, month, year;
	
	sc = fscanf(*fin, "%d\n", amount);
	if (sc == EOF)
		return EMPTY_FILE;
	if (sc != 1 || (*amount) < 0)
		return WRONG_FILE;
	*p = (product_t *)calloc(*amount, sizeof(product_t));
	if (!(*p))
		return ERR_MEMORY;
	do
	{
		sc = fscanf(*fin,"%c", &temp);
		if (sc != EOF && temp == '|')
			am++;
		if (sc != EOF && temp != '\n' && temp != '|')
		{
			if (am == 0)
				(*p)[i].name[a1++] = temp;
			if (am == 1)
				(*p)[i].class_name[a2++] = temp;
			if (am == 2)
				(*p)[i].version[a3++] = temp;
			if (am == 3)
			{
				rc = fscanf(*fin, " %d.%d.%d", &day, &month, &year);
				int code = check_date(day, month, year);
				if (rc != 3 || code != OK)
					return code;
				(*p)[i].install_date.day = day;
				(*p)[i].install_date.month = month;
				(*p)[i].install_date.year = year;
				char up;
				rc  = fscanf(*fin, "%c", &up);
				if (up == '-')
				{
					(*p)[i].update_date.day = 0;
					(*p)[i].update_date.month = 0;
					(*p)[i].update_date.year = 0;
				}
				else
				{
					rc = fscanf(*fin, " %d.%d.%d", &day, &month, &year);
					int code = check_date(day, month, year);
					if (rc != 3 || code != 0)
						return code;
					(*p)[i].update_date.day = day;
					(*p)[i].update_date.month = month;
					(*p)[i].update_date.year = year;
				}
			}
		}
		if (sc == EOF || temp == '\n')
		{
			(*p)[i].name[a1] = '\0';
			(*p)[i].class_name[a2] = '\0';
			(*p)[i].version[a3] = '\0';
			i++;
			a1 = 0;
			a2 = 0;
			a3 = 0;
			am = 0;
		}
	}
	while (sc != EOF);
	return OK;
}

void output(product_t *prod, int amount)
{
	struct tm *tim;
	time_t tt = time(NULL);
	tim = localtime(&tt);
	int day = tim->tm_mday;
	int month;
	int year;
	if (tim->tm_mon - 5 > 0)
	{
		month = tim->tm_mon - 5;
		year = tim->tm_year + 1900;
	}
	else
	{
		month = 12 - (tim->tm_mon - 5);
		year = tim->tm_year + 1900 - 1;
	}
	for (int i = 0; i < amount; i++)
	{
		int i_d = prod[i].install_date.day;
		int i_m = prod[i].install_date.month;
		int i_y = prod[i].install_date.year;
		int u_d = prod[i].update_date.day;
		if (u_d == 0 && (i_y < year || 
		(i_d <= day && i_m <= month && i_y == year) || (i_d > day && i_m < month && i_y == year)))
		{
			printf("%-4d%-15s\t%-20s\t%-10s", i+1, prod[i].name,
			prod[i].class_name, prod[i].version);
			if (i_d >= 10 && i_m >= 10)
				printf("\t%d.%d.%d", i_d, i_m, i_y);
			else if (i_d >= 10 && i_m < 10)
				printf("\t%d.0%d.%d", i_d, i_m, i_y);
			else if (i_d < 10 && i_m >= 10)
				printf("\t0%d.%d.%d", i_d, i_m, i_y);
			else if (i_d < 10 && i_m < 10)
				printf("\t0%d.0%d.%d", i_d, i_m, i_y);
			printf("\t----------\n");
		}
	}
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

void error_message(int code)
{
	if (code == NO_FILENAME)
		printf("No filename!\n");
	else if (code == ERR_FILE)
		printf("Couldn't open file!\n");
	else if (code == EMPTY_FILE)
		printf("File is empty!\n");
	else if (code == WRONG_FILE)
		printf("File has wrong construction!\n");
	else if (code == WRONG_YEAR)
		printf("Wrong year!\n");
	else if (code == WRONG_MONTH)
		printf("Wrong month!\n");
	else if (code == WRONG_DAY)
		printf("Wrong day!\n");
	else if (code == FUTURE_DATE)
		printf("Future date!\n");
	else if (code == WRONG_DATE)
		printf("Date is wrong!\n");
	else if (code == ERR_MEMORY)
		printf("Memory allocation error!\n");
}

void print_products(product_t *prod, int amount)
{
	printf("\n№      NAME\t\t  FUNCTION CLASS\tVERSION\t\tINSTALL DATE\tUPDATE DATE\n\n");
	for (int i = 0; i < amount; i++)
	{
		int i_d = prod[i].install_date.day;
		int i_m = prod[i].install_date.month;
		int i_y = prod[i].install_date.year;
		int u_d = prod[i].update_date.day;
		int u_m = prod[i].update_date.month;
		int u_y = prod[i].update_date.year;
		printf("%-4d%-15s\t%-20s\t%-10s", i+1, prod[i].name,
		prod[i].class_name, prod[i].version);
		if (i_d >= 10 && i_m >= 10)
			printf("\t%d.%d.%d", i_d, i_m, i_y);
		else if (i_d >= 10 && i_m < 10)
			printf("\t%d.0%d.%d", i_d, i_m, i_y);
		else if (i_d < 10 && i_m >= 10)
			printf("\t0%d.%d.%d", i_d, i_m, i_y);
		else if (i_d < 10 && i_m < 10)
			printf("\t0%d.0%d.%d", i_d, i_m, i_y);
		if (u_d == 0)
			printf("\t----------\n");
		else
		{
			if (u_d >= 10 && u_m >= 10)
				printf("\t%d.%d.%d\n", u_d, u_m, u_y);
			else if (u_d >= 10 && u_m < 10)
				printf("\t%d.0%d.%d\n", u_d, u_m, u_y);
			else if (u_d < 10 && u_m >= 10)
				printf("\t0%d.%d.%d\n", u_d, u_m, u_y);
			else if (u_d < 10 && u_m < 10)
				printf("\t0%d.0%d.%d\n", u_d, u_m, u_y);
		}
	}
}

void test()
{
	int err_code = 0;
	setbuf(stdout, NULL);
	char filename[20] = "../in_0.txt";
	FILE *fin = fopen(filename, "r");
	if (!fin)
	{
		err_code = ERR_FILE;
		error_message(err_code);
		return;
	}
	int amount;
	product_t *prod = NULL;
	err_code = read_from_file(&fin, &prod, &amount);
	if (err_code != OK)
	{
		error_message(err_code);
		fclose(fin);
		free(prod);
		return;
	}
	fclose(fin);
	sort_by_key(prod, amount);
	output(prod, amount);
	free(prod);
}

int main()
{
	test();
	return 0;
}