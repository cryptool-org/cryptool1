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
 *    MIRACL  C++ Header file elliptic.h
 *
 *    AUTHOR  : M. Scott
 *  
 *    PURPOSE : Definition of class ECn  (Arithmetic on an Elliptic Curve,
 *               mod n)
 *
 *    NOTE    : Must be used in conjunction with elliptic.cpp and big.cpp
 *              The active curve is set dynamically (via the Big ecurve() 
 *              routine) - so beware the pitfalls implicit in declaring
 *              static or global ECn's (which are initialised before the 
 *              curve is set!). Uninitialised data is OK 
 *
 *    Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#ifndef ELLIPTIC_H
#define ELLIPTIC_H

#include "big.h"

class ECn
{
    epoint *p;
public:
    ECn()                         { p=epoint_init();}
   
    ECn(const Big &x,const Big& y)  {p=epoint_init(); 
                                   epoint_set(x.getbig(),y.getbig(),0,p); }
    
  // This next constructor restores a point on the curve from "compressed" 
  // data, that is the full x co-ordinate, and the LSB of y  (0 or 1)

    ECn(const Big& x,int cb)             {p=epoint_init();
                                   epoint_set(x.getbig(),x.getbig(),cb,p); }
                   
    ECn(const ECn &b)                   {p=epoint_init(); epoint_copy(b.p,p);}

    epoint *get_point() const;
    
    ECn& operator=(const ECn& b)  {epoint_copy(b.p,p);return *this;}

    ECn& operator+=(const ECn& b) {ecurve_add(b.p,p); return *this;}
    ECn& operator-=(const ECn& b) {ecurve_sub(b.p,p); return *this;}

  // Multiplication of a point by an integer. 

    ECn& operator*=(const Big& k) {ecurve_mult(k.getbig(),p,p); return *this;}

    void clear() {epoint_set(NULL,NULL,0,p);}
    BOOL set(const Big& x,const Big& y)    {return epoint_set(x.getbig(),y.getbig(),0,p);}
    BOOL iszero() const;
    int get(Big& x,Big& y) const;

  // This gets the point in compressed form. Return value is LSB of y-coordinate
    int get(Big& x) const;

  // point compression

  // This sets the point from compressed form. cb is LSB of y coordinate 

    BOOL set(const Big& x,int cb=0)  {return epoint_set(x.getbig(),x.getbig(),cb,p);}

    friend ECn operator-(const ECn&);
    friend void multi_add(int,ECn *,ECn *);
  
    friend ECn mul(const Big&, const ECn&, const Big&, const ECn&);
    friend ECn mul(int, const Big *, ECn *);
  
    friend void normalise(ECn &e) {epoint_norm(e.p);}

    friend BOOL operator==(const ECn& a,const ECn& b)
                                  {return epoint_comp(a.p,b.p);}    
    friend BOOL operator!=(const ECn& a,const ECn& b)
                                  {return (!epoint_comp(a.p,b.p));}    

    friend ECn operator*(const Big &,const ECn&);
    friend ostream& operator<<(ostream&,const ECn&);

    ~ECn() {epoint_free(p); }

};

#endif

