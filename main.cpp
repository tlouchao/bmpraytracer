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
    Material wood = Material(Vec2f(.5f, .3f), color(255u, 223u, 128u), 5.f);
    Material chrome = Material(Vec2f(1.f, .5f), color(198u, 198u, 198u), 50.f);
    Material paint = Material(Vec2f(.4f, .2f), color(223u, 0u, 0u), 1.f);
    color bgcolor = color(0u, 0u, 128u);

    // primitives
    Sphere sp1 = Sphere(wood, Vec3f(-4.f, 0.f, -14.f), 5.f);
    Sphere sp2 = Sphere(chrome, Vec3f(10.f, 7.f, -25.f), 5.f);
    Sphere sp3 = Sphere(paint, Vec3f(20.f, 2.f, -36.f), 5.f);
    Sphere sp4 = Sphere(paint, Vec3f(4.f, -2.5f, -14.f), 2.5f);
    Light lt1 = Light(Vec3f(15, 20, 0), 1.f);
    Light lt2 = Light(Vec3f(30, 40, -8), .4f);

    std::vector<Sphere> spheres{sp1, sp2, sp3, sp4};
    std::vector<Light> lights{lt1, lt2};

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