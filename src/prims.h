#ifndef PRIMS_H
#define PRIMS_H

#include "vec.h"

// Primitives in modeling applications such as cubes, spheres, lights
class Material {
    private:
        Vec4f albedo;
        color diffuseColor;
        float specExponent;
        float refrIndex;
    public:
        Material(const Vec4f& albedo = Vec4f(1, 0, 0, 0), const color& diffuseColor = color(0, 0, 0), 
            const float specExponent_in = 1, const float refrIndex = 1);
        Vec4f getAlbedo() const;
        color getDiffuseColor() const;
        float getSpecExponent() const;
        float getRefrIndex() const;
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

class Checkers {
    private:
        Material matOdd, matEven;
        Vec3f center;
        size_t rows, cols, factor;
    public:
        Checkers(const Material& matOdd, const Material& matEven, const Vec3f& center);
        Checkers(const Material& matOdd, const Material& matEven, const Vec3f& center,
            size_t rows, size_t cols, size_t factor);
        Material getMaterial(const Vec3f& hit) const;
        Vec3f getCenter() const;
        size_t getRows() const; size_t getCols() const;
        size_t getWidth() const; size_t getHeight() const;
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