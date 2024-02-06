#ifndef LEAN_ALGEBRA_H_
#define LEAN_ALGEBRA_H_
#include <mmintrin.h>
#include <quick_math.h>
#include "quicksort.h"

//Vector implementation
namespace QM{
template<size_t S>
struct Vec
{
    float data[S];
    constexpr size_t size{S}; 

    #ifdef QM_VEC_DYNAMIC 

    float dynamic_max=0;
    float dynamic_min=0; 

    inline void dynamic_insert(size_t i, float val)noexcept
    {
        if(i>=size)return; 
        data[i]=val; 
        if(val>dynamic_max){dynamic_max=val; return;}
        if(val<dynamic_min)dynamic_min=val; 
    }

    #endif


    constexpr float at(size_t i)const noexcept
    {
        return data[i%size];
    }
    inline float& at(size_t i)noexcept
    {
        return data[i%size];
    }
    constexpr float back(size_t i)const noexcept
    {
        if(size==0)return 0/0; 
        return data[size-1];
    }
    inline float& back(size_t i)noexcept
    {
        if(size==0)return 0/0; 
        return data[size-1];
    }
    constexpr float front(size_t i)const noexcept
    {
        if(size==0)return 0/0; 
        return data[0];
    }
    inline float& front(size_t i)noexcept
    {
        if(size==0)return 0/0;
        return data[0];
    }
    
    constexpr size_t size()const noexcept
    {
        return size;
    }
    constexpr bool isEmpty()const noexcept
    {
        for(size_t i=0; i< size;++i)if(data[i]!=0)return false; 
        return true;
    }
    inline void empty_all()noexcept
    {
        for(float& el:data)el=0; 
    }
    inline void swap(size_t i, size_t j)noexcept
    {
        data[i]+=data[j];
        data[j]=data[i]-data[j];
        data[i]-=data[j];
    }
    inline void flip()noexcept
    {
        for(size_t i=0; i<size/2; ++i)swap(i,size-i);
    }
    inline void sort()noexcept
    {
        QM_SORT(data);
    }
    constexpr float max()const noexcept
    {
        if(size==0)return 0/0; 

        float max{data[0]}; 
        for(size_t i=1; i<size;++i)(data[i]>max)?max=data[i]:;

        return max;
    }
    constexpr float min()const noexcept
    {
        if(size==0)return 0/0; 

        float min{data[0]}; 
        for(size_t i=1; i<size;++i)(data[i]<min)?min=data[i]:;

        return min;
    }

   inline void add_all(float x)noexcept
   {
    for(float& el:data)el+=x; 
   }
   inline void mul_all(float x)noexcept
   {
    for(float& el:data)el*=x; 
   }

    
};




}
#endif