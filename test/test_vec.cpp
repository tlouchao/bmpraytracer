#include <gtest/gtest.h>
#include "../src/vec.h"

TEST(RGBTest, GetSet){
    Vec3u c(0xFFu, 0x80u, 0x00u);

    // getters
    EXPECT_TRUE(255u == c[0]);
    EXPECT_TRUE(0xFFu == c[0]);
    EXPECT_TRUE(0x80u == c[1]);
    EXPECT_TRUE(0x00u == c[2]);

    // setters
    c[0] = 0x80u;
    EXPECT_TRUE(128u == c[0]);
    EXPECT_TRUE(0x80u == c[0]);
}

TEST(Vec3Test, GetSet){
    Vec3f v1(3, 0, 0);
    Vec3f v2(0, 4, 0);

    EXPECT_FLOAT_EQ(3.0f, v1[0]);
    EXPECT_FLOAT_EQ(4.0f, v2[1]);
}

TEST(Vec3Test, AddSub){
    Vec3f v1(1.0, 2.0, 3.0);
    Vec3f v2(4.0, 3.0, 2.0);

    Vec3f va = v1 + v2;
    Vec3f vs = v1 - v2;
    Vec3f vv = -v1;

    EXPECT_FLOAT_EQ(5.0f, va[0]);
    EXPECT_FLOAT_EQ(5.0f, va[1]);
    EXPECT_FLOAT_EQ(-3.0f, vs[0]);
    EXPECT_FLOAT_EQ(-1.0f, vs[1]);
    EXPECT_FLOAT_EQ(-1.0f, vv[0]);
}

TEST(Vec3Test, Magnitude){
    Vec3f v3(3, 4, 0);
    EXPECT_FLOAT_EQ(5.0f, v3.magnitude());

    Vec3f vnorm = v3.normalize();
    std::cout << vnorm << '\n';
    EXPECT_FLOAT_EQ(0.6f, vnorm[0]);
    EXPECT_FLOAT_EQ(0.8f, vnorm[1]);
}

TEST(Vec3Test, DotCross){
    Vec3f v1(3, 0, 0);
    Vec3f v2(0, 4, 0);
    Vec3f v3(3, 4, 0);

    // perpendicular, must be 0
    EXPECT_FLOAT_EQ(0.0f, v1 * v2);
    EXPECT_FLOAT_EQ(16.0f, v2 * v3);

    Vec3f cr = cross(v1, v2);
    EXPECT_FLOAT_EQ(12.0f, cr[2]);
}