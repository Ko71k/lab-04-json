// Copyright 2022 Ko71k <rassmagin.rrr@gmail.com>

#include <stdexcept>

#include <gtest/gtest.h>

TEST(Example, EmptyTest) {
    EXPECT_THROW(example(), std::runtime_error);
}
