#include "gtest/gtest.h"
#include "serial_work.h"
#include "parallel_work.h"
#include "err_codes.h"
#include <time.h>

TEST(comare_libs, empty_file)
{
  char str[] = {'y', 'e', 's'};
  int res_ser = serial("data/in_0.txt", str, 100, 3); 
  int res_parall = parallel("data/in_0.txt", str, 100, 3, 4);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_11_mainstr_100)
{
  char str[] = {'S', 'g', 'W', 't', 'X', 'd', 'd', 'k', 'j', 'p', 'u'};
  int res_ser = serial("data/in_1.txt", str, 100, 11); 
  int res_parall = parallel("data/in_1.txt", str, 100, 11, 4);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_10_mainstr_100_have)
{
  char str[] = {'j', 't', 'k', 'm', 'o', 'y', 'm', 'P', 'L', 'e'};
  int res_ser = serial("data/in_1.txt", str, 100, 10); 
  int res_parall = parallel("data/in_1.txt", str, 100, 10, 4);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_10_mainstr_100_notHave)
{
  char str[] = {'j', 't', 'k', 'l', 'l', 'l', 'l', 'P', 'L', 'e'};
  int res_ser = serial("data/in_1.txt", str, 100, 10); 
  int res_parall = parallel("data/in_1.txt", str, 100, 10, 4);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_3_mainstr_100)
{
  char str[] = {'j', 't', 'k'};
  int res_ser = serial("data/in_1.txt", str, 100, 3); 
  int res_parall = parallel("data/in_1.txt", str, 100, 3, 4);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_2_mainstr_100)
{
  char str[] = {'j', 't'};
  int res_ser = serial("data/in_1.txt", str, 100, 2); 
  int res_parall = parallel("data/in_1.txt", str, 100, 2, 4);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_1_mainstr_100)
{
  char str[] = {'j'};
  int res_ser = serial("data/in_1.txt", str, 100, 1); 
  int res_parall = parallel("data/in_1.txt", str, 100, 1, 4);
  ASSERT_EQ(res_ser, res_parall);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}