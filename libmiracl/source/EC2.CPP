/*
 *    MIRACL  C++  functions ec2.cpp
 *
 *    AUTHOR  :    M. Scott
 *             
 *    PURPOSE :    Implementation of class EC2 functions 
 *    NOTE    :    Must be used in conjunction with big.h and big.cpp
 *
 *    Copyright (c) 2000 Shamus Software Ltd.
 */

#include <iostream.h>
#include <ec2.h>

int EC2::get(Big& x,Big& y) const 
        {return epoint2_get(p,x.getbig(),y.getbig());}
int EC2::get(Big& x) const   
        {return epoint2_get(p,x.getbig(),x.getbig());}

BOOL EC2::iszero() const
        {if (p->marker==MR_EPOINT_INFINITY) return TRUE; return FALSE;}

epoint * EC2::get_point() const
{ return p; }

EC2 operator-(const EC2& e)
{ EC2 t=e; epoint2_negate(t.p); return t;}

EC2 mul(const Big& e1,const EC2& p1,const Big& e2,const EC2& p2)
{ 
    EC2 t; 
    ecurve2_mult2(e1.getbig(),p1.get_point(),e2.getbig(),p2.get_point(),t.get_point());
    return t;
}

EC2 operator*(const Big& e,const EC2& b)
{
    EC2 t;
    ecurve2_mult(e.getbig(),b.p,t.p);
    return t;
}

EC2 mul(int n,const Big *y,EC2 *x)
{
    EC2 w;
    int i;
    big *a=(big *)mr_alloc(n,sizeof(big));
    epoint **b=(epoint **)mr_alloc(n,sizeof(epoint *));
    for (i=0;i<n;i++)
    {
        a[i]=y[i].getbig();
        b[i]=x[i].p;
    }
    ecurve2_multn(n,a,b,w.p);

    mr_free(b);
    mr_free(a);
    return w;  
}

void multi_add(int m,EC2 *x, EC2 *w)
{
    int i;
    epoint **xp=(epoint **)mr_alloc(m,sizeof(epoint *));
    epoint **wp=(epoint **)mr_alloc(m,sizeof(epoint *));
    for (i=0;i<m;i++)
    {
        xp[i]=x[i].p;
        wp[i]=w[i].p;
    }
    ecurve2_multi_add(m,xp,wp);
    mr_free(wp);
    mr_free(xp);
}

ostream& operator<<(ostream& s,const EC2& b)
{
    Big x,y;
    b.get(x,y);
    s << "(" << x << "," << y << ")";
    return s;
}

BOOL ecurve2(int m,int a,int b,int c,const Big& a2,const Big& a6,BOOL check,int t)
{ return ecurve2_init(m,a,b,c,a2.fn,a6.fn,check,t);}

