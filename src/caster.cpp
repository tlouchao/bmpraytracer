#include "caster.h"
#include <iostream>

Caster::Caster(std::shared_ptr<Colors>& colors_in, float fov_in) : fov{fov_in} {
    colors = std::shared_ptr<Colors>(colors_in); 
    width = colors.get()->getWidth(); height = colors.get()->getHeight();
    generateRays();
}

Caster::~Caster() noexcept { delete[] rayArr; }

float Caster::getFov() const { return fov; }

void Caster::setFov(float fov_in){ fov = fov_in; }

void Caster::cast(const std::vector<Sphere>& spheres, const std::vector<Light>& lights, const Vec3f& origin) const {
    for (size_t i{}; i < height; ++i){
        for (size_t j{}; j < width; j++){
            // TODO: place hitpoint color calculation into separate function
            float mnDistSpheres = std::numeric_limits<float>::max(); // min dist combined spheres
            float mnDistOut; 
            Vec3f hitPoint;
            Vec3f surfaceNormal;
            color diffuseColor;
            for(size_t sp_k{}; sp_k < spheres.size(); ++sp_k){
                if (isSphereRayIntersect(mnDistOut, spheres[sp_k], rayArr[i * width + j], origin) &&
                    mnDistOut < mnDistSpheres) {
                    mnDistSpheres = mnDistOut;
                    hitPoint = origin + rayArr[i * width + j] * mnDistOut;
                    surfaceNormal = (hitPoint - spheres[sp_k].getCenter()).normalize();
                    diffuseColor = spheres[sp_k].getDiffuseColor();
                    float diffuseIntensity{};
                    for(size_t lt_l{}; lt_l < lights.size(); ++lt_l){
                        Vec3f lightDir = (lights[lt_l].getCenter() - hitPoint).normalize();
                        diffuseIntensity += lights[lt_l].getIntensity() * std::max(0.f, lightDir * surfaceNormal);
                    }
                    diffuseIntensity = std::min(1.f, diffuseIntensity);
                    color resultColor = diffuseColor * diffuseIntensity;
                    colors.get()->setColor(resultColor, i, j);
                }
            }
        }
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