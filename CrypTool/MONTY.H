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

