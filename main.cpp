#include <memory>
#include "src/caster.h"
#include "src/prims.h"
#include "src/bmp.h"
#include <fstream>
#include <iostream>

int main(){
    // initialize image array
    size_t width = 600u, height = 400u;
    auto colors = std::make_shared<Colors>(width, height);
    Caster caster(colors);
    BMP bmp(colors);
    
    // primitives
    Sphere sp1 = Sphere(Vec3f(-4.f, 0.f, -14.f), 5.f);
    Sphere sp2 = Sphere(Vec3f(8.f, 7.f, -25.f), 5.f);
    Sphere sp3 = Sphere(Vec3f(18.f, 2.f, -36.f), 5.f);

    // materials
    color c1 = color(255u, 0u, 255u);
    color c2 = color(255u, 255u, 0u);
    color c3 = color(0u, 255u, 255u);
    color bgcolor = color(0u, 0u, 128u);

    // render scene
    colors.get()->fillColor(bgcolor);
    caster.cast(sp3, c3);
    caster.cast(sp2, c2);
    caster.cast(sp1, c1);

    // write image array to file
    ofstream outf;
    outf.open("out.bmp", ios::out | ios::binary);
    if (outf.is_open()){
        outf << bmp;
    }
    outf.close();
    return 0;
}