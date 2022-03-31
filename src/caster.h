#ifndef CASTER_H
#define CASTER_H

#include "vec.h"

Vec3f* generate_rays(size_t width, size_t height, float fov){
    Vec3f* rays = new Vec3f[width * height];
    for (size_t i{}; i < height; ++i){
        for (size_t j{}; j < width; j++){
            float x =  (2*(j + 0.5)/(float)width  - 1)*tan(fov/2.)*width/(float)height;
            float y = (2*(i + 0.5)/(float)height - 1)*tan(fov/2.);
            rays[i * width + j] = Vec3f(x, y, -1).normalize();
        }
    }
    return rays; 
}

#endif