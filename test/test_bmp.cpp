#include <gtest/gtest.h>
#include "../src/bmp.h"

class BmpTestFixture : public ::testing::Test {
    protected:
        BMP b4 = BMP(3u, 4u);
};

TEST_F(BmpTestFixture, FillAndSetColor){
    color cyan = color(0u, 255u, 255u);
    b4.fillColor(cyan);
    EXPECT_TRUE(b4.getColor(0) == cyan);
    EXPECT_TRUE(b4.getColor(1, 1) == cyan);

    color magenta = color(255u, 0u, 255u);
    b4.fillColor(color(0u, 0u, 0u));
    b4.setColor(magenta, 1);
    b4.setColor(magenta, 1, 2);
    EXPECT_TRUE(b4.getColor(1) == magenta);
    EXPECT_TRUE(b4.getColor(1, 2) == magenta);
}