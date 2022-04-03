#include "caster.h"

Caster::Caster(std::shared_ptr<Colors>& colors_in, float fov_in) : fov{fov_in} {
    colors = std::shared_ptr<Colors>(colors_in); 
    width = colors.get()->getWidth(); height = colors.get()->getHeight();
    generateRays();
}

Caster::~Caster() noexcept { delete[] rayArr; }

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

bool Caster::isSphereRayIntersect(const Sphere& sphere, const Vec3f& origin, const Vec3f& dir) const {
    bool res = false;
    Vec3f L = sphere.getCenter() - origin; // vector from origin to center
    float tca = L * dir; // dot product; projection onto ray; adjacent vector of right tri
    if (tca >= 0){
        float d2 = (L * L) - (tca * tca); // opposite side of right tri
        if (d2 <= sphere.getRadius() * sphere.getRadius()) {
            float thc = sqrtf((sphere.getRadius() * sphere.getRadius()) - d2); // adjacent side of right tri
            float t0 = tca - thc, t1 = tca + thc; // enter and exit points
            if (t0 >= 0 || t1 >= 0){ res = true; }
        }
    }
    return res;
}