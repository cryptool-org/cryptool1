#ifndef __cplusplus
#error Must use C++ for the type modint.
#endif


#if !defined(__MODINT_H)
#define __MODINT_H


#include <iomanip>
#include <cstdlib>


// Low-level inline functions here

#include "raw.h"


// Must be re-declared here
extern rawtype *workspace;
extern int workspaceused;


// Integers modulo a prime class definiton

class modint
{
public:
    // Constructors
    modint (rawtype value);
    modint ();

    // Binary operator functions
    friend modint operator+ (modint, modint);
    friend modint operator+ (rawtype, modint);
    friend modint operator+ (modint, rawtype);
    friend modint operator- (modint, modint);
    friend modint operator- (rawtype, modint);
    friend modint operator- (modint, rawtype);
    friend modint operator* (modint, modint);
    friend modint operator* (rawtype, modint);
    friend modint operator* (modint, rawtype);
    friend modint operator/ (modint, modint);
    friend modint operator/ (rawtype, modint);
    friend modint operator/ (modint, rawtype);
    friend bool operator== (modint, modint);
    friend bool operator== (rawtype, modint);
    friend bool operator== (modint, rawtype);
    friend bool operator!= (modint, modint);
    friend bool operator!= (rawtype, modint);
    friend bool operator!= (modint, rawtype);
    friend std::ostream &operator<< (std::ostream &, modint);
    modint &operator++ ();
    modint &operator-- ();
    modint &operator+= (modint);
    modint &operator+= (rawtype);
    modint &operator-= (modint);
    modint &operator-= (rawtype);
    modint &operator*= (modint);
    modint &operator*= (rawtype);
    modint &operator/= (modint);
    modint &operator/= (rawtype);
    modint operator+ ();
    modint operator- ();

    // Allocation functions
    void *operator new[] (size_t size);
    void operator delete[] (void *data);

    // Type conversion
    operator rawtype ();

    // Commont to all modints
    static rawtype modulus;

    // Implementation
private:
    rawtype value;
};


// Inline functions

inline modint::modint (rawtype val)
{
    // value = (val >= modulus ? val - modulus : val);
    value = val;
}

inline modint::modint ()
{
    /* If you want your numbers initialized ...
    value = 0;
    */
}

inline modint modint::operator+ ()
{
    return *this;
}

inline modint modint::operator- ()
{
    return modint (value == 0 ? 0 : modulus - value);
}


// Overloaded mathematical functions

modint pow (modint base, rawtype exp);


// Definitions of compound-assignment operator member functions

inline modint &modint::operator++ ()
{
    if ((value += 1) == modulus) value = 0;
    return *this;
}

inline modint &modint::operator-- ()
{
    if (value == 0) value = modulus;
    value -= 1;
    return *this;
}

inline modint &modint::operator+= (modint add)
{
    value = modadd (value, add.value, modulus);
    return *this;
}

inline modint &modint::operator+= (rawtype add)
{
    value = modadd (value, add, modulus);
    return *this;
}

inline modint &modint::operator-= (modint sub)
{
    value = modsub (value, sub.value, modulus);
    return *this;
}

inline modint &modint::operator-= (rawtype sub)
{
    value = modsub (value, sub, modulus);
    return *this;
}

inline modint &modint::operator*= (modint mul)
{
    value = modmul (value, mul.value, modulus);
    return *this;
}

inline modint &modint::operator*= (rawtype mul)
{
    value = modmul (value, mul, modulus);
    return *this;
}

inline modint &modint::operator/= (modint div)
{
    value = modmul (value, pow (div, modulus - 2).value, modulus);
    return *this;
}

inline modint &modint::operator/= (rawtype div)
{
    value = modmul (value, pow (modint (div), modulus - 2).value, modulus);
    return *this;
}


// Definitions of non-member binary operator functions

inline modint operator+ (modint m1, modint m2)
{
    return modint (modadd (m1.value, m2.value, modint::modulus));
}

inline modint operator+ (rawtype m1, modint m2)
{
    return modint (modadd (m1, m2.value, modint::modulus));
}

inline modint operator+ (modint m1, rawtype m2)
{
    return modint (modadd (m1.value, m2, modint::modulus));
}

inline modint operator- (modint m1, modint m2)
{
    return modint (modsub (m1.value, m2.value, modint::modulus));
}

inline modint operator- (rawtype m1, modint m2)
{
    return modint (modsub (m1, m2.value, modint::modulus));
}

inline modint operator- (modint m1, rawtype m2)
{
    return modint (modsub (m1.value, m2, modint::modulus));
}

inline modint operator* (modint m1, modint m2)
{
    return modint (modmul (m1.value, m2.value, modint::modulus));
}

inline modint operator* (rawtype m1, modint m2)
{
    return modint (modmul (m1, m2.value, modint::modulus));
}

inline modint operator* (modint m1, rawtype m2)
{
    return modint (modmul (m1.value, m2, modint::modulus));
}

inline modint operator/ (modint m1, modint m2)
{
    return modint (modmul (m1.value, pow (m2, modint::modulus - 2).value, modint::modulus));
}

inline modint operator/ (rawtype m1, modint m2)
{
    return modint (modmul (m1, pow (m2, modint::modulus - 2).value, modint::modulus));
}

inline modint operator/ (modint m1, rawtype m2)
{
    return modint (modmul (m1.value, pow (modint (m2), modint::modulus - 2).value, modint::modulus));
}

inline bool operator== (modint m1, modint m2)
{
    return m1.value == m2.value;
}

inline bool operator== (rawtype m1, modint m2)
{
    return (m1 == m2.value);
}

inline bool operator== (modint m1, rawtype m2)
{
    return (m1.value == m2);
}

inline bool operator!= (modint m1, modint m2)
{
    return (m1.value != m2.value);
}

inline bool operator!= (rawtype m1, modint m2)
{
    return (m1 != m2.value);
}

inline bool operator!= (modint m1, rawtype m2)
{
    return (m1.value != m2);
}


// Definitions of allocation functions

inline void *modint::operator new[] (size_t size)
{
    size /= sizeof (modint);

    if (size > Memorytreshold)
    {
        assert (!workspaceused);
        assert (size <= Maxblocksize);
        workspaceused = 1;
        return (void *) workspace;
    }
    else
        return (void *) new rawtype[size];
}

inline void modint::operator delete[] (void *data)
{
    if (data == (void *) workspace)
    {
        assert (workspaceused);
        workspaceused = 0;
    }
    else
        delete[] (rawtype *) data;
}


// Definitions of type conversion functions

inline modint::operator rawtype ()
{
    return value;
}


// I/O functions

inline std::ostream &operator<< (std::ostream &str, modint m)
{
    str << std::setprecision (Basedigits + 1) << m.value;

    return str;
}


#endif  // __MODINT_H
