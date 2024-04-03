#ifndef QM_COLLISION_2D_H_
#define QM_COLLISION_2D_H_

#include "quick_math.h"
#include "qm_vec2.h"

namespace QM{

    constexpr bool inRect(const vec2&p, float x, float y, float w, float h)
    {
        return x+w>p.x&&p.x>x&&p.y>y&&y+h>p.y;
    }
    constexpr vec2 intersect(const ray2& a, const ray2& b)
    {
        if(a.k==0&&b.k==0)return ERROR_VEC;
        const vec2 dP{b.p-a.p};
        const float alpha{1/(a.k-b.k)};
        return a.p+make_vec(a.k*alpha*dP.x-a.k*b.k*alpha*dP.y,alpha*dP.x-b.k*alpha*dP.y); 
    }
    constexpr vec2 intersect(const line2& a, const line2& b)
    {
        const ray2 foo{a.a,(a.b.x-a.a.x)/(a.b.y-a.a.y)};const ray2 bar{b.a,(b.b.x-b.a.x)/(b.b.y-b.a.y)};
        const vec2 isect=intersect(foo,bar);
        if(inRect(isect,a.a.x,a.a.y,a.b.x-a.a.x,a.b.y-a.a.y))return isect;

        return ERROR_VEC;
    }

};





#endif