#ifndef QM_COMPLEX_H_
#define QM_COMPLEX_H_
#include <string>
#include "quick_math.h"


namespace QM{
struct Complex
{
    float real; 
    float imag; 
    std::string label()const
    {
        return std::to_string(real)+" + i"+std::to_string(imag);
    }
    constexpr float squaredist()const
    {
        return real*real+imag*imag;
    }
    constexpr Complex conjugate()const
    {
        return {real,-imag}; 
    }
};
constexpr Complex complex(float Real,float Imag)
{
    return {Real,Imag};
}
constexpr Complex conjugate(float Real,float Imag)
{
    return {Real,-Imag};
}
constexpr Complex conjugate(const Complex& comp)
{
    return {comp.real,-comp.imag};
}
inline Complex complex(std::string comp)
{
        std::string realS; 
        std::string imS; 
        for(size_t i=0; i<comp.size();++i)
        {
            if(comp.at(i)=='+'&&comp.at(i+1)=='i')
            {
                realS=comp.substr(0,i);
                realS=comp.substr(i+1,comp.size()-i-1);
            }
        }
        for(size_t i=0; i<realS.size();++i)
        {
            if(realS.at(i)<44&&realS.at(i)>57){realS.erase(realS.begin()+i);i--;}
        }
        for(size_t i=0; i<realS.size();++i)
        {
            if(imS.at(i)<44&&imS.at(i)>57){imS.erase(realS.begin()+i);i--;}
        }
        return {(float)atof(realS.c_str()),(float)atof(imS.c_str())};
}

constexpr Complex operator+(const Complex& a, const Complex& b)
{
return {a.real+b.real, a.imag+b.imag};
}
constexpr Complex operator+(const Complex& a, float x)
{
return {a.real+x, a.imag};
}
constexpr Complex operator+(float x,const Complex& a)
{
return {a.real+x, a.imag};
}
constexpr Complex operator-(float x,const Complex& a)
{
return {x-a.real, a.imag};
}
constexpr Complex operator-(const Complex& a, float x)
{
return {a.real-x, a.imag};
}
constexpr Complex operator-(const Complex& a, const Complex& b)
{
return {a.real-b.real, a.imag-b.imag};
}
constexpr Complex operator*(const Complex& a, float x)
{
return {a.real*x, a.imag*x};
}
constexpr Complex operator*(float x, const Complex& a)
{
return {a.real*x, a.imag*x};
}
constexpr Complex operator/(const Complex& a, float x)
{
return {a.real/x, a.imag/x};
}
constexpr Complex operator/(float x, const Complex& a)
{
return {a.real*(x/(a.squaredist())), a.imag*(x/a.squaredist())};
}
constexpr Complex operator*(const Complex& a,const Complex& b)
{
return {a.real*b.real-a.imag*b.imag, a.real*b.imag+a.imag*b.real};
}
constexpr Complex operator/(const Complex& a,const Complex& b)
{
 return a*b.conjugate()/b.squaredist();
}

inline constexpr Complex i_unit=QM::complex(0,1);

constexpr QM::Complex exp(const QM::Complex& num)
{
    const float expEval{QM::exp(num.real)};
    return {expEval*QM::cos(num.imag),expEval*QM::sin(num.imag)};
}
constexpr float abs(const QM::Complex& num)
{
    return QM::sqrt(num.real*num.real+num.imag*num.imag);
}
constexpr QM::Complex square(const QM::Complex& num)
{
    return num*num;
}
constexpr QM::Complex sin(const QM::Complex& num)
{
    return (-0.5f*i_unit)*(exp(num*QM::i_unit)-exp((-1)*num*QM::i_unit));
}
constexpr QM::Complex cos(const QM::Complex& num)
{
    return (0.5f)*(exp(num*QM::i_unit)+exp((-1)*num*QM::i_unit));
}
constexpr QM::Complex tan(const QM::Complex& num)
{
    return QM::sin(num)/QM::cos(num);
}
constexpr float arg(const QM::Complex& num)
{
    return QM::arg(num.imag,num.real);
}
constexpr QM::Complex sqrt(const QM::Complex& num)
{
    return QM::pow(num.imag*num.imag+num.real*num.real,0.25)*exp(QM::i_unit*QM::arg(num)*0.5f);
}
constexpr float length(const QM::Complex& num)
{
    return QM::abs(num);
}
constexpr QM::Complex ln(const QM::Complex& num)
{
    return QM::ln(QM::length(num))+QM::i_unit*QM::arg(num);
}


}
#endif