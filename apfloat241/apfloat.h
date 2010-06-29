#ifndef __cplusplus
#error Must use C++ for the type apfloat.
#endif


#if !defined(__APFLOAT_H)
#define __APFLOAT_H


#include <cstddef>                             // For size_t
#include <fstream>
#include <iostream>


// Some compilers may have already defined these, which will break apfloat
#ifdef INFINITE
#undef INFINITE
#endif


// Don't need the whole modint.h or ap.h here
class modint;
void apbase (int digit);


// BIN should be defined to bin (old gcc versions) or binary (new compilers) in the makefile
#ifndef BIN
#define BIN binary
#endif

// Data location
const int MEMORY = 0;
const int DISK = 1;
const int DEFAULT = -1;

// Precision of integers
const size_t INFINITE = (1UL << (sizeof (size_t) * 8 - 1)) - 1;

// Maximum size to use the n^2 multiplication
const size_t USE_N2_MUL = 50;


// The datastruct class
// Holds the mantissa of an apfloat, either in memory or on disk
class datastruct
{
public:
    // Constructors
    datastruct (size_t newsize = 0, modint *newdata = 0, int newlocation = DEFAULT, int fill = 1);
    datastruct (datastruct &d, size_t newsize = (size_t) DEFAULT, int newlocation = DEFAULT, size_t padsize = (size_t) DEFAULT);

    // Destructor
    ~datastruct ();

    // Functions
    modint *getdata (size_t getposition, size_t getsize);
    void putdata (void);
    modint *readydata (size_t getposition, size_t getsize);
    void cleardata (void);

    std::fstream &openstream (void);
    void closestream (void);

    void resize (size_t newsize);
    void relocate (int newlocation, size_t newsize = (size_t) DEFAULT);

    void capture (const char *newfilename);
    void release (const char *newfilename);

    // Implementation
    size_t size;
    int location;

private:
    modint *data;
    bool gotdata;
    size_t position;
    size_t blocksize;
    int fileno;
    std::fstream *fs;
};


// The apstruct class
// Holds the rest of the information of an apfloat
class apstruct : public datastruct
{
public:
    // Constructors
    apstruct (int newsign = 0, long newexp = 0, size_t newprec = INFINITE, size_t newsize = 0, modint *newdata = 0, int newlocation = DEFAULT, int fill = 1);  // Zero default
    apstruct (apstruct &d, size_t newsize = (size_t) DEFAULT, int newlocation = DEFAULT, size_t padsize = (size_t) DEFAULT);

    // Destructor
    ~apstruct ();

    // Implementation
    int nlinks;
    int sign;
    long exp;
    size_t prec;
};

inline apstruct::apstruct (int newsign, long newexp, size_t newprec, size_t newsize, modint *newdata, int newlocation, int fill)
                          : datastruct (newsize, newdata, newlocation, fill)
{
    nlinks = 1;
    sign = newsign;
    exp = newexp;
    prec = newprec;

    // Rest is created with datastruct constructor automatically
}

inline apstruct::apstruct (apstruct &d, size_t newsize, int newlocation, size_t padsize)
                          : datastruct (d, newsize, newlocation, padsize)
{
    nlinks = 1;
    sign = d.sign;
    exp = d.exp;
    prec = d.prec;

    // Rest is copied with datastruct copy constructor automatically
}

inline apstruct::~apstruct ()
{
    // Everything interesting is deleted with datastruct destructor
}

// Basic and advanced arithmetic functions

size_t rnd23up (size_t x);
size_t lastzeros (apstruct *s, size_t len = (size_t) DEFAULT);
apstruct *apaddsub (apstruct *a, apstruct *b, int sub);
apstruct *apmul (apstruct *a, apstruct *b);
apstruct *apmulmedium (apstruct *a, apstruct *b);
apstruct *apmulshort (apstruct *a, apstruct *b);
apstruct *apdivshort (apstruct *a, apstruct *b);
int apcmp (apstruct *a, apstruct *b, int absolute = 0);
double ap2double (apstruct *a);
apstruct *apabsfloor (apstruct *a);
apstruct *apabsceil (apstruct *a);
size_t apeq (apstruct *a, apstruct *b);
apstruct *apswapfrom (const char *filename);
void apswapto (apstruct *a, const char *filename);


// The apfloat class
// Includes only a pointer to an apstruct
class apfloat
{
public:
    // Constructors
    apfloat ();
    apfloat (int value, size_t prec = INFINITE, int location = DEFAULT);
    apfloat (unsigned value, size_t prec = INFINITE, int location = DEFAULT);
    apfloat (long value, size_t prec = INFINITE, int location = DEFAULT);
    apfloat (unsigned long value, size_t prec = INFINITE, int location = DEFAULT);
    apfloat (double value, size_t prec = (size_t) DEFAULT, int location = DEFAULT);
    apfloat (char *valuestring, size_t prec = (size_t) DEFAULT, int location = DEFAULT);
    apfloat (apstruct *d);
    apfloat (const apfloat &d);

    // Destructor
    ~apfloat ();

    // Operator functions
    friend apfloat operator+ (const apfloat &, const apfloat &);
    friend apfloat operator- (const apfloat &, const apfloat &);
    friend apfloat operator* (const apfloat &, const apfloat &);
    friend apfloat operator/ (const apfloat &, const apfloat &);
    friend bool operator== (const apfloat &, const apfloat &);
    friend bool operator!= (const apfloat &, const apfloat &);
    friend bool operator>= (const apfloat &, const apfloat &);
    friend bool operator<= (const apfloat &, const apfloat &);
    friend bool operator> (const apfloat &, const apfloat &);
    friend bool operator< (const apfloat &, const apfloat &);
    friend std::ostream &operator<< (std::ostream &, const apfloat &);
    friend std::istream &operator>> (std::istream &, apfloat &);
    apfloat &operator++ ();
    apfloat &operator-- ();
    apfloat operator++ (int);
    apfloat operator-- (int);
    apfloat &operator+= (const apfloat &d) { *this = *this + d; return *this; }
    apfloat &operator-= (const apfloat &d) { *this = *this - d; return *this; }
    apfloat &operator*= (const apfloat &d) { *this = *this * d; return *this; }
    apfloat &operator/= (const apfloat &d) { *this = *this / d; return *this; }
    apfloat &operator= (const apfloat &);
    apfloat operator+ () const;
    apfloat operator- () const;

    // Type-converted functions, some compilers can't do these automatically
    friend apfloat operator+ (const apfloat &d1, int d2) { return d1 + apfloat (d2); }
    friend apfloat operator+ (const apfloat &d1, unsigned d2) { return d1 + apfloat (d2); }
    friend apfloat operator+ (const apfloat &d1, long d2) { return d1 + apfloat (d2); }
    friend apfloat operator+ (const apfloat &d1, unsigned long d2) { return d1 + apfloat (d2); }
    friend apfloat operator+ (const apfloat &d1, double d2) { return d1 + apfloat (d2); }
    friend apfloat operator+ (const apfloat &d1, char *d2) { return d1 + apfloat (d2); }
    friend apfloat operator+ (int d1, const apfloat &d2) { return apfloat (d1) + d2; }
    friend apfloat operator+ (unsigned d1, const apfloat &d2) { return apfloat (d1) + d2; }
    friend apfloat operator+ (long d1, const apfloat &d2) { return apfloat (d1) + d2; }
    friend apfloat operator+ (unsigned long d1, const apfloat &d2) { return apfloat (d1) + d2; }
    friend apfloat operator+ (double d1, const apfloat &d2) { return apfloat (d1) + d2; }
    friend apfloat operator+ (char *d1, const apfloat &d2) { return apfloat (d1) + d2; }
    friend apfloat operator- (const apfloat &d1, int d2) { return d1 - apfloat (d2); }
    friend apfloat operator- (const apfloat &d1, unsigned d2) { return d1 - apfloat (d2); }
    friend apfloat operator- (const apfloat &d1, long d2) { return d1 - apfloat (d2); }
    friend apfloat operator- (const apfloat &d1, unsigned long d2) { return d1 - apfloat (d2); }
    friend apfloat operator- (const apfloat &d1, double d2) { return d1 - apfloat (d2); }
    friend apfloat operator- (const apfloat &d1, char *d2) { return d1 - apfloat (d2); }
    friend apfloat operator- (int d1, const apfloat &d2) { return apfloat (d1) - d2; }
    friend apfloat operator- (unsigned d1, const apfloat &d2) { return apfloat (d1) - d2; }
    friend apfloat operator- (long d1, const apfloat &d2) { return apfloat (d1) - d2; }
    friend apfloat operator- (unsigned long d1, const apfloat &d2) { return apfloat (d1) - d2; }
    friend apfloat operator- (double d1, const apfloat &d2) { return apfloat (d1) - d2; }
    friend apfloat operator- (char *d1, const apfloat &d2) { return apfloat (d1) - d2; }
    friend apfloat operator* (const apfloat &d1, int d2) { return d1 * apfloat (d2); }
    friend apfloat operator* (const apfloat &d1, unsigned d2) { return d1 * apfloat (d2); }
    friend apfloat operator* (const apfloat &d1, long d2) { return d1 * apfloat (d2); }
    friend apfloat operator* (const apfloat &d1, unsigned long d2) { return d1 * apfloat (d2); }
    friend apfloat operator* (const apfloat &d1, double d2) { return d1 * apfloat (d2); }
    friend apfloat operator* (const apfloat &d1, char *d2) { return d1 * apfloat (d2); }
    friend apfloat operator* (int d1, const apfloat &d2) { return apfloat (d1) * d2; }
    friend apfloat operator* (unsigned d1, const apfloat &d2) { return apfloat (d1) * d2; }
    friend apfloat operator* (long d1, const apfloat &d2) { return apfloat (d1) * d2; }
    friend apfloat operator* (unsigned long d1, const apfloat &d2) { return apfloat (d1) * d2; }
    friend apfloat operator* (double d1, const apfloat &d2) { return apfloat (d1) * d2; }
    friend apfloat operator* (char *d1, const apfloat &d2) { return apfloat (d1) * d2; }
    friend apfloat operator/ (const apfloat &d1, int d2) { return d1 / apfloat (d2); }
    friend apfloat operator/ (const apfloat &d1, unsigned d2) { return d1 / apfloat (d2); }
    friend apfloat operator/ (const apfloat &d1, long d2) { return d1 / apfloat (d2); }
    friend apfloat operator/ (const apfloat &d1, unsigned long d2) { return d1 / apfloat (d2); }
    friend apfloat operator/ (const apfloat &d1, double d2) { return d1 / apfloat (d2); }
    friend apfloat operator/ (const apfloat &d1, char *d2) { return d1 / apfloat (d2); }
    friend apfloat operator/ (int d1, const apfloat &d2) { return apfloat (d1) / d2; }
    friend apfloat operator/ (unsigned d1, const apfloat &d2) { return apfloat (d1) / d2; }
    friend apfloat operator/ (long d1, const apfloat &d2) { return apfloat (d1) / d2; }
    friend apfloat operator/ (unsigned long d1, const apfloat &d2) { return apfloat (d1) / d2; }
    friend apfloat operator/ (double d1, const apfloat &d2) { return apfloat (d1) / d2; }
    friend apfloat operator/ (char *d1, const apfloat &d2) { return apfloat (d1) / d2; }
    friend bool operator== (const apfloat &d1, int d2) { return d1 == apfloat (d2); }
    friend bool operator== (const apfloat &d1, unsigned d2) { return d1 == apfloat (d2); }
    friend bool operator== (const apfloat &d1, long d2) { return d1 == apfloat (d2); }
    friend bool operator== (const apfloat &d1, unsigned long d2) { return d1 == apfloat (d2); }
    friend bool operator== (const apfloat &d1, double d2) { return d1 == apfloat (d2); }
    friend bool operator== (const apfloat &d1, char *d2) { return d1 == apfloat (d2); }
    friend bool operator== (int d1, const apfloat &d2) { return apfloat (d1) == d2; }
    friend bool operator== (unsigned d1, const apfloat &d2) { return apfloat (d1) == d2; }
    friend bool operator== (long d1, const apfloat &d2) { return apfloat (d1) == d2; }
    friend bool operator== (unsigned long d1, const apfloat &d2) { return apfloat (d1) == d2; }
    friend bool operator== (double d1, const apfloat &d2) { return apfloat (d1) == d2; }
    friend bool operator== (char *d1, const apfloat &d2) { return apfloat (d1) == d2; }
    friend bool operator!= (const apfloat &d1, int d2) { return d1 != apfloat (d2); }
    friend bool operator!= (const apfloat &d1, unsigned d2) { return d1 != apfloat (d2); }
    friend bool operator!= (const apfloat &d1, long d2) { return d1 != apfloat (d2); }
    friend bool operator!= (const apfloat &d1, unsigned long d2) { return d1 != apfloat (d2); }
    friend bool operator!= (const apfloat &d1, double d2) { return d1 != apfloat (d2); }
    friend bool operator!= (const apfloat &d1, char *d2) { return d1 != apfloat (d2); }
    friend bool operator!= (int d1, const apfloat &d2) { return apfloat (d1) != d2; }
    friend bool operator!= (unsigned d1, const apfloat &d2) { return apfloat (d1) != d2; }
    friend bool operator!= (long d1, const apfloat &d2) { return apfloat (d1) != d2; }
    friend bool operator!= (unsigned long d1, const apfloat &d2) { return apfloat (d1) != d2; }
    friend bool operator!= (double d1, const apfloat &d2) { return apfloat (d1) != d2; }
    friend bool operator!= (char *d1, const apfloat &d2) { return apfloat (d1) != d2; }
    friend bool operator>= (const apfloat &d1, int d2) { return d1 >= apfloat (d2); }
    friend bool operator>= (const apfloat &d1, unsigned d2) { return d1 >= apfloat (d2); }
    friend bool operator>= (const apfloat &d1, long d2) { return d1 >= apfloat (d2); }
    friend bool operator>= (const apfloat &d1, unsigned long d2) { return d1 >= apfloat (d2); }
    friend bool operator>= (const apfloat &d1, double d2) { return d1 >= apfloat (d2); }
    friend bool operator>= (const apfloat &d1, char *d2) { return d1 >= apfloat (d2); }
    friend bool operator>= (int d1, const apfloat &d2) { return apfloat (d1) >= d2; }
    friend bool operator>= (unsigned d1, const apfloat &d2) { return apfloat (d1) >= d2; }
    friend bool operator>= (long d1, const apfloat &d2) { return apfloat (d1) >= d2; }
    friend bool operator>= (unsigned long d1, const apfloat &d2) { return apfloat (d1) >= d2; }
    friend bool operator>= (double d1, const apfloat &d2) { return apfloat (d1) >= d2; }
    friend bool operator>= (char *d1, const apfloat &d2) { return apfloat (d1) >= d2; }
    friend bool operator<= (const apfloat &d1, int d2) { return d1 <= apfloat (d2); }
    friend bool operator<= (const apfloat &d1, unsigned d2) { return d1 <= apfloat (d2); }
    friend bool operator<= (const apfloat &d1, long d2) { return d1 <= apfloat (d2); }
    friend bool operator<= (const apfloat &d1, unsigned long d2) { return d1 <= apfloat (d2); }
    friend bool operator<= (const apfloat &d1, double d2) { return d1 <= apfloat (d2); }
    friend bool operator<= (const apfloat &d1, char *d2) { return d1 <= apfloat (d2); }
    friend bool operator<= (int d1, const apfloat &d2) { return apfloat (d1) <= d2; }
    friend bool operator<= (unsigned d1, const apfloat &d2) { return apfloat (d1) <= d2; }
    friend bool operator<= (long d1, const apfloat &d2) { return apfloat (d1) <= d2; }
    friend bool operator<= (unsigned long d1, const apfloat &d2) { return apfloat (d1) <= d2; }
    friend bool operator<= (double d1, const apfloat &d2) { return apfloat (d1) <= d2; }
    friend bool operator<= (char *d1, const apfloat &d2) { return apfloat (d1) <= d2; }
    friend bool operator> (const apfloat &d1, int d2) { return d1 > apfloat (d2); }
    friend bool operator> (const apfloat &d1, unsigned d2) { return d1 > apfloat (d2); }
    friend bool operator> (const apfloat &d1, long d2) { return d1 > apfloat (d2); }
    friend bool operator> (const apfloat &d1, unsigned long d2) { return d1 > apfloat (d2); }
    friend bool operator> (const apfloat &d1, double d2) { return d1 > apfloat (d2); }
    friend bool operator> (const apfloat &d1, char *d2) { return d1 > apfloat (d2); }
    friend bool operator> (int d1, const apfloat &d2) { return apfloat (d1) > d2; }
    friend bool operator> (unsigned d1, const apfloat &d2) { return apfloat (d1) > d2; }
    friend bool operator> (long d1, const apfloat &d2) { return apfloat (d1) > d2; }
    friend bool operator> (unsigned long d1, const apfloat &d2) { return apfloat (d1) > d2; }
    friend bool operator> (double d1, const apfloat &d2) { return apfloat (d1) > d2; }
    friend bool operator> (char *d1, const apfloat &d2) { return apfloat (d1) > d2; }
    friend bool operator< (const apfloat &d1, int d2) { return d1 < apfloat (d2); }
    friend bool operator< (const apfloat &d1, unsigned d2) { return d1 < apfloat (d2); }
    friend bool operator< (const apfloat &d1, long d2) { return d1 < apfloat (d2); }
    friend bool operator< (const apfloat &d1, unsigned long d2) { return d1 < apfloat (d2); }
    friend bool operator< (const apfloat &d1, double d2) { return d1 < apfloat (d2); }
    friend bool operator< (const apfloat &d1, char *d2) { return d1 < apfloat (d2); }
    friend bool operator< (int d1, const apfloat &d2) { return apfloat (d1) < d2; }
    friend bool operator< (unsigned d1, const apfloat &d2) { return apfloat (d1) < d2; }
    friend bool operator< (long d1, const apfloat &d2) { return apfloat (d1) < d2; }
    friend bool operator< (unsigned long d1, const apfloat &d2) { return apfloat (d1) < d2; }
    friend bool operator< (double d1, const apfloat &d2) { return apfloat (d1) < d2; }
    friend bool operator< (char *d1, const apfloat &d2) { return apfloat (d1) < d2; }
    apfloat &operator+= (int d) { *this = *this + apfloat (d); return *this; }
    apfloat &operator+= (unsigned d) { *this = *this + apfloat (d); return *this; }
    apfloat &operator+= (long d) { *this = *this + apfloat (d); return *this; }
    apfloat &operator+= (unsigned long d) { *this = *this + apfloat (d); return *this; }
    apfloat &operator+= (double d) { *this = *this + apfloat (d); return *this; }
    apfloat &operator+= (char *d) { *this = *this + apfloat (d); return *this; }
    apfloat &operator-= (int d) { *this = *this - apfloat (d); return *this; }
    apfloat &operator-= (unsigned d) { *this = *this - apfloat (d); return *this; }
    apfloat &operator-= (long d) { *this = *this - apfloat (d); return *this; }
    apfloat &operator-= (unsigned long d) { *this = *this - apfloat (d); return *this; }
    apfloat &operator-= (double d) { *this = *this - apfloat (d); return *this; }
    apfloat &operator-= (char *d) { *this = *this - apfloat (d); return *this; }
    apfloat &operator*= (int d) { *this = *this * apfloat (d); return *this; }
    apfloat &operator*= (unsigned d) { *this = *this * apfloat (d); return *this; }
    apfloat &operator*= (long d) { *this = *this * apfloat (d); return *this; }
    apfloat &operator*= (unsigned long d) { *this = *this * apfloat (d); return *this; }
    apfloat &operator*= (double d) { *this = *this * apfloat (d); return *this; }
    apfloat &operator*= (char *d) { *this = *this * apfloat (d); return *this; }
    apfloat &operator/= (int d) { *this = *this / apfloat (d); return *this; }
    apfloat &operator/= (unsigned d) { *this = *this / apfloat (d); return *this; }
    apfloat &operator/= (long d) { *this = *this / apfloat (d); return *this; }
    apfloat &operator/= (unsigned long d) { *this = *this / apfloat (d); return *this; }
    apfloat &operator/= (double d) { *this = *this / apfloat (d); return *this; }
    apfloat &operator/= (char *d) { *this = *this / apfloat (d); return *this; }
    apfloat &operator= (int d) { *this = apfloat (d); return *this; }
    apfloat &operator= (unsigned d) { *this = apfloat (d); return *this; }
    apfloat &operator= (long d) { *this = apfloat (d); return *this; }
    apfloat &operator= (unsigned long d) { *this = apfloat (d); return *this; }
    apfloat &operator= (double d) { *this = apfloat (d); return *this; }
    apfloat &operator= (char *d) { *this = apfloat (d); return *this; }

    // Other functions
    int sign (void) const;
    void sign (int newsign);
    long exp (void) const;
    void exp (long newexp);
    size_t prec (void) const;
    void prec (size_t newprec);
    int location (void) const;
    void location (int newlocation);
    void unique (void);
    void swapfrom (const char *filename);
    void swapto (const char *filename);

    // Commont to all apfloats
    static bool prettyprint;

    // Implementation
    apstruct *ap;
};


inline apfloat::apfloat ()
{
    ap = 0;
}


inline apfloat::apfloat (apstruct *d)
{
    ap = d;
}


// Overloaded mathematical functions

apfloat pow (apfloat base, unsigned long exp);
apfloat pow (apfloat base, unsigned exp);
apfloat pow (apfloat base, long exp);
apfloat pow (apfloat base, int exp);
apfloat sqrt (apfloat x);
apfloat cbrt (apfloat x);
apfloat root (apfloat x, unsigned n);
apfloat invroot (apfloat u, unsigned n, size_t destprec = (size_t) DEFAULT, apfloat initguess = apfloat (), size_t initprec = (size_t) DEFAULT);
apfloat floor (apfloat x);
apfloat ceil (apfloat x);
apfloat abs (apfloat x);
apfloat modf (apfloat x, apfloat *ipart);
apfloat fmod (apfloat x, apfloat y);
apfloat pi (size_t destprec, apfloat *LT = 0, apfloat *LQ = 0, apfloat *LP = 0, apfloat *iroot = 0, size_t *terms = 0);
apfloat agm (apfloat a, apfloat b);
void checkpi (size_t destprec);
void checklogconst (size_t destprec);
apfloat rawlog (apfloat x);
apfloat log (apfloat x);
apfloat exp (apfloat u);
apfloat pow (apfloat x, apfloat y);
apfloat acosh (apfloat x);
apfloat asinh (apfloat x);
apfloat atanh (apfloat x);
apfloat cosh (apfloat x);
apfloat sinh (apfloat x);
apfloat tanh (apfloat x);

// More trigonometric functions are defined in apcplx.h

// Constants needed for log & exp
extern apfloat Readypi;
extern apfloat Logbase;


// Functions in apfloat.cpp

std::ostream &pretty (std::ostream &str);


#endif  // __APFLOAT_H
