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
 * the finite field mod p
 *
 * WARNING: This class has been cobbled together for a specific use with
 * the MIRACL library. It is not complete, and may not work in other 
 * applications
 *
 * See Knuth The Art of Computer Programming Vol.2, Chapter 4.6 
 */

#ifndef POLY_H
#define POLY_H

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif
#include "monty.h"

#define FFT_BREAK_EVEN 16

class term
{
public:
    ZZn an;
    int n;
    term *next;
};
  
class Poly
{
public:
    term *start;
    Poly() {start=NULL;}
    Poly(const Poly&);
    void clear();
    term *addterm(const ZZn&,int,term *pos=NULL);
    void multerm(const ZZn&,int);
    ZZn F(const ZZn&) const;
    ZZn coeff(int) const;
    ZZn min() const;

    Poly& operator=(const Poly&);
    Poly& operator=(int);
    Poly& operator+=(const Poly&);
    Poly& operator-=(const Poly&);
    Poly& operator+=(const ZZn& m) {addterm(m,0);    return *this; } 
    Poly& operator-=(const ZZn& m) {addterm((-m),0); return *this; }
    Poly& operator%=(const Poly&);
    Poly& operator*=(const ZZn&);
    Poly& operator/=(const ZZn&);

    friend BOOL iszero(const Poly&);
    friend BOOL isone(const Poly&);
    friend Poly divxn(const Poly&,int);
    friend Poly mulxn(const Poly&,int);
    friend Poly modxn(const Poly&,int);    
    friend Poly invmodxn(const Poly&,int);
    friend Poly reverse(const Poly&);
    friend int degree(const Poly&);
    friend Poly compose(const Poly&,const Poly&,const Poly&);
    friend Poly operator*(const Poly&,const Poly&);
    friend Poly operator%(const Poly&,const Poly&);
    friend Poly operator/(const Poly&,const Poly&);
    friend Poly operator-(const Poly&,const Poly&);
    friend Poly operator+(const Poly&,const Poly&);
    friend Poly operator-(const Poly&,const ZZn&);
    friend Poly operator+(const Poly&,const ZZn&);
    friend Poly operator*(const Poly&,const ZZn&);
    friend Poly operator*(const ZZn&,const Poly&);
    
    friend Poly operator/(const Poly&,const ZZn&);

    friend Poly gcd(const Poly&,const Poly&);
    friend Poly pow(const Poly&,const Big&,const Poly&);
    friend Poly pow(const Poly&,int);

    friend Poly factor(const Poly&,int);
    friend ostream& operator<<(ostream&,const Poly&);
    ~Poly();
};

#endif

