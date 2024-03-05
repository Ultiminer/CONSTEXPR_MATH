#ifndef QUICK_MATH_H_
#define QUICK_MATH_H_

namespace QM{
    
inline constexpr float EULER_NUM{2.7182818284590452};
inline constexpr float LOG_2_EULER_NUM{1.44269504088896340735};
inline constexpr unsigned int EXP_FLOAT_MASK{0x7f800000};
inline constexpr unsigned int EV_EXPT_EXP_FLOAT_MASK{0x807FFFFF};
inline constexpr float ONE_OVER_LN_2{1.4426950408}; 
inline constexpr float LN_2{0.6931471805599453};
inline constexpr float HALF_LN_2_SQUARED{0.240226506959100};
inline constexpr float POW_TWO_A_1{0.043321698784996581};
inline constexpr float POW_TWO_A_2{9.3838479280898715755293462173177e-4};
inline constexpr float HALF_ROOT_TWO{0.70710678118654};
inline constexpr float QUARTER_PI{0.78539816339744830961566};
inline constexpr size_t PRIMITIVE_FACTORIALS[]={1,1,2,6,24,120,720,5760,51840,518400};
inline constexpr float ONE_OVER_SQRT_2PI{0.398942280401f};

#define GetFloat_Data_Exponent(f) ((*((unsigned int*)&(f)) & EXP_FLOAT_MASK)>>23)
#define AddFloatExponent(f,y) ((((GetFloat_Data_Exponent((f))+(y))<<23)+GetFloat_Data_Mantissa(f)))

//TAKES AS INPUT AN EPSILON BETWEEN -1 and 1 and guesses the corresponding output
constexpr float QUICK_2_TO_EPSILON(float epsilon)
{
  float guess=1+epsilon*(POW_TWO_A_1+POW_TWO_A_2*epsilon); 
  guess*=guess;
  guess*=guess;
  guess*=guess;
  guess*=guess;

  return guess;
}

#define GetFloat_Data_Mantissa(f)((*((unsigned int*)&(f)) & 0x007fffff))
#define GetFloatExponent(f) (((*((unsigned int*)&(f)) & 0x7f800000)>>23)-127)


constexpr float square(float x)
{
    return x*x; 
}
constexpr float sqrt(float x)
{
    //Square root Fixpoint iterations
    #define SQRT_FIX_ITER(guess, eps)(0.5f*((eps)/(guess)+(guess)))
    #define SQRT_2_ITER(guess,eps)(SQRT_FIX_ITER((SQRT_FIX_ITER((SQRT_FIX_ITER((guess),(eps))),(eps))),(eps)))

    constexpr float SQRT_2{1.41421356237};
    constexpr float ONE_OVER_ROOT_TWO{0.707106781186547524};

    //Exponent of float number
    const int e = GetFloatExponent(x);
    
    //Getting float mantissa multiplier
    const unsigned int epsilon=GetFloat_Data_Mantissa(x)+(1<<23)*127; 
    //Half Exponent
    const unsigned int exp_half=(1<<23)*(127+e/2);
   
    if(e%2==0)return (*(float*)&exp_half)*SQRT_2_ITER(0.5f*(1+SQRT_2),*(float*)&epsilon);

    return (*(float*)&exp_half)*((e>=0)?(SQRT_2):(ONE_OVER_ROOT_TWO))*SQRT_2_ITER(0.5f*(1+SQRT_2),*(float*)&epsilon);
}
constexpr float log2(float x)
{
    //Exponent of float number
    const int e = GetFloatExponent(x);
    const unsigned int m_i=GetFloat_Data_Mantissa(x)+(1<<23)*127; 
    const float m=*(float*)&m_i;
    float guess=m-0.97;
    //First Newton iteration
    guess+=ONE_OVER_LN_2*(m*QUICK_2_TO_EPSILON(-guess)-1); 
    //Second Newton iteration
    guess+=ONE_OVER_LN_2*(m*QUICK_2_TO_EPSILON(-guess)-1); 
    //Third Newton iteration
    guess+=ONE_OVER_LN_2*(m*QUICK_2_TO_EPSILON(-guess)-1); 

    return e+guess;
}
constexpr float floor(float x)
{
    if(x>=0)return (int)x; 
    return (int)x-1; 
}
constexpr float pow2(float y)
{
    const unsigned int exp_2=(1<<23)*(127+QM::floor(y));
    return (*(float*)&exp_2)*QUICK_2_TO_EPSILON(y-QM::floor(y)); 
}
constexpr float pow(float x, float y)
{
    return QM::pow2(y*QM::log2(x));
}
constexpr float mod(float x, float m)
{
    if(x<0)return -mod(-x,m);
    return (x-m<0)?x:mod(x-m,m);
}
constexpr float QUICK_SIN_FIRST_QUARTER(float x)
{   
   if(x<0.947)return x-(x*x*x)/6;
   return 1-0.5f*(x-QUARTER_PI*2)*(x-QUARTER_PI*2); 
}
constexpr float sin(float x)
{
    x=mod(x,QUARTER_PI*8);
    if(x<0)x+=QUARTER_PI*8; 
    if(x<=QUARTER_PI*2)
    return QUICK_SIN_FIRST_QUARTER(x);
    if(x<=QUARTER_PI*4)
    return QUICK_SIN_FIRST_QUARTER(4*QUARTER_PI-x);
    if(x<=QUARTER_PI*6)
    return -QUICK_SIN_FIRST_QUARTER(x-QUARTER_PI*4);
    if(x<=QUARTER_PI*8)
    return -QUICK_SIN_FIRST_QUARTER(8*QUARTER_PI-x);

    return 1; 
}
constexpr float cos(float x)
{
    return QM::sin(x+QUARTER_PI*2);
}
constexpr float tan(float x)
{
    return QM::sin(x)/QM::sin(x+QUARTER_PI*2); 
}
constexpr float abs(float x)
{
    if(x>0)return x;
    return -x;
}
constexpr float factorial(size_t n)
{
    if(n<=10)return PRIMITIVE_FACTORIALS[n]; 
    //Stirlings approximation 
    return 2.506628274631000*QM::sqrt(n)*QM::pow(0.36787944117144*n,n);
}
constexpr float binomial_coeff(size_t n, size_t k)
{
 return QM::factorial(n)/(QM::factorial(k)*QM::factorial(n-k));
}
constexpr float ln(float x)
{
    return QM::log2(x)/LOG_2_EULER_NUM; 
}
constexpr float exp(float x)
{
    return QM::pow2(x*LOG_2_EULER_NUM); 
}
constexpr float dist(float x)
{
    return abs(x);
}
constexpr float dist(float x, float y)
{
    return abs(x-y);
}
constexpr float sinh(float x)
{
    return 0.5f*(QM::exp(x)-QM::exp(-x));
}
constexpr float cosh(float x)
{
    return 0.5f*(QM::exp(x)+QM::exp(-x));
}
constexpr float tanh(float x)
{
    const float exp_2_x_{QM::exp(x+x)};
    return 0.5f*((exp_2_x_+1)/(exp_2_x_-1));
}
constexpr float coth(float x)
{
    const float exp_2_x_{QM::exp(x+x)};
    return 0.5f*((exp_2_x_-1)/(exp_2_x_+1));
}
constexpr float atan(float x)
{
    if(x>1)return x/(1+0.28*x*x);
    if(x<-1)return QUARTER_PI*2-x/(x*x+0.28);

    return -QUARTER_PI*2-x/(x*x+0.28);
}
constexpr float asin(float x)
{
    return atan(x/(QM::sqrt(1-x*x))); 
}
constexpr float acos(float x)
{
    return QUARTER_PI*2-atan(x/(QM::sqrt(1-x*x))); 
}
constexpr float max(float x, float y)
{
    if(x>y)return x;
    return y; 
}
constexpr float min(float x, float y)
{
    if(x<y)return x;
    return y; 
}
constexpr size_t max(size_t x, size_t y)
{
    if(x>y)return x;
    return y; 
}
constexpr size_t min(size_t x, size_t y)
{
    if(x<y)return x;
    return y; 
}
constexpr size_t gcd(const size_t m, const size_t n)
{     
    size_t reduction=1; 
    while(true)
    {
        if(m%2+n%2==0)reduction*=2;
        else if(m%3+n%3==0)reduction*=3; 
        else break; 
    }
    const size_t Kmin=QM::min(m,n)/reduction;
    for(size_t g=Kmin; g>1; --g)
    {
        if(m%g+n%g==0)return g*reduction;
    }

    return 1*reduction; 
}
/*Gives the angle of a rise over run situation*/
constexpr float arg(float y, float x)
{
    if(x>0)return QM::atan(y/x);
    if(x<0)
    {
        if(y<0)return atan(y/x)-QUARTER_PI*4;
        return atan(y/x)+QUARTER_PI*4; 
    }
    if(y>0)
    return QUARTER_PI*2;

    return -QUARTER_PI*2;
}
#define SignBit(x) (((*(unsigned int*)&(x)))>>31)

constexpr int sign(float x)
{
    return 1-2*SignBit(x); 
}
constexpr int sign(int x)
{
    return 1-2*SignBit(x); 
}
constexpr int heaviside(float x)
{
    return SignBit(x); 
}
constexpr int step(float x)
{
    return SignBit(x); 
}
constexpr float cron_delta(float x)
{
    if(x==0)return ((float)(1e+300*1e+300));
    return  0;
}
constexpr float normal_distribution(float x, const float mean=0, const float std_dev=1)
{
    return ONE_OVER_SQRT_2PI*(1/std_dev)*QM::exp(-0.5f*square((x-mean)/std_dev));
}
constexpr float gaussian(float x)
{
    return ONE_OVER_SQRT_2PI*QM::exp(-0.5f*x*x);
}
constexpr float gd(float x)
{
    return 2*QM::atan(QM::tanh(0.5f*x));
}
constexpr float sinc(float x)
{
    if(x==0)return 1;
    return QM::sin(x)/x; 
}
constexpr float length(float x, float y)
{
    return QM::sqrt(x*x+y*y);
}
constexpr float length(float x, float y, float z)
{
    return QM::sqrt(x*x+y*y+z*z);
}

/*Triangle math*/
constexpr float triangle_height_on_a(float a, float b, float c)
{
    return 0.5f*(1/a)*QM::sqrt((a+b+c)*(a+b-c)*(a-b+c)*(-a+b+c));
}
constexpr float triangle_area(float a, float b, float c)
{
    return 0.5f*a*QM::triangle_height_on_a(a,b,c);
}







}


#endif