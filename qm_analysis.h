#ifndef QM_ANALYSIS_H_
#define QM_ANALYSIS_H_
#include "quick_math.h"
#include <array>
#include <functional>
namespace QM{
struct FRetVal{
float val; 
float slope; 
};
using FCONST=float;
using FVAR=float; 
template <size_t N>
struct FDynamicInput
{
    std::array<FRetVal, N> param; 
    size_t currVar; 
};

constexpr FRetVal ad_make_const(float c)noexcept
{
    return {c,0};
}
constexpr FRetVal ad_make_var(FCONST k, FVAR x, FCONST d)noexcept
{
    return {k*x+d,k};
}
constexpr FRetVal operator+(const FRetVal& A, const FRetVal& B)
{
    return {A.val+B.val,A.slope+B.slope}; 
}
constexpr FRetVal operator-(const FRetVal& A, const FRetVal& B)
{
    return {A.val-B.val,A.slope-B.slope}; 
}
constexpr FRetVal operator*(const FRetVal& A, const FRetVal& B)
{
    return {A.val*B.val,A.slope*B.val+A.val*B.slope}; 
}
constexpr FRetVal operator/(const FRetVal& A, const FRetVal& B)
{
    return {A.val/B.val,(A.slope*B.val-A.val*B.slope)/(B.val*B.val)}; 
}
constexpr FRetVal operator+(const FRetVal& A, FCONST c)
{
    return {A.val+c,A.slope}; 
}
constexpr FRetVal operator-(const FRetVal& A, FCONST c)
{
    return {A.val-c,A.slope}; 
}
constexpr FRetVal operator*(const FRetVal& A, FCONST c)
{
    return {A.val*c,A.slope*c}; 
}
constexpr FRetVal operator/(const FRetVal& A, FCONST c)
{
    return {A.val/c,A.slope/c}; 
}

constexpr FRetVal ad_sin(const FRetVal& v)noexcept
{
    return {QM::sin(v.val),QM::cos(v.val)*v.slope};
}
constexpr FRetVal ad_cos(const FRetVal& v)noexcept
{
    return {QM::cos(v.val),-QM::sin(v.val)*v.slope};
}
constexpr FRetVal ad_sinh(const FRetVal& v)noexcept
{
    return {QM::sinh(v.val),QM::cosh(v.val)*v.slope};
}
constexpr FRetVal ad_cosh(const FRetVal& v)noexcept
{
    return {QM::cosh(v.val),QM::sinh(v.val)*v.slope};
}
constexpr FRetVal ad_exp(const FRetVal& v)noexcept
{
    return {QM::exp(v.val),QM::exp(v.val)*v.slope};
} 
constexpr FRetVal ad_ln(const FRetVal& v)noexcept
{
    return {QM::ln(v.val),v.slope/v.val};
} 
constexpr FRetVal ad_pow(const FRetVal& v, FCONST y)noexcept
{
    return {QM::pow(v.val,y),y*QM::pow(v.val,y-1)*v.slope};
} 
constexpr FRetVal ad_sqrt(const FRetVal& v)noexcept
{
    const float res{QM::sqrt(v.val)};
    return {res,0.5f*v.slope/res};
} 
constexpr FRetVal ad_one_over(const FRetVal& v)noexcept
{
    return {1/v.val,-1.0f/(v.val*v.val)*v.slope};
} 
constexpr FRetVal ad_tan(const FRetVal& v)noexcept
{
    const float res{QM::tan(v.val)};
    return {res,(1+res*res)*v.slope};
} 
constexpr FRetVal ad_tanh(const FRetVal& v)noexcept
{
    const float res{QM::tanh(v.val)};
    return {res,(1-res*res)*v.slope};
} 

template<size_t N>
constexpr std::array<FRetVal, N> ad_gradient(const std::function<FRetVal(FDynamicInput<N>)>& fun,const std::array<FRetVal, N>& params)noexcept
{
    std::array<FRetVal, N> retVal;
    for(size_t i=0; i<N; ++i)retVal.at(i)=fun({params,i});
    
    return retVal;
}

template<size_t N>
constexpr float finite_difference(const std::function<float(float)>& fun, float param)
{
    const float eps{0.5f/N};
    return N*fun(param+eps)-N*fun(param-eps); 
}


}

#endif