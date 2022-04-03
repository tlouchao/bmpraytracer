#include "prims.h"

Sphere::Sphere(Vec3f center, float radius) : center{center}, radius{radius} {}

Vec3f Sphere::getCenter() const{ return center; }

float Sphere::getRadius() const{ return radius; }