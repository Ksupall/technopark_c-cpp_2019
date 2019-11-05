#include "err_codes.h"
#include "gtest/gtest.h"
#include "parallel_work.h"
#include "serial_work.h"
#include <time.h>

TEST(comare_libs, empty_file)
{
  char str[] = {'y', 'e', 's'};
  int res_ser = serial("data/in_0.txt", str, 100, 3); 
  int res_parall = parallel("data/in_0.txt", str, 100, 3, 4);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_11_threads_4)
{
  char str[] = {'S', 'g', 'W', 't', 'X', 'd', 'd', 'k', 'j', 'p', 'u'};
  int res_ser = serial("data/in_1.txt", str, 100, 11); 
  int res_parall = parallel("data/in_1.txt", str, 100, 11, 4);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_10_threads_4_have)
{
  char str[] = {'j', 't', 'k', 'm', 'o', 'y', 'm', 'P', 'L', 'e'};
  int res_ser = serial("data/in_1.txt", str, 100, 10); 
  int res_parall = parallel("data/in_1.txt", str, 100, 10, 4);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_10_threads_4_notHave)
{
  char str[] = {'j', 't', 'k', 'l', 'l', 'l', 'l', 'P', 'L', 'e'};
  int res_ser = serial("data/in_1.txt", str, 100, 10); 
  int res_parall = parallel("data/in_1.txt", str, 100, 10, 4);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_3_threads_4)
{
  char str[] = {'j', 't', 'k'};
  int res_ser = serial("data/in_1.txt", str, 100, 3); 
  int res_parall = parallel("data/in_1.txt", str, 100, 3, 4);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_2_threads_4)
{
  char str[] = {'j', 't'};
  int res_ser = serial("data/in_1.txt", str, 100, 2); 
  int res_parall = parallel("data/in_1.txt", str, 100, 2, 4);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_1_threads_4)
{
  char str[] = {'j'};
  int res_ser = serial("data/in_1.txt", str, 100, 1); 
  int res_parall = parallel("data/in_1.txt", str, 100, 1, 4);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_11_threads_2)
{
  char str[] = {'v', 'i', 'b', 'e', 'k', 'i', 't', 'e', 'f', 'o', 'o'};
  int res_ser = serial("data/in_2.txt", str, 200, 11); 
  int res_parall = parallel("data/in_2.txt", str, 200, 11, 2);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_10_threads_2_have)
{
  char str[] = {'b', 'e', 'a', 'r', 'w', 'e', 'e', 'k', 'b', 'e'};
  int res_ser = serial("data/in_2.txt", str, 200, 10); 
  int res_parall = parallel("data/in_2.txt", str, 200, 10, 2);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_10_threads_2_notHave)
{
  char str[] = {'j', 't', 'k', 'l', 'l', 'l', 'l', 'P', 'L', 'e'};
  int res_ser = serial("data/in_2.txt", str, 200, 10); 
  int res_parall = parallel("data/in_2.txt", str, 200, 10, 2);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_4_threads_2)
{
  char str[] = {'b', 'i', 'k', 'e'};
  int res_ser = serial("data/in_2.txt", str, 200, 4); 
  int res_parall = parallel("data/in_2.txt", str, 200, 4, 2);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_1_threads_2)
{
  char str[] = {'b'};
  int res_ser = serial("data/in_2.txt", str, 200, 1); 
  int res_parall = parallel("data/in_2.txt", str, 200, 1, 2);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_11_threads_8)
{
  char str[] = {'v', 'i', 'b', 'e', 'k', 'i', 't', 'e', 'f', 'o', 'o'};
  int res_ser = serial("data/in_4.txt", str, 400, 11); 
  int res_parall = parallel("data/in_4.txt", str, 400, 11, 8);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_10_threads_8_have)
{
  char str[] = {'b', 'e', 'a', 'r', 'w', 'e', 'e', 'k', 'b', 'e'};
  int res_ser = serial("data/in_4.txt", str, 400, 10); 
  int res_parall = parallel("data/in_4.txt", str, 400, 10, 8);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_10_threads_8_notHave)
{
  char str[] = {'j', 't', 'k', 'l', 'l', 'l', 'l', 'P', 'L', 'e'};
  int res_ser = serial("data/in_4.txt", str, 400, 10); 
  int res_parall = parallel("data/in_4.txt", str, 400, 10, 8);
  ASSERT_EQ(res_ser, res_parall);
}

TEST(comare_libs, subst_1_threads_8)
{
  char str[] = {'b'};
  int res_ser = serial("data/in_4.txt", str, 400, 1); 
  int res_parall = parallel("data/in_4.txt", str, 400, 1, 8);
  ASSERT_EQ(res_ser, res_parall);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}