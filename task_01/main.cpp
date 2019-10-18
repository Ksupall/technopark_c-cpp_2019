#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.hpp"

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

int main()
{
	int err_code = 0;
	setbuf(stdout, NULL);
	char filename[20] = "../in_0.txt";
	FILE *fin = fopen(filename, "r");
	if (!fin)
	{
		err_code = ERR_FILE;
		error_message(err_code);
		return err_code;
	}
	int amount;
	product_t *prod = NULL;
	err_code = read_from_file(&fin, &prod, &amount);
	if (err_code != OK)
	{
		error_message(err_code);
		fclose(fin);
		free(prod);
		return err_code;
	}
	fclose(fin);
	sort_by_key(prod, amount);
	output(prod, amount);
	free(prod);
	return 0;
}