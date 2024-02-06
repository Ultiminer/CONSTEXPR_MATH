#include <iostream>
#include <math.h>
#include "quick_math.h"
#include <array>
#include "nice_cpp_macros.h"    
int main(int argc, char**argv)
{
    float x=8;
    int l=NCM_GetBitL(x,30,8);
    std::cout<<l-127;


    return 0;
}