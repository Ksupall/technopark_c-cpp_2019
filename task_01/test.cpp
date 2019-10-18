#include "gtest/gtest.h"
#include "struct.hpp"

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
	ASSERT_EQ(FUTURE_DATE, check_date(15, 11, 2019);
}

TEST(check_data, wrong_date)
{
	ASSERT_EQ(WRONG_DATE, check_date(31, 2, 2012);
	ASSERT_EQ(WRONG_DATE, check_date(31, 4, 2012);
	ASSERT_EQ(WRONG_DATE, check_date(31, 6, 2012);
	ASSERT_EQ(WRONG_DATE, check_date(31, 9, 2012);
	ASSERT_EQ(WRONG_DATE, check_date(31, 11, 2012);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}