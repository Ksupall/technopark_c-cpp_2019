#include "gtest/gtest.h"
#include "struct.hpp"

TEST(check_data, wrong_year)
{
	ASSERT_EQ(WRONG_YEAR, check_date(3, 11, -100));
	ASSERT_EQ(WRONG_YEAR, check_date(3, 11, 1980));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}