#include "bmp.h"

BMP::BMP(unsigned int w, unsigned int h, unsigned short bpp) : width{w}, height{h}, bitspp{bpp} {
    if (bpp == 24u || bpp == 32u){
        rowSize = 4u * ceil((bitspp * width) / 32u);
        fileSize = headerSize + (rowSize * height);
        imgArr = new char[rowSize * height];
    } else {
        throw length_error("length must be equal to unsigned int 24u or 32u");
    }
}

BMP::~BMP() noexcept {
    delete[] imgArr;
}

ofstream& operator<< (ofstream& outf, BMP& bmp){
    if (outf.is_open()){
        outf << hex << left << setfill('\0');

        // write bitmap file header; left align with padding (little-endian)
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

        // write pixel array
        unsigned int blue{0xFF0000}, green{0x00FF00}, red{0x0000FF};
        unsigned int bgr;

        outf << setw(sizeof(char));
        for(int i{}; i < bmp.height; ++i){
            for(int j{}; j < bmp.width; ++j){
                if (j < (bmp.width / 3)){
                    bgr = red;
                } else if (j < ((bmp.width / 3) * 2)){
                    bgr = green;
                } else if (j < bmp.width) {
                    bgr = blue;
                }
                outf << (char) (bgr >> 16 & 0xFF);
                outf << (char) (bgr >> 8 & 0xFF); 
                outf << (char) (bgr & 0xFF);
            }
            int rowRem = (((int) outf.tellp()) - bmp.headerSize) % 4;
            if (rowRem != 0){
                outf << setw(4 - rowRem) << (char) 0;
                outf << setw(sizeof(char));
            }
        }
    }
    return outf;
}