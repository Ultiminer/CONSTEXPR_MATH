#include <iostream>
#include <math.h>
#include "quick_math.h"
#include <array>
#include "nice_cpp_macros.h"    
int main(int argc, char**argv)
{
    float x=-10;
    std::cout<<QM::sign(x)<<std::endl;

    return 0;
}