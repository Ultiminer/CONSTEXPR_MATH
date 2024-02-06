#ifndef QUICK_MATH_CALC_H_
#define QUICK_MATH_CALC_H_
#include "quick_math.h"
#include <vector>
#include <functional>
#include <array>
namespace QM{


template<size_t N>
constexpr float grad(const std::function<float(float)>& f, const float x)
{
    constexpr unsigned int expNpos=(1<<23)*(127+N-1); 
    constexpr unsigned int expNneg=(1<<23)*(127-N);
    return (*(float*)&expNpos)*(f(x+(*(float*)&expNneg))-f(x-(*(float*)&expNneg)));
}

template<size_t N, size_t L>
constexpr std::array<float,L> grad(const std::function<float(std::array<float,L>)>& f, const std::array<float,L>& x)
{
    constexpr unsigned int expNpos=(1<<23)*(127+N); 
    constexpr unsigned int expNneg=(1<<23)*(127-N);

    std::array<float,L>out;

    for(size_t i=0; i<L;++i){
    out.data()=x.data();
    out.at(i)+=expNneg; 
    out.at(i)=expNpos*(f(out.at(i))-f(x)); 
    }

    return out; 
}

struct FUN_ARG
{
int var; 
int const_mul; 
int const_add; 
};




}
#endif