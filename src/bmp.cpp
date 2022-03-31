#include "bmp.h"
#include <iostream>

BMP::BMP(unsigned int w, unsigned int h, unsigned short bpp) : width{w}, height{h}, bitspp{bpp} {
    assert(bpp == 24u || bpp == 32u);
    rowSize = 4u * ceil((bitspp * width) / 32u);
    fileSize = headerSize + (rowSize * height);
    imgArr = new color[width * height];
    fillColor(color(0u, 0u, 0u));
}

BMP::~BMP() noexcept {
    delete[] imgArr;
}

color& BMP::getColor(const size_t h, const size_t w){
    assert (w < width && h < height);
    return imgArr[(h * width) + w]; 
}

color& BMP::getColor(const size_t idx){
    assert (idx < width * height);
    return imgArr[idx]; 
}

void BMP::setColor(const color& c, const size_t h, const size_t w){ 
    assert (w < width && h < height);
    imgArr[(h * width) + w] = c; 
}

void BMP::setColor(const color& c, const size_t idx){ 
    assert (idx < width * height);
    imgArr[idx] = c; 
}

void BMP::fillColor(const color& c){ 
    for (size_t i{}; i < height; ++i){
        for (size_t j{}; j < width; ++j){
            imgArr[(i * width) + j] = c;
        }
    }
}

ofstream& operator<< (ofstream& outf, BMP& bmp){
    if (outf.is_open()){
        outf << hex << left << setfill('\0');

        // bitmap file header; left align with padding (little-endian)
        outf << setw(sizeof(char)) << bmp.magic[0] << bmp.magic[1];
        outf << setw(sizeof(uint32_t)) << (char*) &bmp.fileSize;
        outf << setw(sizeof(uint32_t)) << (char*) &bmp.reserved;
        outf << setw(sizeof(uint32_t)) << (char*) &bmp.headerSize;

        // bitmap info header
        outf << setw(sizeof(uint32_t)) << (char*) &bmp.infoHeaderSize;
        outf << setw(sizeof(uint32_t)) << (char*) &bmp.width;
        outf << setw(sizeof(uint32_t)) << (char*) &bmp.height;
        outf << setw(sizeof(uint16_t)) << (char*) &bmp.cplanes;
        outf << setw(sizeof(uint16_t)) << (char*) &bmp.bitspp;
        outf << setw(sizeof(uint32_t)) << (char*) &bmp.compression;
        outf << setw(sizeof(uint32_t)) << (char*) &bmp.imgSize;
        outf << setw(sizeof(uint32_t)) << (char*) &bmp.hres;
        outf << setw(sizeof(uint32_t)) << (char*) &bmp.vres;
        outf << setw(sizeof(uint32_t)) << (char*) &bmp.ncolors;
        outf << setw(sizeof(uint32_t)) << (char*) &bmp.nimpcolors;

        // pixel array
        outf << setw(sizeof(char));
        for(int i{}; i < bmp.height; ++i){
            for(int j{}; j < bmp.width; ++j){
                for (int k{2}; k >= 0; --k){ // backwards ordering (BGR)
                    outf << (char) bmp.getColor(i, j)[k];
                }
            }
            int rowRem = (((int) outf.tellp()) - bmp.headerSize) % 4;
            if (rowRem != 0){ // include padding per row
                outf << setw(4 - rowRem) << (char) 0;
                outf << setw(sizeof(char));
            }
        }
    }
    return outf;
}