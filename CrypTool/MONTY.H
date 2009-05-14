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
 *    MIRACL  C++ Header file monty.h
 *
 *    AUTHOR  : M. Scott
 *  
 *    PURPOSE : Definition of class ZZn  (Arithmetic mod n), using 
 *              Montgomery's Method for modular multiplication
 *    NOTE    : Must be used in conjunction with big.cpp and monty.cpp
 *              The modulus n is always set dynamically (via the modulo() 
 *              routine) - so beware the pitfalls implicit in declaring
 *              static or global ZZn's (which are initialised before n is 
 *              set!). Uninitialised data is OK 
 *                
 *    Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#ifndef MONTY_H
#define MONTY_H

#include "big.h"

class ZZn 
{ 
    Big fn;
public:
    ZZn()       {  } 
    ZZn(int i)  { if (i==0) fn=0; else fn=nres((Big)i); }
    ZZn(long lg){ if (lg==0L) fn=0; else fn=nres((Big)lg); }
    ZZn(const Big& b) { fn=nres(b); }   /* Big -> ZZn */
    ZZn(big& b)        {copy(b,fn.getbig());}
    ZZn(const ZZn& b) { fn=b.fn; }
    ZZn(char* s){ fn=nres((Big)s); }

    ZZn& operator=(int i) {if (i==0) fn=0; else fn=nres((Big)i); return *this;}
    ZZn& operator=(long lg)
                      {if (lg==0L) fn=0; else fn=nres((Big)lg); return *this;}
    ZZn& operator=(const ZZn& b){fn=b.fn; return *this;}
    ZZn& operator=(char* s){fn=nres((Big)s); return *this;}

    ZZn& operator++() {fn=nres_modadd(fn,nres((Big)1));return *this;}
    ZZn& operator--() {fn=nres_modsub(fn,nres((Big)1));return *this;}
    ZZn& operator+=(int i) {fn=nres_modadd(fn,nres((Big)i));return *this;}
    ZZn& operator+=(const ZZn& b){fn=nres_modadd(fn,b.fn);return *this;}
    ZZn& operator-=(int i) {fn=nres_modsub(fn,nres((Big)i));return *this;}
    ZZn& operator-=(const ZZn& b){fn=nres_modsub(fn,b.fn);return *this;}
    ZZn& operator*=(const ZZn& b) {fn=nres_modmult(fn,b.fn);return *this;}
    ZZn& operator*=(int i) {fn=nres_premult(fn,i);return *this;}

    BOOL iszero() const;
    operator Big() {return redc(fn);}   /* ZZn -> Big */
    friend big getbig(ZZn& z) {return z.fn.getbig();}

    ZZn& operator/=(const ZZn& b) {fn=nres_moddiv(fn,b.fn); return *this;}
    ZZn& operator/=(int i) {fn=nres_moddiv(fn,nres((Big)i));return *this;}

    friend ZZn operator-(const ZZn&);

    friend ZZn operator+(const ZZn&,int);
    friend ZZn operator+(int, const ZZn&);
    friend ZZn operator+(const ZZn&, const ZZn&);

    friend ZZn operator-(const ZZn&, int);
    friend ZZn operator-(int, const ZZn&);
    friend ZZn operator-(const ZZn&, const ZZn&);

    friend ZZn operator*(const ZZn&, int);
    friend ZZn operator*(int, const ZZn&);
    friend ZZn operator*(const ZZn&, const ZZn&);

    friend ZZn operator/(const ZZn&, int);
    friend ZZn operator/(int, const ZZn&);
    friend ZZn operator/(const ZZn&, const ZZn&);

    friend BOOL operator==(const ZZn& b1,const ZZn& b2)
    { if (b1.fn==b2.fn) return TRUE; else return FALSE;}
/* Roger Löschung */
    friend BOOL operator!=(const ZZn& b1,const ZZn& b2)
    { if (b1.fn!=b2.fn) return TRUE; else return FALSE;}
/**/
    friend ZZn  pow( const ZZn&, const Big&);
    friend ZZn  pow( const ZZn&,int);
    friend ZZn  pow( const ZZn&, const Big&, const ZZn&, const Big&);
    friend ZZn  pow( int,ZZn *,Big *);    

    friend ZZn  sqrt(const ZZn&);          // only works if modulus is prime
    friend ZZn  luc( const ZZn&, const Big&, ZZn* b3=NULL);
    ~ZZn() { }
};

#endif

