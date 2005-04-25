
#ifndef NTL_ctools__H
#define NTL_ctools__H

#include <NTL/config.h>
#include <NTL/mach_desc.h>




#define NTL_OVFBND (1L << (NTL_BITS_PER_LONG-4))

/*
 * NTL_OVFBND is the general bound used throughout NTL to keep various
 * integer values comfortably bounded away from an integer overflow
 * condition.  Do not change this value!
 */





#if ((NTL_BITS_PER_SIZE_T-1) < (NTL_BITS_PER_LONG-4))
#define NTL_OVFBND1 (1L << (NTL_BITS_PER_SIZE_T-1))
#else
#define NTL_OVFBND1 NTL_OVFBND
#endif

/*
 * NTL_OVFBND1 is a smaller bound than NTL_OVF when size_t is
 * narrower than long.  This prevents overflow on calls to malloc
 * and realloc.
 */






#define NTL_OVERFLOW(n, a, b) \
   (((b) >= NTL_OVFBND) || (((long) (n)) > 0 && (((a) >= NTL_OVFBND) || \
    (((long) (n)) >= (NTL_OVFBND-((long)(b))+((long)(a))-1)/((long)(a))))))

/*
 * NTL_OVERFLOW(n, a, b) returns 1 if n*a + b >= NTL_OVFBND,
 * and returns 0 otherwise.  The value n is effectively treated as type long,
 * while the values a and b may be *any* integral type.  It is assumed that
 * n >= 0, a > 0, and b >= 0.  Care is taken to ensure that overflow does
 * not occur. If a and b are constants, and n has no side effects,
 * a good optimizing compiler will * translate this into a single test 
 * of the form n >= c, where c is a constant.
 */






#define NTL_OVERFLOW1(n, a, b) \
   (((b) >= NTL_OVFBND1) || (((long) (n)) > 0 && (((a) >= NTL_OVFBND1) || \
    (((long) (n)) >= (NTL_OVFBND1-((long)(b))+((long)(a))-1)/((long)(a))))))

/*
 * NTL_OVERFLOW1 is the same as NTL_OVERFLOW, except that it uses the
 * bound NTL_OVFBND1 instead of NTL_OVFBND.
 */





#define NTL_MALLOC(n, a, b) \
   (NTL_OVERFLOW1(n, a, b) ? ((void *) 0) : \
    ((void *) malloc(((long)(n))*((long)(a)) + ((long)(b)))))

/*
 * NTL_MALLOC(n, a, b) returns 0 if a*n + b >= NTL_OVFBND1, and otherwise
 * returns malloc(n*a + b). 
 * The programmer must ensure that the name "malloc" is visible
 * at the point in the source code where this macro is expanded.
 */






#define NTL_SNS_MALLOC(n, a, b) \
   (NTL_OVERFLOW1(n, a, b) ? ((void *) 0) : \
    ((void *) NTL_SNS malloc(((long)(n))*((long)(a)) + ((long)(b)))))

/*
 * NTL_SNS_MALLOC is the same as NTL_MALLOC, except that the call
 * to malloc is prefixed by NTL_SNS.
 */








#define NTL_REALLOC(p, n, a, b) \
   (NTL_OVERFLOW1(n, a, b) ? ((void *) 0) : \
    ((void *) realloc((p), ((long)(n))*((long)(a)) + ((long)(b)))))

/*
 * NTL_REALLOC(n, a, b) returns 0 if a*n + b >= NTL_OVFBND1, and otherwise
 * returns realloc(p, n*a + b).
 * The programmer must ensure that the name "realloc" is visible
 * at the point in the source code where this macro is expanded.
 */






#define NTL_SNS_REALLOC(p, n, a, b) \
   (NTL_OVERFLOW1(n, a, b) ? ((void *) 0) : \
    ((void *) NTL_SNS realloc((p), ((long)(n))*((long)(a)) + ((long)(b)))))

/*
 * NTL_SNS_REALLOC is the same as NTL_REALLOC, except that the call
 * to realloc is prefixed by NTL_SNS.
 */





#define NTL_MAX_ALLOC_BLOCK (40000)

/*
 * NTL_MAX_ALLOC_BLOCK is the number of bytes that are allocated in
 * a single block in a number of places throughout NTL (for
 * vec_ZZ_p, ZZVec, vec_GF2X, and GF2XVec).
 */


#define NTL_ULONG_TO_LONG(a) \
   ((((unsigned long) a) >> (NTL_BITS_PER_LONG-1)) ? \
    (((long) (((unsigned long) a) - ((unsigned long) NTL_MIN_LONG))) + \
       NTL_MIN_LONG) : \
    ((long) a))

/* 
 * This macro converts from unsigned long to signed long.  It is portable
 * among platforms for which a long has a 2's complement representation
 * of the same width as an unsigned long.  While it avoids assumptions
 * about the behavior of non-standard conversions,  a good optimizing
 * compiler should turn it into the identity function.
 */


#define NTL_UINT_TO_INT(a) \
   ((((unsigned int) a) >> (NTL_BITS_PER_INT-1)) ? \
    (((int) (((unsigned int) a) - ((unsigned int) NTL_MIN_INT))) + \
       NTL_MIN_INT) : \
    ((int) a))

/* 
 * This macro converts from unsigned int to signed int.  It is portable
 * among platforms for which an int has a 2's complement representation
 * of the same width as an unsigned int.  While it avoids assumptions
 * about the behavior of non-standard conversions,  a good optimizing
 * compiler should turn it into the identity function.
 */


#if (defined(__cplusplus) && !defined(NTL_CXX_ONLY))
extern "C" {
#endif

long _ntl_IsFinite(double *p);
/* This forces a double into memory, and tests if it is "normal";
   that means, not NaN, not +/- infinity, not denormalized, etc.
   Forcing into memory is sometimes necessary on machines 
   with "extended" double precision registers (e.g., Intel x86s)
   to force the standard IEEE format. */

void _ntl_ForceToMem(double *p);
/* This is do-nothing routine that has the effect of forcing
   a double into memory (see comment above). */

double _ntl_ldexp(double x, long e);
   
#if (defined(__cplusplus) && !defined(NTL_CXX_ONLY))
}
#endif

#endif

