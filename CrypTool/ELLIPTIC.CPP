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
 *    MIRACL  C++  functions elliptic.cpp
 *
 *    AUTHOR  :    M. Scott
 *             
 *    PURPOSE :    Implementation of class ECn functions using Montgomery
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
#include "elliptic.h"

int ECn::get(Big& x,Big& y) const 
        {return epoint_get(p,x.getbig(),y.getbig());}
int ECn::get(Big& x) const   
        {return epoint_get(p,x.getbig(),x.getbig());}
BOOL ECn::iszero() const
        {if (p->marker==MR_EPOINT_INFINITY) return TRUE; return FALSE;}
epoint * ECn::get_point() const
{ return p; }

ECn operator-(const ECn& e)
{ ECn t=e; epoint_negate(t.p); return t;}

ECn mul(const Big& e1,const ECn& p1,const Big& e2,const ECn& p2)
{ 
    ECn t; 
    ecurve_mult2(e1.getbig(),p1.get_point(),e2.getbig(),p2.get_point(),t.get_point());
    return t;
}

ECn operator*(const Big& e,const ECn& b)
{
    ECn t;
    ecurve_mult(e.getbig(),b.p,t.p);
    return t;
}

ECn mul(int n,const Big *y,ECn *x)
{
    ECn w;
    int i;
    big *a=(big *)mr_alloc(n,sizeof(big));
    epoint **b=(epoint **)mr_alloc(n,sizeof(epoint *));
    for (i=0;i<n;i++)
    {
        a[i]=y[i].getbig();
        b[i]=x[i].p;
    }
    ecurve_multn(n,a,b,w.p);

    mr_free(b);
    mr_free(a);
    return w;  
}

void multi_add(int m,ECn *x, ECn *w)
{
    int i;
    epoint **xp=(epoint **)mr_alloc(m,sizeof(epoint *));
    epoint **wp=(epoint **)mr_alloc(m,sizeof(epoint *));
    for (i=0;i<m;i++)
    {
        xp[i]=x[i].p;
        wp[i]=w[i].p;
    }
    ecurve_multi_add(m,xp,wp);
    mr_free(wp);
    mr_free(xp);
}

ostream& operator<<(ostream& s,const ECn& b)
{
    Big x,y;
    b.get(x,y);
    s << "(" << x << "," << y << ")";
    return s;
}

void ecurve(const Big& a,const Big& b,const Big& p,int t)
{ ecurve_init(a.fn,b.fn,p.fn,t);}

