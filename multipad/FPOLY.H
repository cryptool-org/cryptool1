/*
 * C++ class to implement a polynomial type and to allow 
 * arithmetic on polynomials whose elements are flash numbers
 *
 * WARNING: This class has been cobbled together for a specific use with
 * the MIRACL library. It is not complete, and may not work in other 
 * applications
 *
 * See Knuth The Art of Computer Programming Vol.2, Chapter 4.6 
 */

#ifndef FPOLY_H
#define FPOLY_H

#include "flash.h"

class fterm
{
public:
    Flash an;
    int n;
    fterm *next;
};
  
class FPoly
{
    fterm *start;
public:
    FPoly() {start=NULL;}
    FPoly(const FPoly&);
    void clear();
    fterm* addterm(Flash,int,fterm *pos=NULL);
    void multerm(Flash,int);
    Flash coeff(int);
    int getterms(Flash *,int *);
    FPoly& operator=(const FPoly&);
    FPoly& operator+=(const FPoly&);
    FPoly& operator-=(const FPoly&);
    friend int degree(const FPoly&);
    friend FPoly operator*(const FPoly&,const FPoly&);
    friend ostream& operator<<(ostream&,const FPoly&);
    ~FPoly();
};


#endif

