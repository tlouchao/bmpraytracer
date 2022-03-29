#include <memory>
#include <gtest/gtest.h>
#include "../src/bmp.h"

using std::unique_ptr;

TEST(ColorTest, ColoRGBInit){
    ColorRGB c1((unsigned char)0xFF, (unsigned char)0x80, (unsigned char)0x00);

    // getters
    EXPECT_TRUE(24u == c1.getDepth());
    EXPECT_TRUE(255u == (unsigned int) c1.getR());
    EXPECT_TRUE((unsigned char) 0xFF == c1.getR());
    EXPECT_TRUE((unsigned char) 0x80 == c1.getG());
    EXPECT_TRUE((unsigned char) 0x00 == c1.getB());

    // setters
    c1.setR((0x80));
    EXPECT_TRUE(128u == (unsigned int) c1.getR());
    EXPECT_TRUE((unsigned char) 0x80 == c1.getR());
}

TEST(ColorTest, ColoRGBAInit){
    ColorRGBA c2((unsigned char)0xFF, (unsigned char)0x80, (unsigned char)0x00, (unsigned char)0xFF);

    // getters
    EXPECT_TRUE(32u == c2.getDepth());
    EXPECT_TRUE(255u == (unsigned int) c2.getR());
    EXPECT_TRUE((unsigned char) 0xFF == c2.getA());

    // setters
    c2.setB((0x80));
    EXPECT_TRUE(128u == (unsigned int) c2.getB());
    EXPECT_TRUE((unsigned char) 0x80 == c2.getB());
    c2.setA((0x40));
    EXPECT_TRUE(64u == (unsigned int) c2.getA());
    EXPECT_TRUE((unsigned char) 0x40 == c2.getA());
}

TEST(ColorTest, GetArray){
    ColorRGB c1((unsigned char)0xFF, (unsigned char)0x80, (unsigned char)0x00);
    ColorRGBA c2((unsigned char)0xFF, (unsigned char)0x80, (unsigned char)0x00, (unsigned char)0xFF);

    unique_ptr<unsigned char[]> c1_arr(c1.getArr());
    EXPECT_TRUE(c1_arr.get()[0] == c1.getR());
    EXPECT_TRUE(c1_arr.get()[1] == c1.getG());
    EXPECT_TRUE(c1_arr.get()[2] == c1.getB());

    unique_ptr<unsigned char[]> c2_arr(c2.getArr());
    EXPECT_TRUE(c2_arr.get()[3] == c2.getA());
}

TEST(ColorTest, EqualsOperator){
    ColorRGB cchar((unsigned char)0xFF, (unsigned char)0x80, (unsigned char)0x00);
    ColorRGB cint((unsigned char)255u, (unsigned char)128u, (unsigned char)0u);
    EXPECT_TRUE(cchar == cint);
}