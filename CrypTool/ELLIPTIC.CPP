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

