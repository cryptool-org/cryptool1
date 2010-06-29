#if !defined(__BASEINT_H)
#define __BASEINT_H


// Functions in baseint.cpp

#if defined (USEASM)
extern "C"
{
#endif

rawtype baseadd (rawtype *dest, rawtype *src1, rawtype *src2, size_t len, rawtype carry);
rawtype basesub (rawtype *dest, rawtype *src1, rawtype *src2, size_t len, rawtype carry);
rawtype basemuladd (rawtype *dest, rawtype *src1, rawtype *src2, rawtype src3, size_t len, rawtype carry);
rawtype basediv (rawtype *dest, rawtype *src1, rawtype src2, size_t len, rawtype carry);

#if defined (USEASM)
}
#endif

#endif  // __BASEINT_H
