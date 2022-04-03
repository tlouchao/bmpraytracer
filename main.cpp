#include "src/caster.h"
#include "src/prims.h"
#include "src/bmp.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

int main(){
    // initialize image array
    size_t width = 600u, height = 400u;
    auto colors = std::make_shared<Colors>(width, height);
    Caster caster(colors);
    BMP bmp(colors);

    // materials
    Material m1 = Material(color(255u, 0u, 255u));
    Material m2 = Material(color(255u, 255u, 0u));
    Material m3 = Material(color(0u, 255u, 255u));
    color bgcolor = color(0u, 0u, 128u);

    // primitives
    Sphere sp1 = Sphere(m1, Vec3f(-4.f, 0.f, -14.f), 5.f);
    Sphere sp2 = Sphere(m2, Vec3f(8.f, 7.f, -25.f), 5.f);
    Sphere sp3 = Sphere(m3, Vec3f(18.f, 2.f, -36.f), 5.f);
    Light lt1 = Light(Vec3f(12, 8, 0), 1);
    // Light lt2 = Light(Vec3f(-25, -25, -50), .25);

    std::vector<Sphere> spheres{sp1, sp2, sp3};
    std::vector<Light> lights{lt1};

    // render scene
    colors.get()->fillColor(bgcolor);
    caster.cast(spheres, lights);

    // write image array to file
    ofstream outf;
    outf.open("out.bmp", ios::out | ios::binary);
    if (outf.is_open()){
        outf << bmp;
    }
    outf.close();
    return 0;
}