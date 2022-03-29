#ifndef BMP_H
#define BMP_H

#include <cmath>
#include <cstdint>
#include <fstream>
#include <iosfwd>
#include <iomanip>
#include <stdexcept>
#include "color.h"

using std::ofstream; 
using std::ios; 
using std::hex; 
using std::setw; 
using std::setfill; 
using std::left;
using std::length_error;

class BMP {
    public:
        char magic[2]{'B', 'M'};
        unsigned int headerSize{ 54 };
        unsigned int infoHeaderSize{ 40 };
        unsigned int reserved { 0 };
        unsigned short bitspp; // bits per pixel
        unsigned int width;
        unsigned int height;
        unsigned short cplanes { 1 }; // must be 1
        unsigned int compression { 0 }; // BI_RGB
        unsigned int imgSize { 0 }; // dummy for BI_RGB
        unsigned int hres{ 0 }; // horizontal resolution
        unsigned int vres{ 0 }; // vertical resolution
        unsigned int ncolors{ 0 }; // 0 to default to 2^n
        unsigned int nimpcolors{ 0 }; // important colors
        unsigned int rowSize;
        unsigned int fileSize;
        char* imgArr;
    public:
        BMP(unsigned int w, unsigned int h, unsigned short bpp = 24u);
        ~BMP();
        void writeImg(const char* imgArr_in, const size_t n);
        void writeImg(const Color* cArr_in, const size_t n);
        void setColor(const Color& c, const size_t b_idx);
        void fillColor(const Color& c);
        friend ofstream& operator<< (ofstream& outf, BMP& bmp);
};

#endif