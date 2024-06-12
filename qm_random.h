#ifndef QM_RANDOM_H_
#define QM_RANDOM_H_
#include <cstdint>
#include <functional>
/*
Random library includes the WELL algorithm implemented for public use under:
https://lomont.org/papers/2008/Lomont_PRNG_2008.pdf
last visited on: 12.06.2024
implemented by: 
Chris Lomont, www.lomont.org
*/

namespace QM{

inline struct RNG{

private:

unsigned long m_state[16]={0};
unsigned int m_index = 0;

private:
/*
WELLRNG512 implemented by: 
Chris Lomont, www.lomont.org
*/
inline unsigned long WELLRNG512()
{
unsigned long a=0, b=0, c=0, d=0;
a = m_state[m_index];
c = m_state[(m_index+13)&15];
b = a^c^(a<<16)^(c<<15);
c = m_state[(m_index+9)&15];
c ^= (c>>11);
a = m_state[m_index] = b^c;
d = a^((a<<5)&0xDA442D24UL);
m_index = (m_index + 15)&15;
a = m_state[m_index];
m_state[m_index] = a^b^d^(a<<2)^(b<<18)^(c<<28);
return m_state[m_index];
}

public:
inline RNG& set_seed(size_t seed)
{
const size_t trans_seed=seed+(((seed+3770)*934761)%5555)+(((seed+1467439)*29133361)%567394211);
const size_t setA=trans_seed%100;
const size_t setB=trans_seed%1000;
const size_t setC=trans_seed%10000;
m_state[0]=setA; 
m_state[1]=setB; 
m_state[2]=setC; 
m_state[3]=setA+setB; 
m_state[4]=setB+setC; 
m_state[5]=setA+setC; 
m_state[6]=setA*setB; 
m_state[7]=setA*setC; 
m_state[8]=setB*setC; 
m_state[9]=setA+setB+setC; 
m_state[10]=setA*setB+setB*setC; 
m_state[11]=setA*setA; 
m_state[12]=setB*setB; 
m_state[13]=setC*setC; 
m_state[14]=setA*setB*setC; 
m_state[15]=setA+setB-setC; 



return *this; 
}

RNG(){set_seed(1234);}
RNG(size_t seed){set_seed(seed);}
inline double get_rand()
{
constexpr double MAX_WELL_512_VAL{(unsigned long)(-1)};

return (double)WELLRNG512()/MAX_WELL_512_VAL; 
}
inline double operator()()
{
return get_rand();
}
inline double get_rand_distro(const std::function<double(double)>& distro, const double distro_max)
{
    constexpr size_t UPPER_BOUND_ITER{100000};
    double rand_x{get_rand()};
    const double rand_y{get_rand()*distro_max};
    for(size_t i=0; i<UPPER_BOUND_ITER &&(rand_y>distro(rand_x));++i)rand_x=get_rand();
    

    return rand_x;
}

}rng;


}


#endif