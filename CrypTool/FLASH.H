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
 *    MIRACL  C++ Header file flash.h
 *
 *    AUTHOR  :    N.Coghlan
 *                 Modified by M.Scott
 *             
 *    PURPOSE :    Definition of class Flash
 *
 *    Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#ifndef FLASH_H
#define FLASH_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "big.h"

extern "C"    
{
    #include <miracl.h>
}

#ifdef MR_FLASH

#ifndef MIRACL_CLASS
#define MIRACL_CLASS

class Miracl
{ /* dummy class to initialise MIRACL - MUST be called before any Bigs    *
   * are created. This could be a problem for static/global data declared *
   * in modules other than the main module */
    miracl *mr;
public:
    Miracl(int nd,mr_small nb=0) {mr=mirsys(nd,nb);mr->RPOINT=TRUE;}
    miracl *operator&()          {return mr;}
    ~Miracl()                    {mirexit();}
};

#endif

class Flash
{ /* Flash Class Definitions */
    flash fn;      /* pointer to actual data */
public:
    Flash()         {fn=mirvar(0);}
    Flash(int i)    {fn=mirvar(i);}
    Flash(int x,int y) {fn=mirvar(0); fconv(x,y,fn); }
    Flash(long lg)  {fn=mirvar(0);   lgconv(lg,fn);}
    Flash(double d) {fn=mirvar(0);    dconv(d,fn);}
    Flash(const Flash& f) {fn=mirvar(0); copy(f.fn, fn);}
    Flash(const Big& b)   {fn=mirvar(0); copy(b.fn, fn);}
    Flash(char* s)  {fn=mirvar(0); cinstr(fn,s);}

    Flash& operator=(int i) {convert(i,fn); return *this;}
    Flash& operator=(long lg){lgconv(lg,fn); return *this;}
    Flash& operator=(double& d)  {dconv(d,fn);    return *this;}
    Flash& operator=(const Flash& f)   {copy(f.fn, fn); return *this;}
    Flash& operator=(const Big& b)     {copy(b.fn, fn); return *this;}
    Flash& operator=(char* s)    {cinstr(fn,s);return *this;}

    Flash& operator++()      {fincr(fn,1,1,fn);  return *this;}
    Flash& operator--()      {fincr(fn,-1,1,fn); return *this;}
    Flash& operator+=(const Flash& f) {fadd(fn,f.fn,fn);  return *this;}

    Flash& operator-=(const Flash& f) {fsub(fn,f.fn,fn);  return *this;}

    Flash& operator*=(const Flash& f) {fmul(fn,f.fn,fn);  return *this;}

    Flash& operator/=(const Flash& f) {fdiv(fn,f.fn,fn);  return *this;}
    Flash& operator%=(const Flash& f) {fmodulo(fn,f.fn,fn); return *this;}

    Big trunc(Flash *rem=NULL);
    Big num(void);
    Big den(void);
    BOOL iszero() const;

    friend Flash operator-(const Flash&);   /* unary - */

    /* binary ops */

    friend Flash operator+(const Flash&, const Flash&);

    friend Flash operator-(const Flash&, const Flash&);

    friend Flash operator*(const Flash&, const Flash&);

    friend Flash operator/(const Flash&, const Flash&);

    friend Flash operator%(const Flash&,const Flash&);

    /* relational ops */

    friend BOOL operator<=(const Flash& f1, const Flash& f2)
    {if (fcomp(f1.fn,f2.fn) <= 0) return TRUE; else return FALSE;}
    friend BOOL operator>=(const Flash& f1, const Flash& f2) 
    {if (fcomp(f1.fn,f2.fn) >= 0) return TRUE; else return FALSE;}
    friend BOOL operator==(const Flash& f1, const Flash& f2)
    {if (fcomp(f1.fn,f2.fn) == 0) return TRUE; else return FALSE;}
    friend BOOL operator!=(const Flash& f1, const Flash& f2)
    {if (fcomp(f1.fn,f2.fn) != 0) return TRUE; else return FALSE;}
    friend BOOL operator<(const Flash& f1, const Flash& f2)
    {if (fcomp(f1.fn,f2.fn) < 0)  return TRUE; else return FALSE;}
    friend BOOL operator>(const Flash& f1, const Flash& f2) 
    {if (fcomp(f1.fn,f2.fn) > 0)  return TRUE; else return FALSE;}

    friend Flash pi(); 
    friend Flash cos(const Flash&);
    friend Flash sin(const Flash&);
    friend Flash tan(const Flash&);

    friend Flash acos(const Flash&);
    friend Flash asin(const Flash&);
    friend Flash atan(const Flash&);

    friend Flash cosh(const Flash&);
    friend Flash sinh(const Flash&);
    friend Flash tanh(const Flash&);

    friend Flash acosh(const Flash&);
    friend Flash asinh(const Flash&);
    friend Flash atanh(const Flash&);

    friend Flash log(const Flash&);
    friend Flash exp(const Flash&);
    friend Flash pow(const Flash&,const Flash&);
    friend Flash sqrt(const Flash&);
    friend Flash nroot(const Flash&,int);
    friend Flash fabs(const Flash&);

    friend double todouble(const Flash& f) { return fdsize(f.fn);}
    friend istream& operator>>(istream&, Flash&);
    friend ostream& operator<<(ostream&, const Flash&);

    ~Flash()   {mirkill(fn);}
};

#endif
#endif

