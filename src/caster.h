#ifndef CASTER_H
#define CASTER_H

#include <memory>
#include <math.h>
#include "colors.h"
#include "prims.h"

class Caster {
    private:
        float fov;
        size_t width;
        size_t height;
        Vec3f* rayArr;
        std::shared_ptr<Colors> colors;
    public:
        Caster(std::shared_ptr<Colors>& colors_in, float fov_in = M_PI / 3); // 60 deg
        ~Caster() noexcept;
        float getFov() const;
        void setFov(float fov_in);
        void cast(const Sphere& sphere, const color& color, 
            const Vec3f& origin = Vec3f(0., 0., 0.)) const;
        bool isSphereRayIntersect(const Sphere&, const Vec3f& dir, 
            const Vec3f& origin = Vec3f(0., 0., 0.)) const;
    private:
        void generateRays();
};

#endif