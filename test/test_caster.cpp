#include <gtest/gtest.h>
#include "../src/caster.h"

class CasterFixture : public ::testing::Test {
    protected:
        // img array
        std::shared_ptr<Colors> cs = std::make_shared<Colors>(3u, 4u);
        Caster caster = Caster(cs);

        // sphere to the right of y-axis, with radius 1
        Sphere sp = Sphere(Vec3f(1, 0, -1), 1);
};

TEST_F(CasterFixture, NoIntersect){
    Vec3f ray = Vec3f(-.01, 0, -1); // left
    EXPECT_FALSE(caster.isSphereRayIntersect(sp, ray));
}

TEST_F(CasterFixture, BorderIntersect){
    Vec3f ray = Vec3f(0, 0, -1); // middle
    EXPECT_TRUE(caster.isSphereRayIntersect(sp, ray));
}

TEST_F(CasterFixture, WithinBorderIntersect){
    Vec3f ray = Vec3f(.5, 0, -1); // right
    EXPECT_TRUE(caster.isSphereRayIntersect(sp, ray));
}