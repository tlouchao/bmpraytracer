#include "color.h"

ColorRGB::ColorRGB (const unsigned char R, const unsigned char G, const unsigned char B) : 
    R{R}, G{G}, B{B} {}

ColorRGBA::ColorRGBA (const unsigned char R, const unsigned char G, const unsigned char B, const unsigned char A) : 
    ColorRGB(R, G, B), A{A} {}

unsigned char ColorRGB::getR() { return R; }
unsigned char ColorRGB::getG() { return G; }
unsigned char ColorRGB::getB() { return B; }
unsigned char ColorRGBA::getA() { return A; }
void ColorRGB::setR(const unsigned char R_in) { R = R_in; }
void ColorRGB::setG(const unsigned char G_in) { G = G_in; }
void ColorRGB::setB(const unsigned char B_in) { B = B_in; }
void ColorRGBA::setA(const unsigned char A_in) { A = A_in; }

unsigned short ColorRGB::getDepth() { return 24u; }
unsigned short ColorRGBA::getDepth() { return 32u; }
unsigned char* ColorRGB::getArr() { unsigned char* ptr = new unsigned char[3]{R, G, B}; return ptr; }
unsigned char* ColorRGBA::getArr() { unsigned char* ptr = new unsigned char[4]{R, G, B, A}; return ptr; }

bool operator==(ColorRGB& c1, ColorRGB& c2){
    return ((c1.getR() == c2.getR()) &&
            (c1.getG() == c2.getG()) &&
            (c1.getB() == c2.getB()));
}

bool operator==(ColorRGBA& c1, ColorRGBA& c2){
    return ((c1.getR() == c2.getR()) &&
            (c1.getG() == c2.getG()) &&
            (c1.getB() == c2.getB()) &&
            (c1.getA() == c2.getA()));
}