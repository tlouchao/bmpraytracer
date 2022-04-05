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
    Material wood = Material(Vec3f(.5f, .3f, .1f), color(255, 223, 128), 5.f);
    Material chrome = Material(Vec3f(.75f, .5f, .9f), color(198, 198, 198), 50.f);
    Material paint = Material(Vec3f(.4f, .2f, 0.f), color(223, 0, 0), 1.f);
    color bgcolor = color(0u, 0u, 128u);

    // primitives
    Sphere sp1 = Sphere(wood, Vec3f(-5.f, 0.f, -15.f), 5.f);
    Sphere sp2 = Sphere(chrome, Vec3f(10.f, 6.5f, -26.f), 5.f);
    Sphere sp3 = Sphere(chrome, Vec3f(21.f, 1.5f, -32.f), 2.5f);

    Sphere sp4 = Sphere(paint, Vec3f(0.f, 8.f, -48.f), 16.f);
    Sphere sp5 = Sphere(paint, Vec3f(4.f, -2.5f, -14.f), 2.5f);

    Light lt1 = Light(Vec3f(15, 20, 0), 1.f);
    Light lt2 = Light(Vec3f(30, 40, -10), .5f);

    std::vector<Sphere> spheres{sp1, sp2, sp3, sp4, sp5};
    std::vector<Light> lights{lt1, lt2};

    // render scene
    caster.setBgColor(bgcolor);
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