#include "colors.h"

Colors::Colors(size_t w, size_t h, unsigned int bpp) : width{w}, height{h} {
    assert(bpp == 24u || bpp == 32u); bitspp = bpp; 
    imgArr = new color[width * height];
    fillColor();
}

Colors::~Colors() noexcept { delete[] imgArr; }

size_t Colors::getWidth() { return width; }

size_t Colors::getHeight() { return height; }

color& Colors::getColor(const size_t h, const size_t w){
    assert (w < width && h < height);
    return imgArr[(h * width) + w]; 
}

color& Colors::getColor(const size_t idx){
    assert (idx < width * height);
    return imgArr[idx]; 
}

void Colors::setColor(const color& c, const size_t h, const size_t w){ 
    assert (w < width && h < height);
    imgArr[(h * width) + w] = c; 
}

void Colors::setColor(const color& c, const size_t idx){ 
    assert (idx < width * height);
    imgArr[idx] = c; 
}

void Colors::fillColor(const color& c){ 
    for (size_t i{}; i < height; ++i){
        for (size_t j{}; j < width; ++j){
            imgArr[(i * width) + j] = c;
        }
    }
}

void Colors::fillColor(){
    fillColor(color(0u, 0u, 0u));
}

unsigned int Colors::getBpp(){ return bitspp; }

color* Colors::getArr() { 
    return imgArr; }