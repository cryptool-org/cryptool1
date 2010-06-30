#ifndef __cplusplus
#error Must use C++ for the type apcomplex.
#endif


#if !defined(__APCPLX_H)
#define __APCPLX_H

#if !defined(__APFLOAT_H)
#include "apfloat.h"
#endif


class apcomplex
{
public:
    // Constructors
    apcomplex (const apfloat &newre, const apfloat &newim = 0) { re = newre; im = newim; }
    apcomplex ();

    // Create a complex object given polar coordinates
    friend apcomplex polar (apfloat mag, apfloat angle = 0);

    // Complex manipulations
    friend apfloat real (const apcomplex &);            // Real part
    friend apfloat imag (const apcomplex &);            // Imaginary part
    friend apcomplex conj (const apcomplex &);          // Complex conjugate
    friend apfloat norm (const apcomplex &);            // Square of the magnitude
    friend apfloat arg (const apcomplex &);             // Angle in the plane

    // Operator functions
    friend apcomplex operator+ (const apcomplex &, const apcomplex &);
    friend apcomplex operator+ (const apfloat &, const apcomplex &);
    friend apcomplex operator+ (const apcomplex &, const apfloat &);
    friend apcomplex operator- (const apcomplex &, const apcomplex &);
    friend apcomplex operator- (const apfloat &, const apcomplex &);
    friend apcomplex operator- (const apcomplex &, const apfloat &);
    friend apcomplex operator* (const apcomplex &, const apcomplex &);
    friend apcomplex operator* (const apfloat &, const apcomplex &);
    friend apcomplex operator* (const apcomplex &, const apfloat &);
    friend apcomplex operator/ (const apcomplex &, const apcomplex &);
    friend apcomplex operator/ (const apfloat &, const apcomplex &);
    friend apcomplex operator/ (const apcomplex &, const apfloat &);
    friend bool operator== (const apcomplex &, const apcomplex &);
    friend bool operator== (const apfloat &, const apcomplex &);
    friend bool operator== (const apcomplex &, const apfloat &);
    friend bool operator!= (const apcomplex &, const apcomplex &);
    friend bool operator!= (const apfloat &, const apcomplex &);
    friend bool operator!= (const apcomplex &, const apfloat &);
    friend std::ostream &operator<< (std::ostream &, const apcomplex &);
    friend std::istream &operator>> (std::istream &, apcomplex &);
    apcomplex &operator+= (const apcomplex &);
    apcomplex &operator+= (const apfloat &);
    apcomplex &operator-= (const apcomplex &);
    apcomplex &operator-= (const apfloat &);
    apcomplex &operator*= (const apcomplex &);
    apcomplex &operator*= (const apfloat &);
    apcomplex &operator/= (const apcomplex &);
    apcomplex &operator/= (const apfloat &);
    apcomplex operator+ () const;
    apcomplex operator- () const;

    // Type-converted functions, some compilers can't do these automatically
    apcomplex (const apfloat &newre, int newim) { re = newre; im = apfloat (newim); }
    apcomplex (const apfloat &newre, unsigned newim) { re = newre; im = apfloat (newim); }
    apcomplex (const apfloat &newre, long newim) { re = newre; im = apfloat (newim); }
    apcomplex (const apfloat &newre, unsigned long newim) { re = newre; im = apfloat (newim); }
    apcomplex (const apfloat &newre, double newim) { re = newre; im = apfloat (newim); }
    apcomplex (const apfloat &newre, char *newim) { re = newre; im = apfloat (newim); }
    apcomplex (int newre, const apfloat &newim = 0) { re = apfloat (newre); im = newim; }
    apcomplex (int newre, int newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (int newre, unsigned newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (int newre, long newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (int newre, unsigned long newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (int newre, double newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (int newre, char *newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (unsigned newre, const apfloat &newim = 0) { re = apfloat (newre); im = newim; }
    apcomplex (unsigned newre, int newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (unsigned newre, unsigned newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (unsigned newre, long newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (unsigned newre, unsigned long newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (unsigned newre, double newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (unsigned newre, char *newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (long newre, const apfloat &newim = 0) { re = apfloat (newre); im = newim; }
    apcomplex (long newre, int newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (long newre, unsigned newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (long newre, long newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (long newre, unsigned long newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (long newre, double newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (long newre, char *newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (unsigned long newre, const apfloat &newim = 0) { re = apfloat (newre); im = newim; }
    apcomplex (unsigned long newre, int newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (unsigned long newre, unsigned newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (unsigned long newre, long newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (unsigned long newre, unsigned long newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (unsigned long newre, double newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (unsigned long newre, char *newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (double newre, const apfloat &newim = 0) { re = apfloat (newre); im = newim; }
    apcomplex (double newre, int newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (double newre, unsigned newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (double newre, long newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (double newre, unsigned long newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (double newre, double newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (double newre, char *newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (char *newre, const apfloat &newim = 0) { re = apfloat (newre); im = newim; }
    apcomplex (char *newre, int newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (char *newre, unsigned newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (char *newre, long newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (char *newre, unsigned long newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (char *newre, double newim) { re = apfloat (newre); im = apfloat (newim); }
    apcomplex (char *newre, char *newim) { re = apfloat (newre); im = apfloat (newim); }

    friend apcomplex operator+ (int d1, const apcomplex &z2) { return apfloat (d1) + z2; }
    friend apcomplex operator+ (unsigned d1, const apcomplex &z2) { return apfloat (d1) + z2; }
    friend apcomplex operator+ (long d1, const apcomplex &z2) { return apfloat (d1) + z2; }
    friend apcomplex operator+ (unsigned long d1, const apcomplex &z2) { return apfloat (d1) + z2; }
    friend apcomplex operator+ (double d1, const apcomplex &z2) { return apfloat (d1) + z2; }
    friend apcomplex operator+ (char *d1, const apcomplex &z2) { return apfloat (d1) + z2; }
    friend apcomplex operator+ (const apcomplex &z1, int d2) { return z1 + apfloat (d2); }
    friend apcomplex operator+ (const apcomplex &z1, unsigned d2) { return z1 + apfloat (d2); }
    friend apcomplex operator+ (const apcomplex &z1, long d2) { return z1 + apfloat (d2); }
    friend apcomplex operator+ (const apcomplex &z1, unsigned long d2) { return z1 + apfloat (d2); }
    friend apcomplex operator+ (const apcomplex &z1, double d2) { return z1 + apfloat (d2); }
    friend apcomplex operator+ (const apcomplex &z1, char *d2) { return z1 + apfloat (d2); }
    friend apcomplex operator- (int d1, const apcomplex &z2) { return apfloat (d1) - z2; }
    friend apcomplex operator- (unsigned d1, const apcomplex &z2) { return apfloat (d1) - z2; }
    friend apcomplex operator- (long d1, const apcomplex &z2) { return apfloat (d1) - z2; }
    friend apcomplex operator- (unsigned long d1, const apcomplex &z2) { return apfloat (d1) - z2; }
    friend apcomplex operator- (double d1, const apcomplex &z2) { return apfloat (d1) - z2; }
    friend apcomplex operator- (char *d1, const apcomplex &z2) { return apfloat (d1) - z2; }
    friend apcomplex operator- (const apcomplex &z1, int d2) { return z1 - apfloat (d2); }
    friend apcomplex operator- (const apcomplex &z1, unsigned d2) { return z1 - apfloat (d2); }
    friend apcomplex operator- (const apcomplex &z1, long d2) { return z1 - apfloat (d2); }
    friend apcomplex operator- (const apcomplex &z1, unsigned long d2) { return z1 - apfloat (d2); }
    friend apcomplex operator- (const apcomplex &z1, double d2) { return z1 - apfloat (d2); }
    friend apcomplex operator- (const apcomplex &z1, char *d2) { return z1 - apfloat (d2); }
    friend apcomplex operator* (int d1, const apcomplex &z2) { return apfloat (d1) * z2; }
    friend apcomplex operator* (unsigned d1, const apcomplex &z2) { return apfloat (d1) * z2; }
    friend apcomplex operator* (long d1, const apcomplex &z2) { return apfloat (d1) * z2; }
    friend apcomplex operator* (unsigned long d1, const apcomplex &z2) { return apfloat (d1) * z2; }
    friend apcomplex operator* (double d1, const apcomplex &z2) { return apfloat (d1) * z2; }
    friend apcomplex operator* (char *d1, const apcomplex &z2) { return apfloat (d1) * z2; }
    friend apcomplex operator* (const apcomplex &z1, int d2) { return z1 * apfloat (d2); }
    friend apcomplex operator* (const apcomplex &z1, unsigned d2) { return z1 * apfloat (d2); }
    friend apcomplex operator* (const apcomplex &z1, long d2) { return z1 * apfloat (d2); }
    friend apcomplex operator* (const apcomplex &z1, unsigned long d2) { return z1 * apfloat (d2); }
    friend apcomplex operator* (const apcomplex &z1, double d2) { return z1 * apfloat (d2); }
    friend apcomplex operator* (const apcomplex &z1, char *d2) { return z1 * apfloat (d2); }
    friend apcomplex operator/ (int d1, const apcomplex &z2) { return apfloat (d1) / z2; }
    friend apcomplex operator/ (unsigned d1, const apcomplex &z2) { return apfloat (d1) / z2; }
    friend apcomplex operator/ (long d1, const apcomplex &z2) { return apfloat (d1) / z2; }
    friend apcomplex operator/ (unsigned long d1, const apcomplex &z2) { return apfloat (d1) / z2; }
    friend apcomplex operator/ (double d1, const apcomplex &z2) { return apfloat (d1) / z2; }
    friend apcomplex operator/ (char *d1, const apcomplex &z2) { return apfloat (d1) / z2; }
    friend apcomplex operator/ (const apcomplex &z1, int d2) { return z1 / apfloat (d2); }
    friend apcomplex operator/ (const apcomplex &z1, unsigned d2) { return z1 / apfloat (d2); }
    friend apcomplex operator/ (const apcomplex &z1, long d2) { return z1 / apfloat (d2); }
    friend apcomplex operator/ (const apcomplex &z1, unsigned long d2) { return z1 / apfloat (d2); }
    friend apcomplex operator/ (const apcomplex &z1, double d2) { return z1 / apfloat (d2); }
    friend apcomplex operator/ (const apcomplex &z1, char *d2) { return z1 / apfloat (d2); }

    friend bool operator== (int d1, const apcomplex &z2) { return apfloat (d1) == z2; }
    friend bool operator== (unsigned d1, const apcomplex &z2) { return apfloat (d1) == z2; }
    friend bool operator== (long d1, const apcomplex &z2) { return apfloat (d1) == z2; }
    friend bool operator== (unsigned long d1, const apcomplex &z2) { return apfloat (d1) == z2; }
    friend bool operator== (double d1, const apcomplex &z2) { return apfloat (d1) == z2; }
    friend bool operator== (char *d1, const apcomplex &z2) { return apfloat (d1) == z2; }
    friend bool operator== (const apcomplex &z1, int d2) { return z1 == apfloat (d2); }
    friend bool operator== (const apcomplex &z1, unsigned d2) { return z1 == apfloat (d2); }
    friend bool operator== (const apcomplex &z1, long d2) { return z1 == apfloat (d2); }
    friend bool operator== (const apcomplex &z1, unsigned long d2) { return z1 == apfloat (d2); }
    friend bool operator== (const apcomplex &z1, double d2) { return z1 == apfloat (d2); }
    friend bool operator== (const apcomplex &z1, char *d2) { return z1 == apfloat (d2); }
    friend bool operator!= (int d1, const apcomplex &z2) { return apfloat (d1) != z2; }
    friend bool operator!= (unsigned d1, const apcomplex &z2) { return apfloat (d1) != z2; }
    friend bool operator!= (long d1, const apcomplex &z2) { return apfloat (d1) != z2; }
    friend bool operator!= (unsigned long d1, const apcomplex &z2) { return apfloat (d1) != z2; }
    friend bool operator!= (double d1, const apcomplex &z2) { return apfloat (d1) != z2; }
    friend bool operator!= (char *d1, const apcomplex &z2) { return apfloat (d1) != z2; }
    friend bool operator!= (const apcomplex &z1, int d2) { return z1 != apfloat (d2); }
    friend bool operator!= (const apcomplex &z1, unsigned d2) { return z1 != apfloat (d2); }
    friend bool operator!= (const apcomplex &z1, long d2) { return z1 != apfloat (d2); }
    friend bool operator!= (const apcomplex &z1, unsigned long d2) { return z1 != apfloat (d2); }
    friend bool operator!= (const apcomplex &z1, double d2) { return z1 != apfloat (d2); }
    friend bool operator!= (const apcomplex &z1, char *d2) { return z1 != apfloat (d2); }

    apcomplex &operator+= (int d) { *this = *this + apfloat (d); return *this; }
    apcomplex &operator+= (unsigned d) { *this = *this + apfloat (d); return *this; }
    apcomplex &operator+= (long d) { *this = *this + apfloat (d); return *this; }
    apcomplex &operator+= (unsigned long d) { *this = *this + apfloat (d); return *this; }
    apcomplex &operator+= (double d) { *this = *this + apfloat (d); return *this; }
    apcomplex &operator+= (char *d) { *this = *this + apfloat (d); return *this; }
    apcomplex &operator-= (int d) { *this = *this - apfloat (d); return *this; }
    apcomplex &operator-= (unsigned d) { *this = *this - apfloat (d); return *this; }
    apcomplex &operator-= (long d) { *this = *this - apfloat (d); return *this; }
    apcomplex &operator-= (unsigned long d) { *this = *this - apfloat (d); return *this; }
    apcomplex &operator-= (double d) { *this = *this - apfloat (d); return *this; }
    apcomplex &operator-= (char *d) { *this = *this - apfloat (d); return *this; }
    apcomplex &operator*= (int d) { *this = *this * apfloat (d); return *this; }
    apcomplex &operator*= (unsigned d) { *this = *this * apfloat (d); return *this; }
    apcomplex &operator*= (long d) { *this = *this * apfloat (d); return *this; }
    apcomplex &operator*= (unsigned long d) { *this = *this * apfloat (d); return *this; }
    apcomplex &operator*= (double d) { *this = *this * apfloat (d); return *this; }
    apcomplex &operator*= (char *d) { *this = *this * apfloat (d); return *this; }
    apcomplex &operator/= (int d) { *this = *this / apfloat (d); return *this; }
    apcomplex &operator/= (unsigned d) { *this = *this / apfloat (d); return *this; }
    apcomplex &operator/= (long d) { *this = *this / apfloat (d); return *this; }
    apcomplex &operator/= (unsigned long d) { *this = *this / apfloat (d); return *this; }
    apcomplex &operator/= (double d) { *this = *this / apfloat (d); return *this; }
    apcomplex &operator/= (char *d) { *this = *this / apfloat (d); return *this; }
    apcomplex &operator= (const apfloat &d) { re = d; im = 0; return *this; }
    apcomplex &operator= (int d) { re = apfloat (d); im = 0; return *this; }
    apcomplex &operator= (unsigned d) { re = apfloat (d); im = 0; return *this; }
    apcomplex &operator= (long d) { re = apfloat (d); im = 0; return *this; }
    apcomplex &operator= (unsigned long d) { re = apfloat (d); im = 0; return *this; }
    apcomplex &operator= (double d) { re = apfloat (d); im = 0; return *this; }
    apcomplex &operator= (char *d) { re = apfloat (d); im = 0; return *this; }

    // Other functions
    size_t prec (void) const;
    void prec (size_t newprec);
    void swapfrom (char *filename1, char *filename2) { re.swapfrom (filename1); im.swapfrom (filename2); }
    void swapto (char *filename1, char *filename2) { re.swapto (filename1); im.swapto (filename2); }

    // Implementation
    apfloat re, im;                             // Won't be private
};


// Inline apcomplex functions

inline apcomplex::apcomplex ()
{
}

inline apcomplex apcomplex::operator+ () const
{
    return *this;
}

inline apcomplex apcomplex::operator- () const
{
    return apcomplex (-re, -im);
}


// Definitions of compound-assignment operator member functions

inline apcomplex &apcomplex::operator+= (const apcomplex &z)
{
    re = re + z.re;
    im = im + z.im;

    return *this;
}

inline apcomplex &apcomplex::operator+= (const apfloat &d)
{
    re = re + d;

    return *this;
}

inline apcomplex &apcomplex::operator-= (const apcomplex &z)
{
    re = re - z.re;
    im = im - z.im;

    return *this;
}

inline apcomplex &apcomplex::operator-= (const apfloat &d)
{
    re = re - d;

    return *this;
}

inline apcomplex &apcomplex::operator*= (const apcomplex &z)
{
    *this = *this * z;

    return *this;
}

inline apcomplex &apcomplex::operator*= (const apfloat &d)
{
    re = re * d;
    im = im * d;

    return *this;
}

inline apcomplex &apcomplex::operator/= (const apfloat &d)
{
    *this = *this / d;

    return *this;
}


// Overloaded mathematical functions

apcomplex pow (apcomplex base, unsigned long exp);
apcomplex pow (apcomplex base, unsigned exp);
apcomplex pow (apcomplex base, long exp);
apcomplex pow (apcomplex base, int exp);
apcomplex sqrt (apcomplex z);
apcomplex cbrt (apcomplex z);
apcomplex invroot (apcomplex u, unsigned n);
apfloat abs (apcomplex z);
apcomplex agm (apcomplex a, apcomplex b);
apcomplex exp (apcomplex z);
apcomplex rawlog (apcomplex z);
apcomplex log (apcomplex z);
apcomplex pow (apcomplex z, apfloat w);
apcomplex pow (apfloat z, apcomplex w);
apcomplex pow (apcomplex z, apcomplex w);
apcomplex acos (apcomplex z);
apcomplex acosh (apcomplex z);
apcomplex asin (apcomplex z);
apcomplex asinh (apcomplex z);
apcomplex atan (apcomplex z);
apcomplex atanh (apcomplex z);
apcomplex cos (apcomplex z);
apcomplex cosh (apcomplex z);
apcomplex sin (apcomplex z);
apcomplex sinh (apcomplex z);
apcomplex tan (apcomplex z);
apcomplex tanh (apcomplex z);

// Real trigonometric functions that use complex stuff
apfloat acos (apfloat x);
apfloat asin (apfloat x);
apfloat atan (apfloat x);
apfloat atan2 (apfloat x, apfloat y);
apfloat cos (apfloat x);
apfloat sin (apfloat x);
apfloat tan (apfloat x);


// Definitions of non-member apcomplex functions

inline apcomplex polar (apfloat mag, apfloat angle)
{
    return mag * exp (apcomplex (0, angle));
}

inline apfloat real (const apcomplex &z)
{
    return z.re;
}

inline apfloat imag (const apcomplex &z)
{
    return z.im;
}

inline apcomplex conj (const apcomplex &z)
{
    return apcomplex (z.re, -z.im);
}

inline apfloat norm (const apcomplex &z)
{
    return z.re * z.re + z.im * z.im;
}

inline apfloat arg (const apcomplex &z)
{
    return atan2 (z.re, z.im);
}


// Definitions of non-member binary operator functions

inline apcomplex operator+ (const apcomplex &z1, const apcomplex &z2)
{
    return apcomplex (z1.re + z2.re, z1.im + z2.im);
}

inline apcomplex operator+ (const apfloat &d1, const apcomplex &z2)
{
    return apcomplex (d1 + z2.re, z2.im);
}

inline apcomplex operator+ (const apcomplex &z1, const apfloat &d2)
{
    return apcomplex (z1.re + d2, z1.im);
}

inline apcomplex operator- (const apcomplex &z1, const apcomplex &z2)
{
    return apcomplex (z1.re - z2.re, z1.im - z2.im);
}

inline apcomplex operator- (const apfloat &d1, const apcomplex &z2)
{
    return apcomplex (d1 - z2.re, -z2.im);
}

inline apcomplex operator- (const apcomplex &z1, const apfloat &d2)
{
    return apcomplex (z1.re - d2, z1.im);
}

inline apcomplex operator* (const apfloat &d1, const apcomplex &z2)
{
    return apcomplex (d1 * z2.re, d1 * z2.im);
}

inline apcomplex operator* (const apcomplex &z1, const apfloat &d2)
{
    return apcomplex (z1.re * d2, z1.im * d2);
}

inline bool operator== (const apcomplex &z1, const apcomplex &z2)
{
    return (z1.re == z2.re && z1.im == z2.im);
}

inline bool operator== (const apfloat &d1, const apcomplex &z2)
{
    return (d1 == z2.re && !z2.im.sign ());
}

inline bool operator== (const apcomplex &z1, const apfloat &d2)
{
    return (z1.re == d2 && !z1.im.sign ());
}

inline bool operator!= (const apcomplex &z1, const apcomplex &z2)
{
    return (z1.re != z2.re || z1.im != z2.im);
}

inline bool operator!= (const apfloat &d1, const apcomplex &z2)
{
    return (d1 != z2.re || z2.im.sign ());
}

inline bool operator!= (const apcomplex &z1, const apfloat &d2)
{
    return (z1.re != d2 || z1.im.sign ());
}


#endif  // __APCPLX_H
