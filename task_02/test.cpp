#include "gtest/gtest.h"
#include "serial_work.h"
#include "parallel_work.h"
#include <time.h>

int create_string(char *string, int len) {
  srand(time(NULL));
  char symb[52] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o',
                  'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 
                  'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', 'Q', 'W',
                  'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S',
                  'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C',
                  'V', 'B', 'N', 'M'};
  for (int i = 0; i < len; i++) {
      int a = rand() % 52;
      string[i] = symb[a];
  }
  return 0;
}

TEST(comare_libs, len_is_null)
{
  char str[] = "yes";
  int res_ser = serial("data/in_0.txt", substr, SIZE, len_substr); 
  int res_parall = parallel("data/in_0.txt", substr, SIZE, len_substr);
  ASSERT_EQ(2, 2);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}