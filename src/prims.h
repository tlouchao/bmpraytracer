#ifndef PRIMS_H
#define PRIMS_H

#include "vec.h"

// Primitives in modeling applications such as cubes, spheres, lights
class Material {
    private:
        color diffuseColor;
    public:
        Material(const color& diffuseColor = color(0, 0, 0));
        color getDiffuseColor() const;
};

class Sphere {
    private:
        Material material;
        Vec3f center;
        float radius;
    public:
        Sphere(const Material& material, const Vec3f& center, float radius);
        color getDiffuseColor() const;
        Vec3f getCenter() const;
        float getRadius() const;
};

class Light {
    private:
        Vec3f center;
        float intensity;
    public:
        Light(const Vec3f& center, float intensity);
        Vec3f getCenter() const;
        float getIntensity() const;
};

#endif