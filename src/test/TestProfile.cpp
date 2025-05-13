#include <iostream>
#include <cstdio>
#include "packer/impl/DefaultProfileReader.hpp"
#include "packer/impl/DefaultProfileWriter.hpp"

using namespace packer;

int main(void){
    
    Profile profile;
    profile.id = "tree";
    profile.dstRange.height = 100;
    profile.srcRange.width = 200;

    printf("---------------WRITE---------------\n");
    {
    DefaultProfileWriter writer("myprofile.txt");
    writer.write(profile);
    profile.id = "home";
    profile.dstRange.height = 200;
    profile.srcRange.width = 300;
    writer.write(profile);
    }
    
    printf("---------------READ---------------\n");
    {
    Indicator ret;
    DefaultProfileReader reader("myprofile.txt");
    while((ret = reader.read(profile)) != Indicator::RD_EOF){
        if(ret == Indicator::RD_INCOMPLETE){ printf("An incomplete profile was read. It may be a blank line."); continue;}
        fprintf(stdout, "%s:(%d,%d,%d,%d),(%d,%d,%d,%d)\n", profile.id.c_str(), 
        profile.srcRange.x, profile.srcRange.y, profile.srcRange.width, profile.srcRange.height,
        profile.dstRange.x, profile.dstRange.y, profile.dstRange.width, profile.dstRange.height);
    }
    }
}