#ifndef QM_INTERVAL_H_
#define QM_INTERVAL_H_

namespace QM{

struct interval
{
float a; float b;
};
constexpr interval operator|(const interval& A, const interval& B)
{
    if(A.a<B.a)
    {
        if(A.b>B.b)return {A.a,A.b};
        return {A.a,B.b};
    }
    if(A.b>B.b)return {B.a,A.b};
    return {B.a,B.b}; 
}

constexpr bool operator==(const interval& A, const interval& B)
{
   return A.a==B.a&&A.b==B.b;
}
constexpr bool operator>(const interval& A, const interval& B)
{
   return A.a>B.a&&A.b>B.b;
}
constexpr bool operator<(const interval& A, const interval& B)
{
   return A.a<B.a&&A.b<B.b;
}
constexpr interval operator&(const interval& A, const interval& B)
{
    if(A.b>=B.a&&A.b<=B.b)return {B.a,A.b};
    if(B.b>=A.a&&B.b<=A.b)return {A.a,B.b};
    return {0,0};
}
constexpr bool operator==(float x, const interval& A)
{
   return x>A.a&&x<A.b;
}
constexpr bool operator==(const interval& A,float x)
{
   return x>A.a&&x<A.b;
}
constexpr bool operator!=(float x, const interval& A)
{
   return x<A.a||x>A.b;
}
constexpr bool operator!=(const interval& A,float x)
{
   return x<A.a||x>A.b;
}
constexpr bool operator>(float x, const interval& A)
{
   return x>A.b;
}
constexpr bool operator>(const interval& A,float x)
{
   return x<A.a;
}
constexpr bool operator<(const interval& A,float x)
{
   return x>A.b;
}
constexpr bool operator<(float x, const interval& A)
{
   return x<A.a;
}


}


#endif