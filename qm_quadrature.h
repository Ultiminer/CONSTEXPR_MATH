#ifndef QM_QUADRATURE_H_
#define QM_QUADRATURE_H_
#include <functional>

namespace QM{

template <size_t N>
constexpr float quadrature(const std::function<float(float)>& f, float a, float b)
{
    const float alpha{(b-a)/N};
    float sum=0.5f*(f(a)+f(b));
    for(size_t i=1; i< N-1;++i)sum+=f(a+i*alpha);

    return alpha*sum; 
}



}


#endif