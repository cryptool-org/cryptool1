#ifndef __cplusplus
#error Must use C++ for the type apint.
#endif


#if !defined(__APINT_H)
#define __APINT_H

#if !defined(__APFLOAT_H)
#include "apfloat.h"
#endif


// Integer number class

class apint
{
public:
    // Constructors
    apint (const apfloat &newval) { val = floor (newval); }
    apint () {};

    // Operator functions
    friend apint operator+ (const apint &, const apint &);
    friend apint operator- (const apint &, const apint &);
    friend apint operator* (const apint &, const apint &);
    friend apint operator/ (const apint &, const apint &);
    friend apint operator% (const apint &, const apint &);
    friend apint operator<< (const apint &, size_t);
    friend apint operator>> (const apint &, size_t);
    friend bool operator== (const apint &, const apint &);
    friend bool operator!= (const apint &, const apint &);
    friend bool operator>= (const apint &, const apint &);
    friend bool operator<= (const apint &, const apint &);
    friend bool operator> (const apint &, const apint &);
    friend bool operator< (const apint &, const apint &);
    friend std::ostream &operator<< (std::ostream &, const apint &);
    friend std::istream &operator>> (std::istream &, apint &);
    apint &operator++ ();
    apint &operator-- ();
    apint operator++ (int);
    apint operator-- (int);
    apint &operator+= (const apint &);
    apint &operator-= (const apint &);
    apint &operator*= (const apint &);
    apint &operator/= (const apint &);
    apint &operator%= (const apint &);
    apint &operator<<= (size_t);
    apint &operator>>= (size_t);
    apint operator+ () const;
    apint operator- () const;

    // Type-converted functions
    apint (int newval) { val = apfloat (newval); }
    apint (unsigned newval) { val = apfloat (newval); }
    apint (long newval) { val = apfloat (newval); }
    apint (unsigned long newval) { val = apfloat (newval); }
    apint (double newval) { val = floor (apfloat (newval)); }
    apint (char *newval) { val = floor (apfloat (newval)); }

    friend apint operator+ (int d1, const apint &d2) { return apint (d1) + d2; }
    friend apint operator+ (unsigned d1, const apint &d2) { return apint (d1) + d2; }
    friend apint operator+ (long d1, const apint &d2) { return apint (d1) + d2; }
    friend apint operator+ (unsigned long d1, const apint &d2) { return apint (d1) + d2; }
    friend apint operator+ (const apint &d1, int d2) { return d1 + apint (d2); }
    friend apint operator+ (const apint &d1, unsigned d2) { return d1 + apint (d2); }
    friend apint operator+ (const apint &d1, long d2) { return d1 + apint (d2); }
    friend apint operator+ (const apint &d1, unsigned long d2) { return d1 + apint (d2); }
    friend apint operator- (int d1, const apint &d2) { return apint (d1) - d2; }
    friend apint operator- (unsigned d1, const apint &d2) { return apint (d1) - d2; }
    friend apint operator- (long d1, const apint &d2) { return apint (d1) - d2; }
    friend apint operator- (unsigned long d1, const apint &d2) { return apint (d1) - d2; }
    friend apint operator- (const apint &d1, int d2) { return d1 - apint (d2); }
    friend apint operator- (const apint &d1, unsigned d2) { return d1 - apint (d2); }
    friend apint operator- (const apint &d1, long d2) { return d1 - apint (d2); }
    friend apint operator- (const apint &d1, unsigned long d2) { return d1 - apint (d2); }
    friend apint operator* (int d1, const apint &d2) { return apint (d1) * d2; }
    friend apint operator* (unsigned d1, const apint &d2) { return apint (d1) * d2; }
    friend apint operator* (long d1, const apint &d2) { return apint (d1) * d2; }
    friend apint operator* (unsigned long d1, const apint &d2) { return apint (d1) * d2; }
    friend apint operator* (const apint &d1, int d2) { return d1 * apint (d2); }
    friend apint operator* (const apint &d1, unsigned d2) { return d1 * apint (d2); }
    friend apint operator* (const apint &d1, long d2) { return d1 * apint (d2); }
    friend apint operator* (const apint &d1, unsigned long d2) { return d1 * apint (d2); }
    friend apint operator/ (int d1, const apint &d2) { return apint (d1) / d2; }
    friend apint operator/ (unsigned d1, const apint &d2) { return apint (d1) / d2; }
    friend apint operator/ (long d1, const apint &d2) { return apint (d1) / d2; }
    friend apint operator/ (unsigned long d1, const apint &d2) { return apint (d1) / d2; }
    friend apint operator/ (const apint &d1, int d2) { return d1 / apint (d2); }
    friend apint operator/ (const apint &d1, unsigned d2) { return d1 / apint (d2); }
    friend apint operator/ (const apint &d1, long d2) { return d1 / apint (d2); }
    friend apint operator/ (const apint &d1, unsigned long d2) { return d1 / apint (d2); }
    friend apint operator% (int d1, const apint &d2) { return apint (d1) % d2; }
    friend apint operator% (unsigned d1, const apint &d2) { return apint (d1) % d2; }
    friend apint operator% (long d1, const apint &d2) { return apint (d1) % d2; }
    friend apint operator% (unsigned long d1, const apint &d2) { return apint (d1) % d2; }
    friend apint operator% (const apint &d1, int d2) { return d1 % apint (d2); }
    friend apint operator% (const apint &d1, unsigned d2) { return d1 % apint (d2); }
    friend apint operator% (const apint &d1, long d2) { return d1 % apint (d2); }
    friend apint operator% (const apint &d1, unsigned long d2) { return d1 % apint (d2); }

    friend apfloat operator+ (double d1, const apint &d2) { return apfloat (d1) + d2.val; }
    friend apfloat operator+ (char *d1, const apint &d2) { return apfloat (d1) + d2.val; }
    friend apfloat operator+ (const apint &d1, double d2) { return d1.val + apfloat (d2); }
    friend apfloat operator+ (const apint &d1, char *d2) { return d1.val + apfloat (d2); }
    friend apfloat operator- (double d1, const apint &d2) { return apfloat (d1) - d2.val; }
    friend apfloat operator- (char *d1, const apint &d2) { return apfloat (d1) - d2.val; }
    friend apfloat operator- (const apint &d1, double d2) { return d1.val - apfloat (d2); }
    friend apfloat operator- (const apint &d1, char *d2) { return d1.val - apfloat (d2); }
    friend apfloat operator* (double d1, const apint &d2) { return apfloat (d1) * d2.val; }
    friend apfloat operator* (char *d1, const apint &d2) { return apfloat (d1) * d2.val; }
    friend apfloat operator* (const apint &d1, double d2) { return d1.val * apfloat (d2); }
    friend apfloat operator* (const apint &d1, char *d2) { return d1.val * apfloat (d2); }
    friend apfloat operator/ (double d1, const apint &d2) { return apfloat (d1) / d2.val; }
    friend apfloat operator/ (char *d1, const apint &d2) { return apfloat (d1) / d2.val; }
    friend apfloat operator/ (const apint &d1, double d2) { return d1.val / apfloat (d2); }
    friend apfloat operator/ (const apint &d1, char *d2) { return d1.val / apfloat (d2); }

    friend bool operator== (int d1, const apint &d2) { return apfloat (d1) == d2.val; }
    friend bool operator== (unsigned d1, const apint &d2) { return apfloat (d1) == d2.val; }
    friend bool operator== (long d1, const apint &d2) { return apfloat (d1) == d2.val; }
    friend bool operator== (unsigned long d1, const apint &d2) { return apfloat (d1) == d2.val; }
    friend bool operator== (double d1, const apint &d2) { return apfloat (d1) == d2.val; }
    friend bool operator== (char *d1, const apint &d2) { return apfloat (d1) == d2.val; }
    friend bool operator== (const apint &d1, int d2) { return d1.val == apfloat (d2); }
    friend bool operator== (const apint &d1, unsigned d2) { return d1.val == apfloat (d2); }
    friend bool operator== (const apint &d1, long d2) { return d1.val == apfloat (d2); }
    friend bool operator== (const apint &d1, unsigned long d2) { return d1.val == apfloat (d2); }
    friend bool operator== (const apint &d1, double d2) { return d1.val == apfloat (d2); }
    friend bool operator== (const apint &d1, char *d2) { return d1.val == apfloat (d2); }
    friend bool operator!= (int d1, const apint &d2) { return apfloat (d1) != d2.val; }
    friend bool operator!= (unsigned d1, const apint &d2) { return apfloat (d1) != d2.val; }
    friend bool operator!= (long d1, const apint &d2) { return apfloat (d1) != d2.val; }
    friend bool operator!= (unsigned long d1, const apint &d2) { return apfloat (d1) != d2.val; }
    friend bool operator!= (double d1, const apint &d2) { return apfloat (d1) != d2.val; }
    friend bool operator!= (char *d1, const apint &d2) { return apfloat (d1) != d2.val; }
    friend bool operator!= (const apint &d1, int d2) { return d1.val != apfloat (d2); }
    friend bool operator!= (const apint &d1, unsigned d2) { return d1.val != apfloat (d2); }
    friend bool operator!= (const apint &d1, long d2) { return d1.val != apfloat (d2); }
    friend bool operator!= (const apint &d1, unsigned long d2) { return d1.val != apfloat (d2); }
    friend bool operator!= (const apint &d1, double d2) { return d1.val != apfloat (d2); }
    friend bool operator!= (const apint &d1, char *d2) { return d1.val != apfloat (d2); }
    friend bool operator>= (int d1, const apint &d2) { return apfloat (d1) >= d2.val; }
    friend bool operator>= (unsigned d1, const apint &d2) { return apfloat (d1) >= d2.val; }
    friend bool operator>= (long d1, const apint &d2) { return apfloat (d1) >= d2.val; }
    friend bool operator>= (unsigned long d1, const apint &d2) { return apfloat (d1) >= d2.val; }
    friend bool operator>= (double d1, const apint &d2) { return apfloat (d1) >= d2.val; }
    friend bool operator>= (char *d1, const apint &d2) { return apfloat (d1) >= d2.val; }
    friend bool operator>= (const apint &d1, int d2) { return d1.val >= apfloat (d2); }
    friend bool operator>= (const apint &d1, unsigned d2) { return d1.val >= apfloat (d2); }
    friend bool operator>= (const apint &d1, long d2) { return d1.val >= apfloat (d2); }
    friend bool operator>= (const apint &d1, unsigned long d2) { return d1.val >= apfloat (d2); }
    friend bool operator>= (const apint &d1, double d2) { return d1.val >= apfloat (d2); }
    friend bool operator>= (const apint &d1, char *d2) { return d1.val >= apfloat (d2); }
    friend bool operator<= (int d1, const apint &d2) { return apfloat (d1) <= d2.val; }
    friend bool operator<= (unsigned d1, const apint &d2) { return apfloat (d1) <= d2.val; }
    friend bool operator<= (long d1, const apint &d2) { return apfloat (d1) <= d2.val; }
    friend bool operator<= (unsigned long d1, const apint &d2) { return apfloat (d1) <= d2.val; }
    friend bool operator<= (double d1, const apint &d2) { return apfloat (d1) <= d2.val; }
    friend bool operator<= (char *d1, const apint &d2) { return apfloat (d1) <= d2.val; }
    friend bool operator<= (const apint &d1, int d2) { return d1.val <= apfloat (d2); }
    friend bool operator<= (const apint &d1, unsigned d2) { return d1.val <= apfloat (d2); }
    friend bool operator<= (const apint &d1, long d2) { return d1.val <= apfloat (d2); }
    friend bool operator<= (const apint &d1, unsigned long d2) { return d1.val <= apfloat (d2); }
    friend bool operator<= (const apint &d1, double d2) { return d1.val <= apfloat (d2); }
    friend bool operator<= (const apint &d1, char *d2) { return d1.val <= apfloat (d2); }
    friend bool operator> (int d1, const apint &d2) { return apfloat (d1) > d2.val; }
    friend bool operator> (unsigned d1, const apint &d2) { return apfloat (d1) > d2.val; }
    friend bool operator> (long d1, const apint &d2) { return apfloat (d1) > d2.val; }
    friend bool operator> (unsigned long d1, const apint &d2) { return apfloat (d1) > d2.val; }
    friend bool operator> (double d1, const apint &d2) { return apfloat (d1) > d2.val; }
    friend bool operator> (char *d1, const apint &d2) { return apfloat (d1) > d2.val; }
    friend bool operator> (const apint &d1, int d2) { return d1.val > apfloat (d2); }
    friend bool operator> (const apint &d1, unsigned d2) { return d1.val > apfloat (d2); }
    friend bool operator> (const apint &d1, long d2) { return d1.val > apfloat (d2); }
    friend bool operator> (const apint &d1, unsigned long d2) { return d1.val > apfloat (d2); }
    friend bool operator> (const apint &d1, double d2) { return d1.val > apfloat (d2); }
    friend bool operator> (const apint &d1, char *d2) { return d1.val > apfloat (d2); }
    friend bool operator< (int d1, const apint &d2) { return apfloat (d1) < d2.val; }
    friend bool operator< (unsigned d1, const apint &d2) { return apfloat (d1) < d2.val; }
    friend bool operator< (long d1, const apint &d2) { return apfloat (d1) < d2.val; }
    friend bool operator< (unsigned long d1, const apint &d2) { return apfloat (d1) < d2.val; }
    friend bool operator< (double d1, const apint &d2) { return apfloat (d1) < d2.val; }
    friend bool operator< (char *d1, const apint &d2) { return apfloat (d1) < d2.val; }
    friend bool operator< (const apint &d1, int d2) { return d1.val < apfloat (d2); }
    friend bool operator< (const apint &d1, unsigned d2) { return d1.val < apfloat (d2); }
    friend bool operator< (const apint &d1, long d2) { return d1.val < apfloat (d2); }
    friend bool operator< (const apint &d1, unsigned long d2) { return d1.val < apfloat (d2); }
    friend bool operator< (const apint &d1, double d2) { return d1.val < apfloat (d2); }
    friend bool operator< (const apint &d1, char *d2) { return d1.val < apfloat (d2); }

    apint &operator+= (int d) { val = val + d; return *this; }
    apint &operator+= (unsigned d) { val = val + d; return *this; }
    apint &operator+= (long d) { val = val + d; return *this; }
    apint &operator+= (unsigned long d) { val = val + d; return *this; }
    apint &operator+= (double d) { *this = val + d; return *this; }
    apint &operator+= (char *d) { *this = val + d; return *this; }
    apint &operator-= (int d) { val = val - d; return *this; }
    apint &operator-= (unsigned d) { val = val - d; return *this; }
    apint &operator-= (long d) { val = val - d; return *this; }
    apint &operator-= (unsigned long d) { val = val - d; return *this; }
    apint &operator-= (double d) { *this = val - d; return *this; }
    apint &operator-= (char *d) { *this = val - d; return *this; }
    apint &operator*= (int d) { val = val * d; return *this; }
    apint &operator*= (unsigned d) { val = val * d; return *this; }
    apint &operator*= (long d) { val = val * d; return *this; }
    apint &operator*= (unsigned long d) { val = val * d; return *this; }
    apint &operator*= (double d) { *this = val * d; return *this; }
    apint &operator*= (char *d) { *this = val * d; return *this; }
    apint &operator/= (int d) { *this = *this / apint (d); return *this; }
    apint &operator/= (unsigned d) { *this = *this / apint (d); return *this; }
    apint &operator/= (long d) { *this = *this / apint (d); return *this; }
    apint &operator/= (unsigned long d) { *this = *this / apint (d); return *this; }
    apint &operator/= (double d) { *this = val / d; return *this; }
    apint &operator/= (char *d) { *this = val / d; return *this; }
    apint &operator%= (int d) { *this = *this % d; return *this; }
    apint &operator%= (unsigned d) { *this = *this % d; return *this; }
    apint &operator%= (long d) { *this = *this % d; return *this; }
    apint &operator%= (unsigned long d) { *this = *this % d; return *this; }
    apint &operator= (int d) { val = apfloat (d); return *this; }
    apint &operator= (unsigned d) { val = apfloat (d); return *this; }
    apint &operator= (long d) { val = apfloat (d); return *this; }
    apint &operator= (unsigned long d) { val = apfloat (d); return *this; }
    apint &operator= (double d) { *this = apfloat (d); return *this; }
    apint &operator= (char *d) { *this = apfloat (d); return *this; }

    // Functions to convert between apfloat and apint
    friend apfloat operator+ (const apfloat &d1, const apint &d2) { return d1 + d2.val; }
    friend apfloat operator+ (const apint &d1, const apfloat &d2) { return d1.val + d2; }
    friend apfloat operator- (const apfloat &d1, const apint &d2) { return d1 - d2.val; }
    friend apfloat operator- (const apint &d1, const apfloat &d2) { return d1.val - d2; }
    friend apfloat operator* (const apfloat &d1, const apint &d2) { return d1 * d2.val; }
    friend apfloat operator* (const apint &d1, const apfloat &d2) { return d1.val * d2; }
    friend apfloat operator/ (const apfloat &d1, const apint &d2) { return d1 / d2.val; }
    friend apfloat operator/ (const apint &d1, const apfloat &d2) { return d1.val / d2; }
    friend bool operator== (const apfloat &d1, const apint &d2) { return d1 == d2.val; }
    friend bool operator== (const apint &d1, const apfloat &d2) { return d1.val == d2; }
    friend bool operator!= (const apfloat &d1, const apint &d2) { return d1 != d2.val; }
    friend bool operator!= (const apint &d1, const apfloat &d2) { return d1.val != d2; }
    friend bool operator>= (const apfloat &d1, const apint &d2) { return d1 >= d2.val; }
    friend bool operator>= (const apint &d1, const apfloat &d2) { return d1.val >= d2; }
    friend bool operator<= (const apfloat &d1, const apint &d2) { return d1 <= d2.val; }
    friend bool operator<= (const apint &d1, const apfloat &d2) { return d1.val <= d2; }
    friend bool operator> (const apfloat &d1, const apint &d2) { return d1 > d2.val; }
    friend bool operator> (const apint &d1, const apfloat &d2) { return d1.val > d2; }
    friend bool operator< (const apfloat &d1, const apint &d2) { return d1 < d2.val; }
    friend bool operator< (const apint &d1, const apfloat &d2) { return d1.val < d2; }
    apint &operator+= (const apfloat &d) { *this = val + d; return *this; }
    apint &operator-= (const apfloat &d) { *this = val - d; return *this; }
    apint &operator*= (const apfloat &d) { *this = val * d; return *this; }
    apint &operator/= (const apfloat &d) { *this = val / d; return *this; }
    apint &operator= (const apfloat &d) { val = floor (d); return *this; }

    // Type conversion
    operator apfloat () { return val; }

    // Other functions
    int sign (void) const { return val.sign (); }
    void sign (int newsign) { val.sign (newsign); }
    long exp (void) const { return val.exp (); }
    void exp (long newexp) { val.exp (newexp); }
    size_t prec (void) const { return val.prec (); }
    void swapfrom (char *filename) { val.swapfrom (filename); }
    void swapto (char *filename) { val.swapto (filename); }

    // Implementation
    apfloat val;                                // Won't be private
};

typedef struct apdiv_struct
{
    apint quot;
    apint rem;
} apdiv_t;

// Inline apint functions

inline apint apint::operator+ () const
{
    return *this;
}

inline apint apint::operator- () const
{
    return apint (-val);
}


// Definitions of compound-assignment operator member functions

inline apint &apint::operator+= (const apint &d)
{
    val = val + d.val;

    return *this;
}

inline apint &apint::operator-= (const apint &d)
{
    val = val - d.val;

    return *this;
}

inline apint &apint::operator*= (const apint &d)
{
    val = val * d.val;

    return *this;
}

inline apint &apint::operator/= (const apint &d)
{
    *this = *this / d;

    return *this;
}

inline apint &apint::operator%= (const apint &d)
{
    *this = *this % d;

    return *this;
}

inline apint &apint::operator<<= (size_t d)
{
    val = val * pow (apfloat (2), d);

    return *this;
}

inline apint &apint::operator>>= (size_t d)
{
    *this = *this / apint (pow (apfloat (2), d));

    return *this;
}

// flomar, 07/02/2010: hack of the day
void startApfloatComputation();
void cancelApfloatComputation();

// Overloaded mathematical functions

apint pow (apint base, unsigned long exp);
apint pow (apint base, unsigned exp);
apint pow (apint base, long exp);
apint pow (apint base, int exp);
apint abs (apint x);
apdiv_t div (apint numer, apint denom);
apint factorial (unsigned long n, unsigned long m = 1);
apint gcd (apint a, apint b);
apint lcm (apint a, apint b);
apint powmod (apint base, apint exp, apint modulus);

// Definitions of non-member binary operator functions

inline apint operator+ (const apint &d1, const apint &d2)
{
    return apint (d1.val + d2.val);
}

inline apint operator- (const apint &d1, const apint &d2)
{
    return apint (d1.val - d2.val);
}

inline apint operator* (const apint &d1, const apint &d2)
{
    return apint (d1.val * d2.val);
}

inline apint operator<< (const apint &d1, size_t d2)
{
    return apint (d1.val * pow (apfloat (2), d2));
}

inline apint operator>> (const apint &d1, size_t d2)
{
    return d1 / pow (apfloat (2), d2);
}

inline bool operator== (const apint &d1, const apint &d2)
{
    return (d1.val == d2.val);
}

inline bool operator!= (const apint &d1, const apint &d2)
{
    return (d1.val != d2.val);
}

inline bool operator>= (const apint &d1, const apint &d2)
{
    return (d1.val >= d2.val);
}

inline bool operator<= (const apint &d1, const apint &d2)
{
    return (d1.val <= d2.val);
}

inline bool operator> (const apint &d1, const apint &d2)
{
    return (d1.val > d2.val);
}

inline bool operator< (const apint &d1, const apint &d2)
{
    return (d1.val < d2.val);
}

inline std::ostream &operator<< (std::ostream &str, const apint &d)
{
    str << pretty << d.val;

    return str;
}


#endif  // __APINT_H
