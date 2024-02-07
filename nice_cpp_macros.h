#ifndef NICE_CPP_MACROS_H_
#define NICE_CPP_MACROS_H_

/*Combining the wisdom acquired from the creation of the quick_math header into a helper library*/

#define NCM_LENGTH(x) ((sizeof(x))/(sizeof(*(x))))
#define NCM_FloatExponent(f) (((*((unsigned int*)&(f)) & 0x7f800000)>>23)-127)
#define NCM_FloatMantissa(f)((*((unsigned int*)&(f)) & 0x007fffff))
#define NCM_POW2(x) ((1<<23)*(127+(x)))
#define NCM_FLOAT_MULTIPLIER(x) (NCM_FloatMantissa((x))+(1<<23)*127)
#define NCM_Swap(x,y)((x)=(x)+(y); (y)=(x)-(y);(x)=(x)-(y);)
#define NCM_SignBit(x) (((*(unsigned int*)&(x)))>>31)
#define NCM_GetBit(x,bitPos) ((((*(unsigned int*)&(x))&(1<<(bitPos))))>>(bitPos))
#define NCM_GetBitL(x,bitPos, length) ((((*(unsigned int*)&(x))<<(31-bitPos)))>>(32-length))


#endif