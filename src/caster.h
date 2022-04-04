#ifndef CASTER_H
#define CASTER_H

#include <cmath>
#include <limits>
#include <memory>
#include <vector>
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
        void cast(const std::vector<Sphere>& spheres, const std::vector<Light>& lights, 
            const Vec3f& origin = Vec3f(0., 0., 0.)) const;
        Vec3f reflect(Vec3f& dir, Vec3f& N) const;
        bool isSphereRayIntersect(float& mnDistOut, Vec3f& hitOut, const Sphere& sphere, const Vec3f& dir,
            const Vec3f& origin = Vec3f(0., 0., 0.)) const;
    private:
        void generateRays();
};

#endif