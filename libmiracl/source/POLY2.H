/*
 * C++ class to implement a polynomial type and to allow 
 * arithmetic on polynomials whose elements are from
 * the finite field 2^m
 *
 * WARNING: This class has been cobbled together for a specific use with
 * the MIRACL library. It is not complete, and may not work in other 
 * applications
 *
 * See Knuth The Art of Computer Programming Vol.2, Chapter 4.6 
 */

#ifndef POLY2_H
#define POLY2_H

#include <iostream.h>
#include <gf2m.h>

#define KARAT_BREAK_EVEN 8

class term2
{
public:
    GF2m an;
    int n;
    term2 *next;
};
  
class Poly2
{
public:
    term2 *start;
    Poly2() {start=NULL;}
    Poly2(const Poly2&);
    void clear();
    term2 *addterm(const GF2m&,int,term2 *pos=NULL);
    void multerm(const GF2m&,int);
    GF2m F(const GF2m&) const;
    GF2m coeff(int) const;
    GF2m min() const;

    Poly2& operator=(const Poly2&);
    Poly2& operator=(int);
    Poly2& operator+=(const Poly2&);
    Poly2& operator+=(const GF2m& m) {addterm(m,0); return *this; }
    Poly2& operator%=(const Poly2&);
    Poly2& operator*=(const GF2m&);
    Poly2& operator/=(const GF2m&);

    friend BOOL iszero(const Poly2&);
    friend BOOL isone(const Poly2&);
    friend Poly2 divxn(const Poly2&,int);
    friend Poly2 mulxn(const Poly2&,int);
    friend Poly2 modxn(const Poly2&,int);    
    friend Poly2 invmodxn(const Poly2&,int);
    friend Poly2 reverse(const Poly2&);
    friend int degree(const Poly2&);
    friend Poly2 operator*(const Poly2&,const Poly2&);
    friend Poly2 operator%(const Poly2&,const Poly2&);
    friend Poly2 operator/(const Poly2&,const Poly2&);
    friend Poly2 operator+(const Poly2&,const Poly2&);
    friend Poly2 operator+(const Poly2&,const GF2m&);

    friend Poly2 operator*(const Poly2&,const GF2m&);
    friend Poly2 operator*(const GF2m&,const Poly2&);
    
    friend Poly2 operator/(const Poly2&,const GF2m&);

    friend Poly2 fulldiv(Poly2&,const Poly2&);
    friend Poly2 gcd(const Poly2&,const Poly2&);
    friend Poly2 inverse(const Poly2&,const Poly2&);
    friend void  swap(Poly2 &,Poly2 &);

    friend Poly2 pow(const Poly2&,const Big&,const Poly2&);
    friend Poly2 pow(const Poly2&,int);

    friend ostream& operator<<(ostream&,const Poly2&);
    ~Poly2();
};

#endif

