#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 0
#define ERR_FILE -1

int main () {
  srand(time(NULL));
  char four_symb[20][5] = {"tree", "foot", "door", "bear", "vibe",
                          "neck", "rose", "week", "bike", "beer",
                          "road", "year", "kite", "wine", "fork",
                          "cock", "page", "sign", "leaf", "wind"};
						  /*
  char five_symb[35][6] = {"abuse", "acock", "alarm", "alien", "allow",
                          "along", "alley", "beach", "below", "bench",
                          "belly", "berry", "candy", "chalk", "chaos",
                          "clock", "death", "drive", "drink", "extra",
                          "excel", "exist", "fabre", "fifty", "flash",
                          "grass", "grape", "graph", "horse", "hotel",
                          "kitty", "large", "level", "mixer", "model"};
  char symb[52] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o',
                  'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 
                  'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', 'Q', 'W',
                  'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S',
                  'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C',
                  'V', 'B', 'N', 'M'};
				  */
  FILE *f = fopen("data/in_1.txt", "w");
  if (!f) {
    printf("Couldn't find file!\n");
    return ERR_FILE;
  }
  for (int i = 0; i < 25; i++) {
    int a = rand() % 20;
    fprintf(f, "%s", four_symb[a]);
  }
  fclose(f);
  return OK;
}