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

