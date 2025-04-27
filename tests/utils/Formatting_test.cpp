#include <gtest/gtest.h>
#include "utils/Formatting.h"

TEST(FormattingTests, formatDuplicationsTest) {
    const Dedup::Findings findings{
        {"image1.jpg", "image2.jpg"},
        {
            {{1, 0.96789125f}},
            {{1, 0.97545874f}, {1, 0.99125416f}},
        }
    };
    EXPECT_EQ(Formatting::formatDuplications(findings, 0), "image1.jpg\nimage2.jpg (0.97)");
    EXPECT_EQ(Formatting::formatDuplications(findings, 1), "image2.jpg\nimage2.jpg (0.98)\nimage2.jpg (0.99)");
}
