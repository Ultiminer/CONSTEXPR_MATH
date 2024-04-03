#ifndef QM_VEC_2_H_
#define QM_VEC_2_H_
#include "quick_math.h"

namespace QM{
    struct vec2{
        float x; float y; 
        inline void make_unitary()
        {
            const float alpha{1/(QM::sqrt(x*x+y*y))};
            x*=alpha; 
            y*=alpha; 
        }
        inline void make_slope()
        {
            x/=y; 
            y=1; 
        }
        inline void transpose()
        {
            x+=y; 
            y=x-y;
            x-=y; 
        }
        inline void normal()
        {
            transpose();
            x*=-1; 
        }
    };
    struct polarvec2{
        float r; float theta; 
    };
    struct mat22{
        union 
        {
            struct {float a; float b; float c; float d;};
            struct {vec2 u; vec2 w; };
            struct {float e11; float e12; float e21; float e22;};
        };
        inline void invert()
        {
            const float alpha{1/(a*d-b*c)};
            a+=d;d=a-d;a-=d;
            a*=alpha; b*=-alpha;  
            c*=-alpha;d*=alpha;  
        }
    };
    struct line2{
        vec2 a; vec2 b;
    };
    struct ray2{
        vec2 p; float k;
    };


    inline constexpr vec2 ERROR_VEC{71128.2F,-82117.1F};

    constexpr vec2 make_vec(float x, float y)
    {
        return {x,y};
    }
    constexpr float det(const mat22& m)
    {
        return m.a*m.d-m.b*m.c; 
    }
    constexpr polarvec2 make_polar(const vec2& v)
    {
        return {QM::sqrt(v.x*v.x+v.y*v.y), QM::arg(v.y,v.x)}; 
    }
    constexpr vec2 make_cartesian(const polarvec2& v)
    {
        return {v.r*QM::cos(v.theta), v.r*QM::sin(v.theta)}; 
    }
    constexpr vec2 operator+(const vec2& a, const vec2& b)
    {
        return {a.x+b.x,a.y+b.y};
    }
    constexpr vec2 operator-(const vec2& a, const vec2& b)
    {
        return {a.x-b.x,a.y-b.y};
    }
    constexpr float operator*(const vec2& a, const vec2& b)
    {
        return {a.x*b.x+a.y*b.y};
    }
    constexpr float operator^(const vec2& a, const vec2& b)
    {
        return {a.x*b.y-a.y*b.x};
    }
    constexpr vec2 operator*(const vec2& a, float x)
    {
        return {a.x*x,a.y*x};
    }
    constexpr vec2 operator*(float x, const vec2& a)
    {
        return {a.x*x,a.y*x};
    }
    constexpr vec2 operator/(const vec2& a, float x)
    {
        return {a.x/x,a.y/x};
    }

    constexpr polarvec2 operator+(const polarvec2& a, const polarvec2& b)
    {
        return {a.r+b.r,a.theta+b.theta};
    }
    constexpr polarvec2 operator-(const polarvec2& a, const polarvec2& b)
    {
        return {a.r-b.r,a.theta-b.theta};
    }
    constexpr polarvec2 operator*(const polarvec2& a, float x)
    {
        return {a.r*x,a.theta*x};
    }
    constexpr polarvec2 operator*(float x, const polarvec2& a)
    {
        return {a.r*x,a.theta*x};
    }
    constexpr polarvec2 operator/(const polarvec2& a, float x)
    {
        return {a.r/x,a.theta/x};
    }
    
    constexpr mat22 operator+(const mat22& a, const mat22& b)
    {
        return {a.a+b.a,a.b+b.b,a.c+b.c,a.d+b.d};
    }
    constexpr mat22 operator-(const mat22& a, const mat22& b)
    {
        return {a.a-b.a,a.b-b.b,a.c-b.c,a.d-b.d};
    }
    constexpr mat22 operator*(const mat22& a, float x)
    {
        return {a.a*x,a.b*x,a.c*x,a.d*x};
    }
    constexpr mat22 operator/(const mat22& a, float x)
    {
        const float inv{1.0f/x};
        return {a.a*inv,a.b*inv,a.c*inv,a.d*inv};
    }
    constexpr mat22 operator*(float x, const mat22& a)
    {
        return {a.a*x,a.b*x,a.c*x,a.d*x};
    }
    constexpr mat22 operator*(const mat22& a, const mat22& b)
    {
        return {a.a*b.a+a.b*b.c,a.a*b.c+a.c*b.d,a.b*b.a+a.d*b.b,a.b*b.c+a.d*b.d};
    }
    constexpr vec2 operator*(const mat22& m, const vec2& v)
    {
        return {m.a*v.x+m.b*v.y,m.c*v.x+m.d*v.y};
    }  




};




#endif