#ifndef __cplusplus
#error Must use C++ for the type tapfloat.
#endif


#if !defined(__APFLOAT_H)
#include "apfloat.h"
#endif

#if !defined(__TAPFLOAT_H)
#define __TAPFLOAT_H


// Low-level transformed apfloat functions

apstruct *transform (apstruct *s, int m, size_t ssize, size_t n);
apstruct *tapmul (apstruct *a, apstruct *b1, apstruct *b2, apstruct *b3);
apstruct *tapmul (apstruct *a1, apstruct *a2, apstruct *a3, apstruct *b1, apstruct *b2, apstruct *b3);
apstruct *tapadd (apstruct *a, apstruct *b, int m);


// The tapfloat class
// Includes three pointers to apstructs
class tapfloat
{
public:
    // Constructors
    tapfloat ();
    tapfloat (apstruct *d1, apstruct *d2, apstruct *d3);
    tapfloat (const tapfloat &d);

    // Destructor
    ~tapfloat ();

    // Operator functions
    friend tapfloat operator+ (const tapfloat &, const tapfloat &);
    friend apfloat operator* (const apfloat &, const tapfloat &);
    friend apfloat operator* (const tapfloat &, const apfloat &);
    friend apfloat operator* (const tapfloat &, const tapfloat &);
    tapfloat &operator+= (const tapfloat &);
    tapfloat &operator= (const tapfloat &);

    // Type-converted functions, some compilers can't do these automatically
    friend apfloat operator* (const tapfloat &d1, int d2) { return d1 * apfloat (d2); }
    friend apfloat operator* (const tapfloat &d1, unsigned d2) { return d1 * apfloat (d2); }
    friend apfloat operator* (const tapfloat &d1, long d2) { return d1 * apfloat (d2); }
    friend apfloat operator* (const tapfloat &d1, unsigned long d2) { return d1 * apfloat (d2); }
    friend apfloat operator* (const tapfloat &d1, double d2) { return d1 * apfloat (d2); }
    friend apfloat operator* (const tapfloat &d1, char *d2) { return d1 * apfloat (d2); }
    friend apfloat operator* (int d1, const tapfloat &d2) { return apfloat (d1) * d2; }
    friend apfloat operator* (unsigned d1, const tapfloat &d2) { return apfloat (d1) * d2; }
    friend apfloat operator* (long d1, const tapfloat &d2) { return apfloat (d1) * d2; }
    friend apfloat operator* (unsigned long d1, const tapfloat &d2) { return apfloat (d1) * d2; }
    friend apfloat operator* (double d1, const tapfloat &d2) { return apfloat (d1) * d2; }
    friend apfloat operator* (char *d1, const tapfloat &d2) { return apfloat (d1) * d2; }

    // Other functions
    void unique (void);

    // Implementation
    apstruct *ap1, *ap2, *ap3;
};


inline tapfloat::tapfloat ()
{
    ap1 = 0;
    ap2 = 0;
    ap3 = 0;
}


inline tapfloat::tapfloat (apstruct *d1, apstruct *d2, apstruct *d3)
{
    ap1 = d1;
    ap2 = d2;
    ap3 = d3;
}


// Transformed apfloat functions

tapfloat transform (apfloat x, size_t ssize = (size_t) DEFAULT, size_t padsize = (size_t) DEFAULT);
apfloat pow (tapfloat base, unsigned long exp);
apfloat pow (tapfloat base, unsigned exp);
apfloat pow (tapfloat base, long exp);
apfloat pow (tapfloat base, int exp);


#endif  // __TAPFLOAT_H
