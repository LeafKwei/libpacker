#include <cstdio>
#include "packer/util/Bitmap.hpp"
using packer::Bitmap;

int main(void){
    printf("---start test---\n");
    Bitmap bitmap(128);
    printf("size = %d\n", bitmap.size());
    
    printf("no set: %d\n", bitmap.test(0));
    bitmap.set(1);
    printf("set: %d\n", bitmap.test(1));

    bitmap.resize(1024);
    printf("new size: %d\n", bitmap.size());
    bitmap.set(1023);
    printf("set: %d\n", bitmap.test(1023));
    bitmap.clear();
    printf("clear: %d\n", bitmap.test(1023));

    return 0;
}