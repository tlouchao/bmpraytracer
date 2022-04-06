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
        color bgColor;
        std::shared_ptr<Colors> colors;
    public:
        Caster(std::shared_ptr<Colors>& colors_in, float fov_in = M_PI / 3); // 60 deg
        ~Caster() noexcept;
        float getFov() const;
        void setFov(float fov_in);
        color getBgColor() const;
        void setBgColor(color fov_in);
        void cast(const std::vector<Sphere>& spheres, const std::vector<Checkers>& checkers, 
            const std::vector<Light>& lights, size_t depth = 4) const;
        void cast_ray(color& resultColorOut, const std::vector<Sphere>& spheres, const std::vector<Checkers>& checkers, 
            const std::vector<Light>& lights, const Vec3f& dir, const Vec3f& origin, size_t depth = 4) const;
        bool isSphereRayIntersect(float& mnDistOut, const Sphere& sphere, const Vec3f& dir,
            const Vec3f& origin) const;
        bool isPlaneRayIntersect(float& mnDistOut, const Checkers& checkers, const Vec3f& dir,
            const Vec3f& origin) const;
    private:
        void generateRays();
};

#endif