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
 *    MIRACL  C++  functions monty.cpp
 *
 *    AUTHOR  :    M. Scott
 *             
 *    PURPOSE :    Implementation of class ZZn functions using Montgomery
 *                 representation
 *    NOTE    :    Must be used in conjunction with big.h and big.cpp
 *
 *    Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif
#include "monty.h"

BOOL ZZn::iszero() const
{return fn.iszero(); }

ZZn operator-( const ZZn& b)
{ZZn nb; nb.fn=nres_negate(b.fn); return nb;}
ZZn operator+( const ZZn& b,int i)
{ZZn abi; abi.fn=nres_modadd(b.fn,nres((Big)i));return abi;}
ZZn operator+(int i, const ZZn& b)
{ZZn aib; aib.fn=nres_modadd(b.fn,nres((Big)i));return aib;}
ZZn operator+( const ZZn& b1,  const ZZn& b2)
{ZZn abb;abb.fn=nres_modadd(b1.fn,b2.fn); return abb;}

ZZn operator-(const ZZn& b, int i)
{ZZn mbi; mbi.fn=nres_modsub(b.fn,nres((Big)i)); return mbi;}
ZZn operator-(int i, const ZZn& b)   
{ZZn mib; mib.fn=nres_modsub(nres((Big)i),b.fn); return mib;}
ZZn operator-(const ZZn& b1,  const ZZn& b2)
{ZZn mbb;mbb.fn=nres_modsub(b1.fn,b2.fn);  return mbb;}

ZZn operator*( const ZZn& b1, int i)
{ZZn xbb; xbb.fn=nres_premult(b1.fn,i); return xbb;}
ZZn operator*( int i, const ZZn& b2)
{ZZn xbb; xbb.fn=nres_premult(b2.fn,i); return xbb;}
ZZn operator*( const ZZn& b1, const ZZn& b2)
{ZZn xbb; xbb.fn=nres_modmult(b1.fn,b2.fn); return xbb;}

ZZn operator/(const ZZn& b1, int i)
{ZZn z; z.fn=nres_moddiv(b1.fn,nres((Big)i)); return z;}
ZZn operator/(int i, const ZZn& b2)
{ZZn z; z.fn=nres_moddiv(nres((Big)i),b2.fn); return z;}
ZZn operator/(const ZZn& b1, const ZZn& b2)
{ZZn z; z.fn=nres_moddiv(b1.fn,b2.fn); return z;}

ZZn pow( const ZZn& b1, const Big& b2)
{ZZn z;z.fn=nres_pow(b1.fn,b2);return z;}

ZZn pow( const ZZn& b,int i)
{ZZn z; z.fn=nres_pow(b.fn,(Big)i); return z;}

ZZn pow( const ZZn& b1, const Big& b2, const ZZn& b3,const Big& b4)
{ZZn z;z.fn=nres_pow2(b1.fn,b2,b3.fn,b4); return z;}

ZZn pow(int n,ZZn *x,Big *y)
{
   ZZn z;
   int i;
   Big *a=new Big[n];
   for (i=0;i<n;i++) 
      a[i]=x[i].fn;
   z.fn=nres_pown(n,a,y);

   delete [] a;
   return z;
}

ZZn luc( const ZZn& b1, const Big& b2, ZZn *b3)
{ZZn z; if (b3!=NULL) z.fn=nres_luc(b1.fn,b2,&(b3->fn)); 
        else          z.fn=nres_luc(b1.fn,b2); 
 return z;}


ZZn sqrt(const ZZn& b)
{ZZn z; z.fn=nres_sqrt(b.fn); return z;}

