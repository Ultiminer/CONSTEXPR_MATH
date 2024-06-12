#ifndef QM_SIMD_H_
#define QM_SIMD_H_
#include <immintrin.h>
#include <array>
namespace QM{



template<size_t S>
constexpr float simd_sum(const std::array<float,S>& list)noexcept
{
    __m256 acc=0; 
    for(size_t i=0; i<S/16; ++i)
    {
       acc=_mm256_fmadd_ps(
       _mm256_load_ps((list.data()+i*8)),
       _mm256_load_ps((list.data()+(i+1)*8))
       ,acc
       ) ;
    }
    return (*((float*)(&acc)))
    +(*((float*)(&acc)+1))
    +(*((float*)(&acc)+2))
    +(*((float*)(&acc)+3))
    +(*((float*)(&acc)+4))
    +(*((float*)(&acc)+5))
    +(*((float*)(&acc)+6))
    +(*((float*)(&acc)+7))
    ;
}


template<size_t S>
constexpr float simd_mul(const std::array<float,S>& list)noexcept
{
    __m256 acc=0; 
    for(size_t i=0; i<S/16; ++i)
    {
       acc=_mm256_fmul_ps(
       _mm256_load_ps((list.data()+i*8)),
       _mm256_load_ps((list.data()+(i+1)*8))
       ,acc
       ) ;
    }
    return (*((float*)(&acc)))
    *(*((float*)(&acc)+1))
    *(*((float*)(&acc)+2))
    *(*((float*)(&acc)+3))
    *(*((float*)(&acc)+4))
    *(*((float*)(&acc)+5))
    *(*((float*)(&acc)+6))
    *(*((float*)(&acc)+7))
    ;
}

template<size_t S>
constexpr std::array<float,S> simd_vec_mul(const std::array<float,S>& listA,const std::array<float,S>& listB)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_mul_ps(
       _mm256_load_ps((listA.data()+i*8)),
       _mm256_load_ps((listB.data()+i*8))
       ) ;

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_sin(const std::array<float,S>& list)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_sin_ps( _mm256_load_ps((list.data()+i*8)));

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_cos(const std::array<float,S>& list)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_cos_ps( _mm256_load_ps((list.data()+i*8)));

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_tan(const std::array<float,S>& list)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_tan_ps( _mm256_load_ps((list.data()+i*8)));

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_asin(const std::array<float,S>& list)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_asin_ps( _mm256_load_ps((list.data()+i*8)));

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_acos(const std::array<float,S>& list)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_acos_ps( _mm256_load_ps((list.data()+i*8)));

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_atan(const std::array<float,S>& list)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_atan_ps( _mm256_load_ps((list.data()+i*8)));

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_sinh(const std::array<float,S>& list)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_sinh_ps( _mm256_load_ps((list.data()+i*8)));

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_cosh(const std::array<float,S>& list)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_cosh_ps( _mm256_load_ps((list.data()+i*8)));

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_tanh(const std::array<float,S>& list)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_tanh_ps( _mm256_load_ps((list.data()+i*8)));

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_log(const std::array<float,S>& list)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_log_ps( _mm256_load_ps((list.data()+i*8)));

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_exp(const std::array<float,S>& list)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_exp_ps( _mm256_load_ps((list.data()+i*8)));

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_vec_add(const std::array<float,S>& listA,const std::array<float,S>& listB)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_add_ps(
       _mm256_load_ps((listA.data()+i*8)),
       _mm256_load_ps((listB.data()+i*8))
       ) ;

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_and(const std::array<float,S>& listA,const std::array<float,S>& listB)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_and_ps(
       _mm256_load_ps((listA.data()+i*8)),
       _mm256_load_ps((listB.data()+i*8))
       ) ;

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_or(const std::array<float,S>& listA,const std::array<float,S>& listB)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_or_ps(
       _mm256_load_ps((listA.data()+i*8)),
       _mm256_load_ps((listB.data()+i*8))
       ) ;

    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_xor(const std::array<float,S>& listA,const std::array<float,S>& listB)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_xor_ps(
       _mm256_load_ps((listA.data()+i*8)),
       _mm256_load_ps((listB.data()+i*8))
       ) ;
    
    
    return retVal; 
}
template<size_t S>
constexpr std::array<float,S> simd_cmp(const std::array<float,S>& listA,const std::array<float,S>& listB)noexcept
{
    std::array<float,S> retVal=0; 
    for(size_t i=0; i<S/8; ++i)
       *(__m256*)(retVal.data()+i*8)=_mm256_cmp_ps(
       _mm256_load_ps((listA.data()+i*8)),
       _mm256_load_ps((listB.data()+i*8))
       ) ;
    
    
    return retVal; 
}



}



#endif