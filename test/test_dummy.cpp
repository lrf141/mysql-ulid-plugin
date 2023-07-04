#include "gtest/gtest.h"

#include "../include/dummy.h"

TEST(test_dummy, check_return_zero) {
	EXPECT_EQ(one(), 1);
};