#include "sphere.h"

Sphere::Sphere(Vec3f center, float radius) : center{center}, radius{radius} {}

bool Sphere::ray_intersect(const Vec3f& origin, const Vec3f& dir) const{
    bool res = false;
    Vec3f L = center - origin; // vector from origin to center
    float tca = L * dir; // dot product; projection onto ray; adjacent vector of right tri
    if (tca >= 0){
        float d2 = (L * L) - (tca * tca); // opposite side of right tri
        if (d2 <= radius * radius) {
            float thc = sqrtf((radius * radius) - d2); // adjacent side of right tri
            float t0 = tca - thc, t1 = tca + thc; // enter and exit points
            if (t0 >= 0 || t1 >= 0){ res = true; }
        }
    }
    return res;
}