#include <gtest/gtest.h>
#include <regex>
#include "utils/DateTime.h"

TEST(DateTimeTests, currentTest) {
    const std::regex pattern(
        R"(^[0-9]{4}(0[1-9]|1[0-2])(0[1-9]|[1-2][0-9]|3[0-1])(2[0-3]|[01][0-9])[0-5][0-9][0-5][0-9]$)"
    );
    EXPECT_EQ(std::regex_match(DateTime::current(), pattern), true);
}
