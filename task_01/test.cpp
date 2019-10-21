#include "gtest/gtest.h"
#include "struct.hpp"
#include <cstring>

TEST(check_data, wrong_year)
{
  ASSERT_EQ(WRONG_YEAR, check_date(3, 11, -100));
  ASSERT_EQ(WRONG_YEAR, check_date(3, 11, 1980));
}

TEST(check_data, wrong_month)
{
  ASSERT_EQ(WRONG_MONTH, check_date(3, -11, 2013));
  ASSERT_EQ(WRONG_MONTH, check_date(3, 14, 2013));
}

TEST(check_data, wrong_day)
{
  ASSERT_EQ(WRONG_DAY, check_date(-3, 11, 2013));
  ASSERT_EQ(WRONG_DAY, check_date(33, 11, 2013));
}

TEST(check_data, future_date)
{
  ASSERT_EQ(FUTURE_DATE, check_date(3, 11, 2086));
  ASSERT_EQ(FUTURE_DATE, check_date(3, 12, 2019));
  ASSERT_EQ(FUTURE_DATE, check_date(15, 11, 2019));
}

TEST(check_data, wrong_date)
{
  ASSERT_EQ(WRONG_DATE, check_date(31, 2, 2012));
  ASSERT_EQ(WRONG_DATE, check_date(31, 4, 2012));
  ASSERT_EQ(WRONG_DATE, check_date(31, 6, 2012));
  ASSERT_EQ(WRONG_DATE, check_date(31, 9, 2012));
  ASSERT_EQ(WRONG_DATE, check_date(31, 11, 2012));
}

TEST(sort_by_key, array_two)
{
  product_t p[2] =
  {{"WordPad", "Office application", "12.09.03", {23, 12, 2001}, {0, 0, 0}}, 
  {"Firefox", "Browser", "10.10.5", {11, 10, 2019}, {0, 0, 0}}};
  int key[2] = {0, 1};
  int result[2] = {1, 0};
  sort_by_key(p, 2, key);
  ASSERT_EQ(0, memcmp(result, key, 2 * sizeof(int)));
}

TEST(sort_by_key, array_three)
{
  product_t p[3] =
  {{"WordPad", "Office application", "12.09.03", {23, 12, 2001}, {0, 0, 0}}, 
  {"Firefox", "Browser", "10.10.5", {11, 10, 2019}, {0, 0, 0}},
  {"Dead Island", "Game", "78.89.25", {30, 8, 2019}, {0, 0, 0}}};
  int key[3] = {0, 1, 2};
  int result[3] = {1, 2, 0};
  sort_by_key(p, 3, key);
  ASSERT_EQ(0, memcmp(result, key, 3 * sizeof(int)));
}

TEST(sort_by_key, array_four)
{
  product_t p[4] =
  {{"WordPad", "Office application", "12.09.03", {23, 12, 2001}, {0, 0, 0}}, 
  {"Firefox", "Browser", "10.10.5", {11, 10, 2019}, {0, 0, 0}},
  {"Dead Island", "Game", "78.89.25", {30, 8, 2019}, {0, 0, 0}},
  {"Avast", "Antivirus", "02.05.16", {29, 3, 2015}, {30, 11, 2018}}};
  int key[4] = {0, 1, 2, 3};
  int result[4] = {3, 1, 2, 0};
  sort_by_key(p, 4, key);
  ASSERT_EQ(0, memcmp(result, key, 4 * sizeof(int)));
}

TEST(sort_by_key, array_four_one_class)
{
  product_t p[4] =
  {{"WordPad", "Office application", "12.09.03", {23, 12, 2001}, {0, 0, 0}}, 
  {"Avast", "Browser", "10.10.5", {11, 10, 2019}, {0, 0, 0}},
  {"Dead Island", "Game", "78.89.25", {30, 8, 2019}, {0, 0, 0}},
  {"Firefox", "Browser", "02.05.16", {29, 3, 2015}, {30, 11, 2018}}};
  int key[4] = {0, 1, 2, 3};
  int result[4] = {1, 3, 2, 0};
  sort_by_key(p, 4, key);
  ASSERT_EQ(0, memcmp(result, key, 4 * sizeof(int)));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}