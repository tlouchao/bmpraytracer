#include "prims.h"

// sphere
Sphere::Sphere(const Material& material_in, const Vec3f& center_in, float radius_in) : 
    material(material_in), center{center_in} { assert (radius_in >= 0); radius = radius_in; }

color Sphere::getDiffuseColor() const { return material.getDiffuseColor(); }

Vec3f Sphere::getCenter() const{ return center; }

float Sphere::getRadius() const{ return radius; }

// material
Material::Material(const color& diffuseColor) : diffuseColor{diffuseColor} {}

color Material::getDiffuseColor() const { return diffuseColor; }

// light
Light::Light(const Vec3f& center_in, float intensity_in) : 
    center{center_in} { assert (intensity_in >= 0 && intensity_in <= 1); intensity = intensity_in; }

Vec3f Light::getCenter() const{ return center; }

float Light::getIntensity() const{ return intensity; }