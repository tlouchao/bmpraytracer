#ifndef CASTER_H
#define CASTER_H

#include <memory>
#include <math.h>
#include "colors.h"
#include "prims.h"

class Caster {
    private:
        float fov;
        Vec3f* rayArr;
        size_t width;
        size_t height;
        std::shared_ptr<Colors> colors;
    public:
        Caster(std::shared_ptr<Colors>& colors_in, float fov_in = M_PI / 3); // 60 deg
        ~Caster() noexcept;
    private:
        void generateRays();
        bool isSphereRayIntersect(const Sphere&, const Vec3f& origin, const Vec3f& dir) const;
};

#endif