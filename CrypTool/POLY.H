/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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

