#ifndef PRIMS_H
#define PRIMS_H

#include "vec.h"

// Primitives in modeling applications such as cubes, spheres, lights
class Material {
    private:
        Vec2f albedo;
        color diffuseColor;
        float specExponent;
    public:
        Material(const Vec2f& albedo = Vec2f(1, 0), 
            const color& diffuseColor = color(0, 0, 0),
            const float specExponent_in = 1);
        Vec2f getAlbedo() const;
        color getDiffuseColor() const;
        float getSpecExponent() const;
};

class Sphere {
    private:
        Material material;
        Vec3f center;
        float radius;
    public:
        Sphere(const Material& material, const Vec3f& center, float radius);
        Material getMaterial() const;
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