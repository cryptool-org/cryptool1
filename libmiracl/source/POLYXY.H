/*
 * C++ class to implement a bivariate polynomial type and to allow 
 * arithmetic on polynomials whose coefficients are from
 * the finite field mod p
 *
 * WARNING: This class has been cobbled together for a specific use with
 * the MIRACL library. It is not complete, and may not work in other 
 * applications
 *
 * See Knuth The Art of Computer Programming Vol.2, Chapter 4.6 
 */

#ifndef POLYXY_H
#define POLYXY_H

#include <iostream.h>
#include <monty.h>
#include "poly.h"

class termXY
{
public:
    ZZn an;
    int nx;
    int ny;
    termXY *next;
};
  
class PolyXY
{
public:
    termXY *start;
    PolyXY() {start=NULL;}
    PolyXY(const PolyXY&);
    void clear();
    termXY *addterm(const ZZn&,int,int,termXY *pos=NULL);
    ZZn F(const ZZn&,const ZZn&);
    Poly F(const ZZn&);
    ZZn coeff(int,int);
    PolyXY& operator=(const PolyXY&);

    friend PolyXY diff_dx(const PolyXY&);
    friend PolyXY diff_dy(const PolyXY&);

    friend ostream& operator<<(ostream&,const PolyXY&);
    ~PolyXY();
};

#endif

