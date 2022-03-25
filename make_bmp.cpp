#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using std::cout; using std::cin; using std::endl; 
using std::hex; using std::setw; using std::setfill; using std::left;
using std::stringstream; using std::ofstream; using std::ios; using std::ios_base;
using std::string; using std::to_string;
using std::system_error; using std::length_error;

void writeToBmpFile(){
    ofstream bmpf;
    bmpf.open("out.bmp", ios::out | ios::binary);
    if (bmpf.is_open()){

        // BMP properties
        unsigned int headerSize = 54;
        unsigned int infoHeaderSize = 40;
        unsigned int biWidth = 600;
        unsigned int biHeight = 400;
        unsigned int depth = 3;
        unsigned int biBitCount = 24;
        unsigned int rowSize = (depth * biWidth) + ((depth * biWidth) % 4);
        unsigned int fileSize = (rowSize * biHeight) + headerSize;

        // write bitmap file header; left align with padding (little-endian)
        bmpf << hex << left << setfill('\0');
        bmpf << setw(sizeof(char)) << 'B' << 'M';
        bmpf << setw(4) << (char*) &fileSize;
        bmpf << setw(4) << (char) 0;
        bmpf << setw(4) << (char*) &headerSize;

        // bitmap info header
        bmpf << setw(4) << (char) infoHeaderSize;
        bmpf << setw(4) << (char*)(void*)(&biWidth);
        bmpf << setw(4) << (char*)(void*)(&biHeight);
        bmpf << setw(2) << (char) 1;
        bmpf << setw(2) << (char*) &biBitCount;
        bmpf << setw(4) << (char) 0;
        bmpf << setw(4) << (char) 0;
        bmpf << setw(4) << (char) 0;
        bmpf << setw(4) << (char) 0;
        bmpf << setw(4) << (char) 0;
        bmpf << setw(4) << (char) 0;

        unsigned int blue{0xFF0000}, green{0x00FF00}, red{0x0000FF};
        unsigned int white{0xFFFFFF};
        unsigned int bgr;
        
        // write pixel array
        bmpf << setw(sizeof(char));
        for(int i{}; i < biHeight; ++i){
            for(int j{}; j < biWidth; ++j){
                if (j < (biWidth / 3)){
                    bgr = red;
                } else if (j < ((biWidth / 3) * 2)){
                   bgr = green;
                } else if (j < biWidth) {
                    bgr = blue;
                }
                bmpf << (char) (bgr >> 16 & 0xFF);
                bmpf << (char) (bgr >> 8 & 0xFF); 
                bmpf << (char) (bgr & 0xFF);
            }
            int rowRem = (((int) bmpf.tellp()) - headerSize) % 4;
            if (rowRem != 0){
                bmpf << setw(4 - rowRem) << (char) 0;
                bmpf << setw(sizeof(char));
            }
        }
    }
    bmpf.close();
}
int main(){
    writeToBmpFile();
    return 0;
}