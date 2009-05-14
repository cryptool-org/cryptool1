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

