#ifndef FGE_ANALYSIS_H_
#define FGE_ANALYSIS_H_
#include <functional>
#include "quick_math.h"

namespace FGE{

/*BASIC FUNCTIONS*/
struct FRetVal
{
float val; 
float slope; 
};
constexpr FRetVal Sin(const FRetVal& x)
{
    return {QM::sin(x.val),QM::cos(x.val)*x.slope}; 
}
constexpr FRetVal Cos(const FRetVal& x)
{
    return {QM::cos(x.val),-QM::sin(x.val)*x.slope}; 
}
constexpr FRetVal Tan(const FRetVal& x)
{
    const float eps{ 1/QM::cos(x.val)};
    return {QM::tan(x.val),eps*eps*x.slope}; 
}
constexpr FRetVal CosH(const FRetVal& x)
{
    return {QM::cosh(x.val),QM::sinh(x.val)*x.slope}; 
}
constexpr FRetVal SinH(const FRetVal& x)
{
    return {QM::sinh(x.val),QM::cosh(x.val)*x.slope}; 
}
constexpr FRetVal Exp(const FRetVal& x)
{
    const float eps{QM::exp(x.val)};
    return {eps,eps*x.slope};
}
constexpr FRetVal Ln(const FRetVal& x)
{
    return {QM::ln(x.val),x.slope/x.val};
}
constexpr FRetVal Sqrt(const FRetVal& x)
{
    float eps{QM::sqrt(x.val)};
    return {eps,x.slope*0.5f/eps};
}
constexpr FRetVal OneOver(const FRetVal& x)
{
    float eps{1/x.val};
    return {eps,-x.slope*eps*eps};
}
template<size_t N>
constexpr FRetVal Pow(const FRetVal& x)
{
    float eps{QM::pow(x.val,N)};
    return {eps,x.slope*N*eps/x.val};
}
template<size_t NUMERATOR, size_t DENOMINATOR>
constexpr FRetVal Pow(const FRetVal& x)
{
    constexpr float div{NUMERATOR/DENOMINATOR};
    float eps{QM::pow(x.val,div)};
    return {eps,x.slope*div*eps/x.val};
}
constexpr FRetVal operator+(const FRetVal& a, float k)
{
    return {a.val+k, a.slope}; 
}
constexpr FRetVal operator*(const FRetVal& a, float k)
{
    return {a.val*k, a.slope*k}; 
}
constexpr FRetVal operator*(const FRetVal& a, const FRetVal& b)
{
    return {a.val*b.val, a.val*b.slope+a.slope*b.val}; 
}

constexpr FRetVal operator+(const FRetVal& a, const FRetVal& b)
{
    return {a.val+b.val, a.slope+b.slope}; 
}

//Activation Functions
constexpr FRetVal Identity(const FRetVal& x)
{
    return {x.val,x.slope};
}
constexpr FRetVal BinaryStep(const FRetVal& x)
{
    return {(float)!(x.val<0),0};
}
constexpr FRetVal Sigmoid(const FRetVal& x)
{
    const float s{1/(1+QM::exp(-x.val))};
    return {s,x.slope*s*(1-s)};
}
constexpr FRetVal TanH(const FRetVal& x)
{
    const float eps{QM::tanh(x.val)};
    return {eps,x.slope*(1-eps*eps)};
}
constexpr FRetVal ReLU(const FRetVal& x)
{
    return {x.val*(x.val>0),x.slope*(x.val>0)};
}
constexpr FRetVal Softplus(const FRetVal& x)
{
    return {QM::ln(1+QM::exp(x.val)),x.slope/(1+QM::exp(-x.val))};
}
constexpr FRetVal ELU(const FRetVal& x, float alpha)
{
    if(x.val>0)return{x.val,x.slope};
    const float eps{alpha*QM::exp(x.val)};
    return {eps-alpha,x.slope*eps};
}
constexpr FRetVal LeakyReLU(const FRetVal& x)
{
    const float multiplier{0.01f+0.99f*(x.val>0)};
    return {multiplier*x.val,multiplier*x.slope};
}
constexpr FRetVal PReLU(const FRetVal& x, float alpha)
{
    const float multiplier{1+(alpha-1)*(x.val<0)};
    return {multiplier*x.val,multiplier*x.slope};
}
constexpr FRetVal Gaussian(const FRetVal& x)
{
    const float eps{QM::exp(-x.val*x.val)};
    return {eps,-2*x.slope*eps};
}
constexpr FRetVal SiLU(const FRetVal& x)
{
    const float expM{QM::exp(-x.val)};
    const float expPD{1/(1+expM)};

    return {x.val*expPD,x.slope*(1+expM+x.val*expM)/(expPD*expPD)};
}



constexpr float Sin(const float& x)
{
    return QM::sin(x); 
}
constexpr float Cos(const float& x)
{
    return QM::cos(x); 
}
constexpr float Tan(const float& x)
{
    return QM::tan(x); 
}
constexpr float CosH(const float& x)
{
    return QM::cosh(x); 
}
constexpr float SinH(const float& x)
{
    return QM::sinh(x); 
}
constexpr float Exp(const float& x)
{
    return QM::exp(x);
}
constexpr float Ln(const float& x)
{
    return QM::ln(x);
}
constexpr float Sqrt(const float& x)
{
    return QM::sqrt(x);
}
//Activation Functions
constexpr float Identity(const float& x)
{
    return x;
}
constexpr float BinaryStep(const float& x)
{
    return (float)!(x<0);
}
constexpr float Sigmoid(const float& x)
{
    return 1/(1+QM::exp(-x));
}
constexpr float TanH(const float& x)
{
    return QM::tanh(x);
}
constexpr float ReLU(const float& x)
{
    return x*(x >0);
}
constexpr float Softplus(const float& x)
{
    return QM::ln(1+QM::exp(x));
}
constexpr float ELU(const float& x, float alpha)
{
    if(x>0)return x;
    const float eps{alpha*QM::exp(x)};
    return eps-alpha;
}
constexpr float LeakyReLU(const float& x)
{
    const float multiplier{0.01f+0.99f*(x>0)};
    return multiplier*x;
}
constexpr float PReLU(const float& x, float alpha)
{
    const float multiplier{1+(alpha-1)*(x<0)};
    return multiplier*x;
}
constexpr float Gaussian(const float& x)
{
    const float eps{QM::exp(-x*x)};
    return eps;
}
constexpr float SiLU(const float& x)
{
    const float expM{QM::exp(-x)};
    const float expPD{1/(1+expM)};

    return x*expPD;
}





}


#endif