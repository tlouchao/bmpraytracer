#include <gtest/gtest.h>
#include "../src/colors.h"

TEST(ColorsTest, FillAndSetColor){
    Colors cs = Colors(3u, 4u);
    color cyan = color(0u, 255u, 255u);
    cs.fillColor(cyan);
    EXPECT_TRUE(cs.getColor(0) == cyan);
    EXPECT_TRUE(cs.getColor(1, 1) == cyan);

    color magenta = color(255u, 0u, 255u);
    cs.fillColor(color(0u, 0u, 0u));
    cs.setColor(magenta, 1);
    cs.setColor(magenta, 1, 2);
    EXPECT_TRUE(cs.getColor(1) == magenta);
    EXPECT_TRUE(cs.getColor(1, 2) == magenta);
}