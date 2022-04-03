#include <gtest/gtest.h>
#include "../src/caster.h"

class CasterFixture : public ::testing::Test {
    protected:
        // img array
        std::shared_ptr<Colors> cs = std::make_shared<Colors>(3u, 4u);
        Caster caster = Caster(cs);
        float mnDistOut = std::numeric_limits<float>::max();

        // sphere to the right of y-axis, with radius 1
        Material m = Material(color(255u, 0u, 0u));
        Sphere sp = Sphere(m, Vec3f(1.f, 0.f, -1.f), 1.f);
};

TEST_F(CasterFixture, GetSetFov){
    EXPECT_FLOAT_EQ(caster.getFov(), M_PI / 3);

    float fovTwo = M_PI_2;
    caster.setFov(fovTwo);
    EXPECT_FLOAT_EQ(caster.getFov(), M_PI / 2);
}

TEST_F(CasterFixture, NoIntersect){
    Vec3f ray = Vec3f(-.01, 0, -1); // left
    EXPECT_FALSE(caster.isSphereRayIntersect(mnDistOut, sp, ray));
    EXPECT_FLOAT_EQ(std::numeric_limits<float>::max(), mnDistOut);
}

TEST_F(CasterFixture, BorderIntersect){
    Vec3f ray = Vec3f(0, 0, -1); // middle
    EXPECT_TRUE(caster.isSphereRayIntersect(mnDistOut, sp, ray));
    EXPECT_FLOAT_EQ(1, mnDistOut);
}

TEST_F(CasterFixture, WithinBorderIntersect){
    Vec3f ray = Vec3f(1, 0, -1); // right
    EXPECT_TRUE(caster.isSphereRayIntersect(mnDistOut, sp, ray));
    EXPECT_FLOAT_EQ((1 - cos(M_PI / 6)) * 2, mnDistOut); // cosine(30 degrees)
}