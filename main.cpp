#include <fstream>
#include "src/bmp.h"

int main(){
    ofstream outf;
    BMP bmp(600u, 400u);
    outf.open("out.bmp", ios::out | ios::binary);
    if (outf.is_open()){
        outf << bmp;
    }
    outf.close();
    return 0;
}