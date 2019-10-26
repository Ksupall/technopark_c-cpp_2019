#include "gtest/gtest.h"
#include "serial_work.h"
#include "parallel_work.h"
#include "err_codes.h"
#include <time.h>

TEST(comare_libs, empty_file)
{
  char str[] = {'y', 'e', 's'};
  int res_ser = serial("data/in_0.txt", str, 100, 3); 
  int res_parall = parallel("data/in_0.txt", str, 100, 3);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_3_mainstr_100)
{
  char str[] = {'j', 't', 'k'};
  int res_ser = serial("data/in_1.txt", str, 100, 3); 
  int res_parall = parallel("data/in_1.txt", str, 100, 3);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_2_mainstr_100)
{
  char str[] = {'j', 't'};
  int res_ser = serial("data/in_1.txt", str, 100, 2); 
  int res_parall = parallel("data/in_1.txt", str, 100, 2);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_1_mainstr_100)
{
  char str[] = {'j'};
  int res_ser = serial("data/in_1.txt", str, 100, 3); 
  int res_parall = parallel("data/in_1.txt", str, 100, 3);
  ASSERT_EQ(res_ser, res_parall);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}