#include <fstream>
#include "src/bmp.h"
#include "src/sphere.h"
#include "src/caster.h"

int main(){
    ofstream outf;
    unsigned int width = 600u, height = 400u;
    BMP bmp(width, height);
    bmp.fillColor(color(0, 0, 128u));

    Vec3f origin = Vec3f(0,0,0);
    Sphere sp1 = Sphere(Vec3f(-4.f, 0.f, -14.f), 5.f);
    Sphere sp2 = Sphere(Vec3f(8.f, 7.f, -25.f), 5.f);
    Sphere sp3 = Sphere(Vec3f(18.f, 2.f, -36.f), 5.f);
    color c1 = color(255u, 0u, 255u);
    color c2 = color(255u, 255u, 0u);
    color c3 = color(0u, 255u, 255u);

    Vec3f* rays = generate_rays(width, height, 1.04f); // 60 degrees
    for (size_t i{}; i < height; ++i){
        for (size_t j{}; j < width; j++){
            if (sp3.ray_intersect(origin, rays[i * width + j])){
                bmp.setColor(c3, i, j);
            }
            if (sp2.ray_intersect(origin, rays[i * width + j])){
                bmp.setColor(c2, i, j);
            }
            if (sp1.ray_intersect(origin, rays[i * width + j])){
                bmp.setColor(c1, i, j);
            }
        }
    }
    delete[] rays;
    outf.open("out.bmp", ios::out | ios::binary);
    if (outf.is_open()){
        outf << bmp;
    }
    outf.close();
    return 0;
}