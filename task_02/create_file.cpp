#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main () {
	srand(time(NULL));
	char symb[52] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o',
				'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 
				'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', 'Q', 'W',
				'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S',
				'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C',
				'V', 'B', 'N', 'M'};
	FILE *f;
	f = fopen("in_1.txt", "w");
	if (!f)
		printf("Couldn't find file!\n");
	for (int i = 0; i < 100; i++)
	{
		int a = rand() % 52;
		fprintf(f, "%c", symb[a]);
	}
	fclose(f);
	
	return 0;
}