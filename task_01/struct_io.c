#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct_io.h"

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


//вывод на экран результата задачи
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

// вывод на экран всего списка
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