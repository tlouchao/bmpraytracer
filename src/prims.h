#ifndef PRIMS_H
#define PRIMS_H

#include "vec.h"

class Sphere {
    private:
        Vec3f center;
        float radius;
    public:
        Sphere(Vec3f center, float radius);
        Vec3f getCenter() const;
        float getRadius() const;
};

#endif