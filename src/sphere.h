#ifndef SPHERE_H
#define SPHERE_H

#include "vec.h"

class Sphere {
    private:
        Vec3f center;
        float radius;
    public:
        Sphere(Vec3f center, float radius);
        bool ray_intersect(const Vec3f& origin, const Vec3f& dir) const;
};

#endif