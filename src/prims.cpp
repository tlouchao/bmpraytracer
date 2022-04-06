#include "prims.h"

// material
Material::Material(const Vec4f& albedo, const color& diffuseColor, const float specExponent_in, const float refrIndex_in) : 
    albedo{albedo}, diffuseColor{diffuseColor} { 
    assert (specExponent_in >= 1.f); specExponent = specExponent_in; 
    assert (refrIndex_in >= 1.f); refrIndex = refrIndex_in;
}

Vec4f Material::getAlbedo() const { return albedo; }

color Material::getDiffuseColor() const { return diffuseColor; }

float Material::getSpecExponent() const { return specExponent; }

float Material::getRefrIndex() const { return refrIndex; }

// sphere
Sphere::Sphere(const Material& material_in, const Vec3f& center_in, float radius_in) : 
    material(material_in), center{center_in} { assert (radius_in >= 0); radius = radius_in; }

Material Sphere::getMaterial() const { return material; }

Vec3f Sphere::getCenter() const{ return center; }

float Sphere::getRadius() const{ return radius; }

// checkers
Checkers::Checkers(const Material& matOdd, const Material& matEven, const Vec3f& center) :
    matOdd{matOdd}, matEven{matEven}, center{center} {
    rows = 8; cols = 8; factor = 2;
}

Checkers::Checkers(const Material& matOdd, const Material& matEven, const Vec3f& center,
    size_t rows, size_t cols, size_t factor) : 
    matOdd{matOdd}, matEven{matEven}, center{center}, rows{rows}, cols{cols}, factor{factor} {}

Material Checkers::getMaterial(const Vec3f& hit) const {
    Material res = (int(.5 * hit[0] + 1000) + int(.5 * hit[2])) & 1 ? matOdd : matEven;
    return res;
}

Vec3f Checkers::getCenter() const { return center; }

size_t Checkers::getRows() const { return rows; }

size_t Checkers::getCols() const { return cols; }

size_t Checkers::getWidth() const { return rows * factor; }

size_t Checkers::getHeight() const { return cols * factor; }

// light
Light::Light(const Vec3f& center_in, float intensity_in) : 
    center{center_in} { assert (intensity_in >= 0 && intensity_in <= 1); intensity = intensity_in; }

Vec3f Light::getCenter() const{ return center; }

float Light::getIntensity() const{ return intensity; }