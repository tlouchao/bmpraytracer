#include "bmp.h"

BMP::BMP(std::shared_ptr<Colors>& c){
    colors = std::shared_ptr<Colors>(c);
    unsigned int tmpbpp = colors.get()->getBpp();
    assert(tmpbpp == 24u || tmpbpp == 32u); bitspp = tmpbpp;

    // TODO: check here during cast, to prevent overflow
    width = (unsigned int) colors.get()->getWidth(); 
    height = (unsigned int) colors.get()->getHeight();
    rowSize = 4u * ceil((bitspp * width) / 32u);
    fileSize = headerSize + (rowSize * height);
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
                    outf << (char) bmp.colors.get()->getColor(i, j)[k];
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