#include <fstream>
#include "src/bmp.h"
#include <iostream>

int main(){
    ofstream outf;
    BMP bmp(3u, 3u);
    bmp.setColor(color(255u, 0, 0), 0);
    bmp.setColor(color(0, 255u, 0), 1);
    bmp.setColor(color(0, 0, 255u), 2);
    bmp.setColor(color(255u, 255u, 0), 3);
    bmp.setColor(color(0, 255u, 255u), 4);
    bmp.setColor(color(255u, 0, 255u), 5);
    for(int i{}; i < 9; ++i){
        std::cout << bmp.getColor(i) << " | ";
    }
    std::cout << '\n';
    outf.open("out.bmp", ios::out | ios::binary);
    if (outf.is_open()){
        outf << bmp;
    }
    outf.close();
    return 0;
}