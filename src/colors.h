#ifndef COLORS_H
#define COLORS_H

#include "vec.h"

// container for vec3 array of colors
class Colors {
    private:
        size_t width, height;
        unsigned int bitspp;
        color* imgArr;
    public:
        Colors(size_t w, size_t h, unsigned int bpp = 24u);
        ~Colors() noexcept;
        size_t getWidth();
        size_t getHeight();
        color& getColor(const size_t h, const size_t w);
        color& getColor(const size_t idx);
        void setColor(const color& c, const size_t h, const size_t w);
        void setColor(const color& c, const size_t idx);
        void fillColor(const color& c);
        void fillColor();
        unsigned int getBpp();
        color* getArr();
};

#endif