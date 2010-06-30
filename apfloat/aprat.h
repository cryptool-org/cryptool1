#ifndef __cplusplus
#error Must use C++ for the type aprational.
#endif


#if !defined(__APRAT_H)
#define __APRAT_H

#if !defined(__APINT_H)
#include "apint.h"
#endif


// Rational numbers class

class aprational
{
public:
    // Constructors
    aprational (const apint &newnom, const apint &newden = apint (1)) { nom = newnom; den = newden; if (autoreduce) reduce (); }
    aprational () {};

    // Operator functions
    friend aprational operator+ (const aprational &, const aprational &);
    friend aprational operator+ (const apint &, const aprational &);
    friend aprational operator+ (const aprational &, const apint &);
    friend aprational operator- (const aprational &, const aprational &);
    friend aprational operator- (const apint &, const aprational &);
    friend aprational operator- (const aprational &, const apint &);
    friend aprational operator* (const aprational &, const aprational &);
    friend aprational operator* (const apint &, const aprational &);
    friend aprational operator* (const aprational &, const apint &);
    friend aprational operator/ (const aprational &, const aprational &);
    friend aprational operator/ (const apint &, const aprational &);
    friend aprational operator/ (const aprational &, const apint &);
    friend bool operator== (const aprational &, const aprational &);
    friend bool operator== (const apint &, const aprational &);
    friend bool operator== (const aprational &, const apint &);
    friend bool operator!= (const aprational &, const aprational &);
    friend bool operator!= (const apint &, const aprational &);
    friend bool operator!= (const aprational &, const apint &);
    friend std::ostream &operator<< (std::ostream &, const aprational &);
    friend std::istream &operator>> (std::istream &, aprational &);
    aprational &operator+= (const aprational &);
    aprational &operator+= (const apint &);
    aprational &operator-= (const aprational &);
    aprational &operator-= (const apint &);
    aprational &operator*= (const aprational &);
    aprational &operator*= (const apint &);
    aprational &operator/= (const aprational &);
    aprational &operator/= (const apint &);
    aprational operator+ () const;
    aprational operator- () const;

    // Type-converted functions, some compilers can't do these automatically
    aprational (const apint &newnom, int newden) { nom = newnom; den = apint (newden); if (autoreduce) reduce (); }
    aprational (const apint &newnom, unsigned newden) { nom = newnom; den = apint (newden); if (autoreduce) reduce (); }
    aprational (const apint &newnom, long newden) { nom = newnom; den = apint (newden); if (autoreduce) reduce (); }
    aprational (const apint &newnom, unsigned long newden) { nom = newnom; den = apint (newden); if (autoreduce) reduce (); }
    aprational (const apint &newnom, double newden) { nom = newnom; den = apint (newden); if (autoreduce) reduce (); }
    aprational (const apint &newnom, char *newden) { nom = newnom; den = apint (newden); if (autoreduce) reduce (); }
    aprational (int newnom, const apint &newden = apint (1)) { nom = apint (newnom); den = newden; if (autoreduce) reduce (); }
    aprational (int newnom, int newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (int newnom, unsigned newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (int newnom, long newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (int newnom, unsigned long newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (int newnom, double newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (int newnom, char *newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (unsigned newnom, const apint &newden = apint (1)) { nom = apint (newnom); den = newden; if (autoreduce) reduce (); }
    aprational (unsigned newnom, int newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (unsigned newnom, unsigned newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (unsigned newnom, long newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (unsigned newnom, unsigned long newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (unsigned newnom, double newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (unsigned newnom, char *newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (long newnom, const apint &newden = apint (1)) { nom = apint (newnom); den = newden; if (autoreduce) reduce (); }
    aprational (long newnom, int newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (long newnom, unsigned newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (long newnom, long newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (long newnom, unsigned long newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (long newnom, double newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (long newnom, char *newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (unsigned long newnom, const apint &newden = apint (1)) { nom = apint (newnom); den = newden; if (autoreduce) reduce (); }
    aprational (unsigned long newnom, int newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (unsigned long newnom, unsigned newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (unsigned long newnom, long newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (unsigned long newnom, unsigned long newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (unsigned long newnom, double newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (unsigned long newnom, char *newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (double newnom, const apint &newden = apint (1)) { nom = apint (newnom); den = newden; if (autoreduce) reduce (); }
    aprational (double newnom, int newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (double newnom, unsigned newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (double newnom, long newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (double newnom, unsigned long newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (double newnom, double newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (double newnom, char *newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (char *newnom, const apint &newden = apint (1)) { nom = apint (newnom); den = newden; if (autoreduce) reduce (); }
    aprational (char *newnom, int newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (char *newnom, unsigned newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (char *newnom, long newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (char *newnom, unsigned long newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (char *newnom, double newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }
    aprational (char *newnom, char *newden) { nom = apint (newnom); den = apint (newden); if (autoreduce) reduce (); }

    friend aprational operator+ (int d1, const aprational &r2) { return apint (d1) + r2; }
    friend aprational operator+ (unsigned d1, const aprational &r2) { return apint (d1) + r2; }
    friend aprational operator+ (long d1, const aprational &r2) { return apint (d1) + r2; }
    friend aprational operator+ (unsigned long d1, const aprational &r2) { return apint (d1) + r2; }
    friend aprational operator+ (double d1, const aprational &r2) { return apint (d1) + r2; }
    friend aprational operator+ (char *d1, const aprational &r2) { return apint (d1) + r2; }
    friend aprational operator+ (const aprational &r1, int d2) { return r1 + apint (d2); }
    friend aprational operator+ (const aprational &r1, unsigned d2) { return r1 + apint (d2); }
    friend aprational operator+ (const aprational &r1, long d2) { return r1 + apint (d2); }
    friend aprational operator+ (const aprational &r1, unsigned long d2) { return r1 + apint (d2); }
    friend aprational operator+ (const aprational &r1, double d2) { return r1 + apint (d2); }
    friend aprational operator+ (const aprational &r1, char *d2) { return r1 + apint (d2); }
    friend aprational operator- (int d1, const aprational &r2) { return apint (d1) - r2; }
    friend aprational operator- (unsigned d1, const aprational &r2) { return apint (d1) - r2; }
    friend aprational operator- (long d1, const aprational &r2) { return apint (d1) - r2; }
    friend aprational operator- (unsigned long d1, const aprational &r2) { return apint (d1) - r2; }
    friend aprational operator- (double d1, const aprational &r2) { return apint (d1) - r2; }
    friend aprational operator- (char *d1, const aprational &r2) { return apint (d1) - r2; }
    friend aprational operator- (const aprational &r1, int d2) { return r1 - apint (d2); }
    friend aprational operator- (const aprational &r1, unsigned d2) { return r1 - apint (d2); }
    friend aprational operator- (const aprational &r1, long d2) { return r1 - apint (d2); }
    friend aprational operator- (const aprational &r1, unsigned long d2) { return r1 - apint (d2); }
    friend aprational operator- (const aprational &r1, double d2) { return r1 - apint (d2); }
    friend aprational operator- (const aprational &r1, char *d2) { return r1 - apint (d2); }
    friend aprational operator* (int d1, const aprational &r2) { return apint (d1) * r2; }
    friend aprational operator* (unsigned d1, const aprational &r2) { return apint (d1) * r2; }
    friend aprational operator* (long d1, const aprational &r2) { return apint (d1) * r2; }
    friend aprational operator* (unsigned long d1, const aprational &r2) { return apint (d1) * r2; }
    friend aprational operator* (double d1, const aprational &r2) { return apint (d1) * r2; }
    friend aprational operator* (char *d1, const aprational &r2) { return apint (d1) * r2; }
    friend aprational operator* (const aprational &r1, int d2) { return r1 * apint (d2); }
    friend aprational operator* (const aprational &r1, unsigned d2) { return r1 * apint (d2); }
    friend aprational operator* (const aprational &r1, long d2) { return r1 * apint (d2); }
    friend aprational operator* (const aprational &r1, unsigned long d2) { return r1 * apint (d2); }
    friend aprational operator* (const aprational &r1, double d2) { return r1 * apint (d2); }
    friend aprational operator* (const aprational &r1, char *d2) { return r1 * apint (d2); }
    friend aprational operator/ (int d1, const aprational &r2) { return apint (d1) / r2; }
    friend aprational operator/ (unsigned d1, const aprational &r2) { return apint (d1) / r2; }
    friend aprational operator/ (long d1, const aprational &r2) { return apint (d1) / r2; }
    friend aprational operator/ (unsigned long d1, const aprational &r2) { return apint (d1) / r2; }
    friend aprational operator/ (double d1, const aprational &r2) { return apint (d1) / r2; }
    friend aprational operator/ (char *d1, const aprational &r2) { return apint (d1) / r2; }
    friend aprational operator/ (const aprational &r1, int d2) { return r1 / apint (d2); }
    friend aprational operator/ (const aprational &r1, unsigned d2) { return r1 / apint (d2); }
    friend aprational operator/ (const aprational &r1, long d2) { return r1 / apint (d2); }
    friend aprational operator/ (const aprational &r1, unsigned long d2) { return r1 / apint (d2); }
    friend aprational operator/ (const aprational &r1, double d2) { return r1 / apint (d2); }
    friend aprational operator/ (const aprational &r1, char *d2) { return r1 / apint (d2); }

    friend bool operator== (int d1, const aprational &r2) { return apint (d1) == r2; }
    friend bool operator== (unsigned d1, const aprational &r2) { return apint (d1) == r2; }
    friend bool operator== (long d1, const aprational &r2) { return apint (d1) == r2; }
    friend bool operator== (unsigned long d1, const aprational &r2) { return apint (d1) == r2; }
    friend bool operator== (double d1, const aprational &r2) { return apint (d1) == r2; }
    friend bool operator== (char *d1, const aprational &r2) { return apint (d1) == r2; }
    friend bool operator== (const aprational &r1, int d2) { return r1 == apint (d2); }
    friend bool operator== (const aprational &r1, unsigned d2) { return r1 == apint (d2); }
    friend bool operator== (const aprational &r1, long d2) { return r1 == apint (d2); }
    friend bool operator== (const aprational &r1, unsigned long d2) { return r1 == apint (d2); }
    friend bool operator== (const aprational &r1, double d2) { return r1 == apint (d2); }
    friend bool operator== (const aprational &r1, char *d2) { return r1 == apint (d2); }
    friend bool operator!= (int d1, const aprational &r2) { return apint (d1) != r2; }
    friend bool operator!= (unsigned d1, const aprational &r2) { return apint (d1) != r2; }
    friend bool operator!= (long d1, const aprational &r2) { return apint (d1) != r2; }
    friend bool operator!= (unsigned long d1, const aprational &r2) { return apint (d1) != r2; }
    friend bool operator!= (double d1, const aprational &r2) { return apint (d1) != r2; }
    friend bool operator!= (char *d1, const aprational &r2) { return apint (d1) != r2; }
    friend bool operator!= (const aprational &r1, int d2) { return r1 != apint (d2); }
    friend bool operator!= (const aprational &r1, unsigned d2) { return r1 != apint (d2); }
    friend bool operator!= (const aprational &r1, long d2) { return r1 != apint (d2); }
    friend bool operator!= (const aprational &r1, unsigned long d2) { return r1 != apint (d2); }
    friend bool operator!= (const aprational &r1, double d2) { return r1 != apint (d2); }
    friend bool operator!= (const aprational &r1, char *d2) { return r1 != apint (d2); }

    aprational &operator+= (int d) { *this = *this + apint (d); return *this; }
    aprational &operator+= (unsigned d) { *this = *this + apint (d); return *this; }
    aprational &operator+= (long d) { *this = *this + apint (d); return *this; }
    aprational &operator+= (unsigned long d) { *this = *this + apint (d); return *this; }
    aprational &operator+= (double d) { *this = *this + apint (d); return *this; }
    aprational &operator+= (char *d) { *this = *this + apint (d); return *this; }
    aprational &operator-= (int d) { *this = *this - apint (d); return *this; }
    aprational &operator-= (unsigned d) { *this = *this - apint (d); return *this; }
    aprational &operator-= (long d) { *this = *this - apint (d); return *this; }
    aprational &operator-= (unsigned long d) { *this = *this - apint (d); return *this; }
    aprational &operator-= (double d) { *this = *this - apint (d); return *this; }
    aprational &operator-= (char *d) { *this = *this - apint (d); return *this; }
    aprational &operator*= (int d) { *this = *this * apint (d); return *this; }
    aprational &operator*= (unsigned d) { *this = *this * apint (d); return *this; }
    aprational &operator*= (long d) { *this = *this * apint (d); return *this; }
    aprational &operator*= (unsigned long d) { *this = *this * apint (d); return *this; }
    aprational &operator*= (double d) { *this = *this * apint (d); return *this; }
    aprational &operator*= (char *d) { *this = *this * apint (d); return *this; }
    aprational &operator/= (int d) { *this = *this / apint (d); return *this; }
    aprational &operator/= (unsigned d) { *this = *this / apint (d); return *this; }
    aprational &operator/= (long d) { *this = *this / apint (d); return *this; }
    aprational &operator/= (unsigned long d) { *this = *this / apint (d); return *this; }
    aprational &operator/= (double d) { *this = *this / apint (d); return *this; }
    aprational &operator/= (char *d) { *this = *this / apint (d); return *this; }
    aprational &operator= (const apint &d) { nom = d; den = apint (1); return *this; }
    aprational &operator= (int d) { nom = apint (d); den = apint (1); return *this; }
    aprational &operator= (unsigned d) { nom = apint (d); den = apint (1); return *this; }
    aprational &operator= (long d) { nom = apint (d); den = apint (1); return *this; }
    aprational &operator= (unsigned long d) { nom = apint (d); den = apint (1); return *this; }
    aprational &operator= (double d) { nom = apint (d); den = apint (1); return *this; }
    aprational &operator= (char *d) { nom = apint (d); den = apint (1); return *this; }

    // Type conversion
    operator apfloat () { return nom / den; }

    // Other functions
    void reduce (void);
    apfloat approx (size_t prec = (size_t) DEFAULT);
    void swapfrom (char *filename1, char *filename2) { nom.swapfrom (filename1); den.swapfrom (filename2); }
    void swapto (char *filename1, char *filename2) { nom.swapto (filename1); den.swapto (filename2); }

    // Global variables
    static bool autoreduce;

    // Implementation
    apint nom, den;                           // Won't be private
};


// Inline aprational functions

inline aprational aprational::operator+ () const
{
    return *this;
}

inline aprational aprational::operator- () const
{
    return aprational (-nom, den);
}


// Definitions of compound-assignment operator member functions

inline aprational &aprational::operator+= (const aprational &r)
{
    nom = nom * r.den + den * r.nom;
    den = den * r.den;

    if (autoreduce) reduce ();

    return *this;
}

inline aprational &aprational::operator+= (const apint &d)
{
    nom = nom + den * d;

    if (autoreduce) reduce ();

    return *this;
}

inline aprational &aprational::operator-= (const aprational &r)
{
    nom = nom * r.den - den * r.nom;
    den = den * r.den;

    if (autoreduce) reduce ();

    return *this;
}

inline aprational &aprational::operator-= (const apint &d)
{
    nom = nom - den * d;

    if (autoreduce) reduce ();

    return *this;
}

inline aprational &aprational::operator*= (const aprational &r)
{
    nom = nom * r.nom;
    den = den * r.den;

    if (autoreduce) reduce ();

    return *this;
}

inline aprational &aprational::operator*= (const apint &d)
{
    nom = nom * d;

    if (autoreduce) reduce ();

    return *this;
}

inline aprational &aprational::operator/= (const aprational &r)
{
    nom = nom * r.den;
    den = den * r.nom;

    if (autoreduce) reduce ();

    return *this;
}

inline aprational &aprational::operator/= (const apint &d)
{
    den = den * d;

    if (autoreduce) reduce ();

    return *this;
}


// Overloaded mathematical functions

aprational pow (aprational base, unsigned long exp);
aprational pow (aprational base, unsigned exp);
aprational pow (aprational base, long exp);
aprational pow (aprational base, int exp);

// Definitions of non-member binary operator functions

inline aprational operator+ (const aprational &r1, const aprational &r2)
{
    return aprational (r1.nom * r2.den + r1.den * r2.nom, r1.den * r2.den);
}

inline aprational operator+ (const apint &d1, const aprational &r2)
{
    return aprational (d1 * r2.den + r2.nom, r2.den);
}

inline aprational operator+ (const aprational &r1, const apint &d2)
{
    return aprational (r1.nom + r1.den * d2, r1.den);
}

inline aprational operator- (const aprational &r1, const aprational &r2)
{
    return aprational (r1.nom * r2.den - r1.den * r2.nom, r1.den * r2.den);
}

inline aprational operator- (const apint &d1, const aprational &r2)
{
    return aprational (d1 * r2.den - r2.nom, r2.den);
}

inline aprational operator- (const aprational &r1, const apint &d2)
{
    return aprational (r1.nom - r1.den * d2, r1.den);
}

inline aprational operator* (const aprational &r1, const aprational &r2)
{
    return aprational (r1.nom * r2.nom, r1.den * r2.den);
}

inline aprational operator* (const apint &d1, const aprational &r2)
{
    return aprational (d1 * r2.nom, r2.den);
}

inline aprational operator* (const aprational &r1, const apint &d2)
{
    return aprational (r1.nom * d2, r1.den);
}

inline aprational operator/ (const aprational &r1, const aprational &r2)
{
    return aprational (r1.nom * r2.den, r1.den * r2.nom);
}

inline aprational operator/ (const apint &d1, const aprational &r2)
{
    return aprational (d1 * r2.den, r2.nom);
}

inline aprational operator/ (const aprational &r1, const apint &d2)
{
    return aprational (r1.nom, r1.den * d2);
}

inline bool operator== (const aprational &r1, const aprational &r2)
{
    return (r1.nom == r2.nom && r1.den == r2.den);
}

inline bool operator== (const apint &d1, const aprational &r2)
{
    return (d1 == r2.nom && r2.den == 1);
}

inline bool operator== (const aprational &r1, const apint &d2)
{
    return (r1.nom == d2 && r1.den == 1);
}

inline bool operator!= (const aprational &r1, const aprational &r2)
{
    return (r1.nom != r2.nom || r1.den != r2.den);
}

inline bool operator!= (const apint &d1, const aprational &r2)
{
    return (d1 != r2.nom || r2.den != 1);
}

inline bool operator!= (const aprational &r1, const apint &d2)
{
    return (r1.nom != d2 || r1.den != 1);
}


#endif  // __APRAT_H
