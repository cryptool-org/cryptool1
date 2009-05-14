/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

/*
 * C++ class to implement a polynomial type and to allow 
 * arithmetic on polynomials whose elements are from
 * the finite field mod p. 
 *
 * WARNING: This class has been cobbled together for a specific use with
 * the MIRACL library. It is not complete, and may not work in other 
 * applications
 *
 * This type is automatically reduced
 * wrt a polynomial modulus.
 *
 * See Knuth The Art of Computer Programming Vol.2, Chapter 4.6 
 */

#ifndef POLYMOD_H
#define POLYMOD_H

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif
#include "poly.h"

extern Poly modulus;

class PolyMod
{
public:
    Poly p;

    PolyMod() { }
    PolyMod(const Poly& m)     {p=m%modulus; }
    PolyMod(const PolyMod& m)  {p=m.p; }
    void clear()               {p.clear();}
    term* addterm(const ZZn& z,int i,term *pos=NULL) {return p.addterm(z,i,pos);}
    void multerm(const ZZn& z,int i) {p.multerm(z,i);}
    ZZn F(const ZZn& z)        {return p.F(z); }
    ZZn coeff(int i) const;
    PolyMod& operator=(int m)               {p=m; return *this;}
    PolyMod& operator=(const PolyMod& m)    {p=m.p; return *this;}
    PolyMod& operator=(const Poly& m)       {reduce(m,*this); return *this;}
    PolyMod& operator+=(const PolyMod& m)   {p=(p+m.p)%modulus;return *this;}
    PolyMod& operator-=(const PolyMod& m)   {p=(p-m.p)%modulus;return *this;}
    PolyMod& operator+=(const ZZn& m)       {addterm(m,0); return *this;}
    PolyMod& operator-=(const ZZn& m)       {addterm((-m),0); return *this;}
    PolyMod& operator*=(const ZZn& z)       {p*=z;return *this;}
    PolyMod& operator/=(const ZZn& z)       {p/=z;return *this;}
    PolyMod& operator*=(const PolyMod&);
    
    friend void setmod(const Poly&);
    friend void reduce(const Poly&,PolyMod&);

    friend BOOL iszero(const PolyMod&);     
    friend BOOL isone(const PolyMod&); 
    friend int degree(const PolyMod&); 

    friend PolyMod operator*(const PolyMod&,const PolyMod&); 
    friend PolyMod operator-(const PolyMod&,const PolyMod&);
    friend PolyMod operator+(const PolyMod&,const PolyMod&);
    friend PolyMod operator-(const PolyMod&,const ZZn&);
    friend PolyMod operator+(const PolyMod&,const ZZn&);

    friend PolyMod operator*(const PolyMod&,const ZZn&);
    friend PolyMod operator*(const ZZn&,const PolyMod&);
    friend PolyMod compose(const PolyMod&,const PolyMod&);    

    friend PolyMod operator/(const PolyMod&,const ZZn&);
    friend Poly gcd(const PolyMod&);
    friend PolyMod pow(const PolyMod&,const Big&);
    friend ostream& operator<<(ostream& ,const PolyMod&);
    ~PolyMod() {}
};

#endif

