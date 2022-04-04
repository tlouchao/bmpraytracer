#include "prims.h"

// sphere
Sphere::Sphere(const Material& material_in, const Vec3f& center_in, float radius_in) : 
    material(material_in), center{center_in} { assert (radius_in >= 0); radius = radius_in; }

Material Sphere::getMaterial() const { return material; }

Vec3f Sphere::getCenter() const{ return center; }

float Sphere::getRadius() const{ return radius; }

// material
Material::Material(const Vec2f& albedo, const color& diffuseColor, const float specExponent_in) : 
    albedo{albedo}, diffuseColor{diffuseColor}{ assert (specExponent_in >= 1.f); specExponent = specExponent_in; }

Vec2f Material::getAlbedo() const { return albedo; }

color Material::getDiffuseColor() const { return diffuseColor; }

float Material::getSpecExponent() const { return specExponent; }

// light
Light::Light(const Vec3f& center_in, float intensity_in) : 
    center{center_in} { assert (intensity_in >= 0 && intensity_in <= 1); intensity = intensity_in; }

Vec3f Light::getCenter() const{ return center; }

float Light::getIntensity() const{ return intensity; }