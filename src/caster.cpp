#include "caster.h"
#include <iostream>

Caster::Caster(std::shared_ptr<Colors>& colors_in, float fov_in) : fov{fov_in} {
    colors = std::shared_ptr<Colors>(colors_in); bgColor = color(0, 0, 0);
    width = colors.get()->getWidth(); height = colors.get()->getHeight();
    generateRays();
}

Caster::~Caster() noexcept { delete[] rayArr; }

float Caster::getFov() const { return fov; }

void Caster::setFov(float fov_in){ fov = fov_in; }

color Caster::getBgColor() const { return bgColor; } 

void Caster::setBgColor(color bgColor_in ) { bgColor = bgColor_in; }

void Caster::cast(const std::vector<Sphere>& spheres, const std::vector<Checkers>& checkers, 
    const std::vector<Light>& lights, size_t depth) const {
    Vec3f origin = Vec3f(0, 0, 0);
    for (size_t i{}; i < height; ++i){
        for (size_t j{}; j < width; j++){
            color resultColorOut = bgColor;
            cast_ray(resultColorOut, spheres, checkers, lights, rayArr[i * width + j], origin, depth);
            colors.get()->setColor(resultColorOut, i, j);
        }
    }
}

void Caster::cast_ray(color& resultColorOut, const std::vector<Sphere>& spheres, const std::vector<Checkers>& checkers,
    const std::vector<Light>& lights, const Vec3f& dir, const Vec3f& origin, size_t depth) const {
    // min collision dist and collision point
    float mnDistGroup = std::numeric_limits<float>::max();
    float mnDistOut, shadowDistOut; 
    Vec3f hitOut, shadowHitOut;
    Vec3f N;
    Material material;
    bool isIntersectFound = false;
    // loop thru primitives
    for(size_t sp_k{}; sp_k < spheres.size(); ++sp_k){
        if (isSphereRayIntersect(mnDistOut, spheres[sp_k], dir, origin) &&
            mnDistOut < mnDistGroup) {
            mnDistGroup = mnDistOut;
            hitOut = origin + (dir * mnDistOut);
            N = (hitOut - spheres[sp_k].getCenter()).normalize();
            material = spheres[sp_k].getMaterial();
            isIntersectFound = true;
        }
    }
    for (size_t cc_k{}; cc_k < checkers.size(); ++cc_k){
        if (isPlaneRayIntersect(mnDistOut, checkers[cc_k], dir, origin) &&
            mnDistOut < mnDistGroup) {
            mnDistGroup = mnDistOut;
            hitOut = origin + (dir * mnDistOut);
            N = Vec3f(0, 1, 0);
            material = checkers[cc_k].getMaterial(hitOut);
            isIntersectFound = true;
        }
    }
    // calc lights
    float diffuseIntensity{}, specularIntensity{};
    color flectColorOut = bgColor, fractColorOut = bgColor;
    if (isIntersectFound){
        // recursive reflect & refract
        if (depth > 0) {
            Vec3f reflectDir = reflect(dir, N), refractDir = refract(dir, N, material.getRefrIndex());
            Vec3f reflectOrigin = reflectDir * N < 0 ? hitOut - N * 1e-3 : hitOut + N * 1e-3;
            Vec3f refractOrigin = refractDir * N < 0 ? hitOut - N * 1e-3 : hitOut + N * 1e-3;
            reflectDir.normalize(); if (refractDir != Vec3f(0, 0, 0)){ refractDir.normalize(); } 
            cast_ray(flectColorOut, spheres, checkers, lights, reflectDir, reflectOrigin, depth - 1); 
            cast_ray(fractColorOut, spheres, checkers, lights, refractDir, refractOrigin, 0);
        }
        for(size_t lt_l{}; lt_l < lights.size(); ++lt_l){
            Vec3f lightDir = (lights[lt_l].getCenter() - hitOut).normalize();
            float mnDistLight = (lights[lt_l].getCenter() - hitOut).magnitude();
            Vec3f shadowOrigin = lightDir * N < 0 ? hitOut - N * 1e-3 : hitOut + N * 1e-3;
            bool shadowIntersectFound = false;
            // recalc collision point between shadow ray and primitive
            for (size_t sp_k{}; sp_k < spheres.size(); ++sp_k){
                if (isSphereRayIntersect(shadowDistOut, spheres[sp_k], lightDir, shadowOrigin)) {
                    shadowHitOut = origin + (lightDir * shadowDistOut);
                    if ((shadowHitOut - shadowOrigin).magnitude() < mnDistLight) {
                        mnDistLight = (shadowHitOut - shadowOrigin).magnitude();
                        shadowIntersectFound = true;
                    }
                }
            }
            // calc spec and diffuse only if not in shadow
            if (!shadowIntersectFound) { 
                diffuseIntensity += lights[lt_l].getIntensity() * std::max(0.f, lightDir * N);
                specularIntensity += powf(std::max(0.f, reflect(lightDir, N)*dir), 
                    material.getSpecExponent())*lights[lt_l].getIntensity();
            }
        }
    }
    // set color
    if (isIntersectFound){
        resultColorOut = (material.getDiffuseColor() * diffuseIntensity * material.getAlbedo()[0]) +
                         (color(255u, 255u, 255u) * specularIntensity * material.getAlbedo()[1]) +
                         flectColorOut * material.getAlbedo()[2] +
                         fractColorOut * material.getAlbedo()[3];
        for (size_t m{}; m < 3; ++m){ resultColorOut[m] = std::clamp(resultColorOut[m], 0u, 255u); }
    }
}

bool Caster::isSphereRayIntersect(float& mnDistOut, const Sphere& sphere, const Vec3f& dir, const Vec3f& origin) const {
    bool res = false;
    Vec3f L = sphere.getCenter() - origin; // vector from origin to center
    float tca = L * dir; // adjacent side of right tri
    if (tca >= 0){
        float d2 = (L * L) - (tca * tca); // opposite side of right tri
        if (d2 <= sphere.getRadius() * sphere.getRadius()) {
            float thc = sqrtf((sphere.getRadius() * sphere.getRadius()) - d2); // adjacent side of inner right tri
            mnDistOut = tca - thc; // write collision point to out value
            float t0 = tca - thc, t1 = tca + thc; // enter and exit points
            if (t0 >= 0 || t1 >= 0){ res = true; }
        }
    }
    return res;
}

bool Caster::isPlaneRayIntersect(float& mnDistOut, const Checkers& checkers, const Vec3f& dir, const Vec3f& origin) const {
    bool res = false;
    float dy = (origin[1] + checkers.getCenter()[1])/dir[1];
        Vec3f hitTmp = origin + dir * dy;
        /*
        // TODO: Learn checkerboard render algo
        if (dy > 0 && fabs(hitTmp[0]) < 10 && hitTmp[2] < -10 && hitTmp[2] > -30) {
            mnDistOut = dy;
            res = true;
        }
        */
        if (dy > 0 &&
            fabs(hitTmp[0]) <(checkers.getWidth() / 2) && 
            hitTmp[2] < (checkers.getCenter()[2]) + (checkers.getHeight() / 2) && 
            hitTmp[2] > (checkers.getCenter()[2]) - (checkers.getHeight() / 2)) { 
            mnDistOut = dy;
            res = true;
        }
    return res;
}

// generate normalized rays
void Caster::generateRays() {
    rayArr = new Vec3f[width * height];
    for (size_t i{}; i < height; ++i){
        for (size_t j{}; j < width; j++){
            float x =  (2*(j + 0.5)/(float)width  - 1)*tan(fov/2.)*width/(float)height;
            float y = (2*(i + 0.5)/(float)height - 1)*tan(fov/2.);
            rayArr[i * width + j] = Vec3f(x, y, -1).normalize();
        }
    }
}