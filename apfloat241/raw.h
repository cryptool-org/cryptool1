#if !defined(__RAW_H)
#define __RAW_H


// The modint raw data type, unsigned if possible
typedef unsigned rawtype;


const rawtype MAXMODULUS = 0x7FFFFFFF;
const rawtype MAXRAW = 0xFFFFFFFF;
const int RAWBITS = 32;

// Base (must be BASEDIGIT^BASEDIGITS = BASE < all MODULI)
const rawtype BASE = 1000000000;
const rawtype BASEDIGIT = 10;
const int BASEDIGITS = 9;
const rawtype BASEFACTORS[] = {2, 5};           // All prime factors of BASE
const int NBASEFACTORS = 2;                     // Number of prime factors of BASE

const rawtype MODULI[3] = {2113929217, 2013265921, 1811939329};     // upto n = 2^25
const rawtype PRIMITIVEROOTS[3] = {5, 31, 13};
const rawtype WFTAMODULI[3] = {1955923201, 1676505601, 1549497601}; // upto n = 5040^2
const rawtype WFTAPRIMITIVEROOTS[3] = {29, 31, 17};

const size_t MAXTRANSFORMLENGTH = 50331648;         // Maximum transform length for these moduli


// Low-level inline functions

// General GCC

inline rawtype modmul (rawtype a, rawtype b, rawtype m)
{
    return (unsigned long long) a * b % m;
}

inline rawtype modadd (rawtype a, rawtype b, rawtype m)
{
    rawtype r;

    r = a + b;
    return (r >= m ? r - m : r);
}

inline rawtype modsub (rawtype a, rawtype b, rawtype m)
{
    int r;

    r = a - b;
    return (r < 0 ? r + m : r);
}


#endif  // __RAW_H
