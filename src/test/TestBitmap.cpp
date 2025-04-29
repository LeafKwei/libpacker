#include <cstdio>
#include "packer/util/Bitmap.hpp"
using packer::Bitmap;

int main(void){
    printf("---start test---\n");
    Bitmap bitmap(16);

    bitmap.setn(0, 16);
    if(bitmap.testAND(0, 16)) printf("All in true\n");
    
    bitmap.unsetn(0, 16);
    if(!bitmap.testAND(0, 16)) printf("All in false\n");

    bitmap.set(6);
    if(bitmap.testOR(0, 16)) printf("One in true");

    return 0;
}