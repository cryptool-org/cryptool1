/*
 *   MIRACL small number theoretic routines 
 *   mrsmall.c
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

mr_utype smul(mr_utype x,mr_utype y,mr_utype n)
{ /* returns x*y mod n */
    mr_small r;
    x%=n;
    y%=n;
    if (x<0) x+=n;
    if (y<0) y+=n;
    muldiv(x,y,(mr_small)0,n,&r);
    return (mr_utype)r;
}

mr_utype spmd(mr_utype x,mr_utype n,mr_utype m) 
{ /*  returns x^n mod m  */
    mr_small r,sx;
    x%=m;
    if (x<0) x+=m;
    r=0;
    if (x==0) return (mr_utype)r;
    r=1;
    if (n==0) return (mr_utype)r;
    sx=x;
    forever
    {
        if (n%2!=0) muldiv(r,sx,(mr_small)0,m,&r);
        n/=2;
        if (n==0) return (mr_utype)r;
        muldiv(sx,sx,(mr_small)0,m,&sx);
    }
}

mr_utype invers(mr_utype x,mr_utype y)
{ /* returns inverse of x mod y */
    mr_utype r,s,q,t,p;
    x%=y;
    if (x<0) x+=y;
    r=1;
    s=0;
    p=y;
    while (p!=0)
    { /* main euclidean loop */
        q=x/p;
        t=r-s*q;
        r=s;
        s=t;
        t=x-p*q;
        x=p;
        p=t;
    }
    if (r<0) r+=y;
    return r;
}

mr_utype sqrmp(mr_utype x,mr_utype m)
{ /* square root mod a small prime by Shanks method  *
   * returns 0 if root does not exist or m not prime */
    mr_small z,y,v,w,t,q;
    int i,e,n,r;
    BOOL pp;
    x%=m;
    if (x<0) x+=m;
    if (x==0) return 0;
    if (x==1) return 1;
    if (spmd(x,(m-1)/2,m)!=1) return 0;    /* Legendre symbol not 1   */
    if (m%4==3) return spmd(x,(m+1)/4,m);  /* easy case for m=4.k+3   */
    if (m%8==5)
    { /* also relatively easy */
        t=spmd(x,(m-1)/4,m);
        if (t==1) return spmd(x,(m+3)/8,m);
        if (t==(mr_small)(m-1))
        {
            muldiv((mr_small)4,x,(mr_small)0,m,&t);
            t=spmd(t,(m+3)/8,m);
            muldiv(t,(m+1)/2,(mr_small)0,m,&t);
            return (mr_utype)t;
        }
        return 0;
    }
    q=m-1;
    e=0;
    while (q%2==0) 
    {
        q/=2;
        e++;
    }
    if (e==0) return 0;      /* even m */
    for (r=2;;r++)
    { /* find suitable z */
        z=spmd((mr_utype)r,q,m);
        if (z==1) continue;
        t=z;
        pp=FALSE;
        for (i=1;i<e;i++)
        { /* check for composite m */
            if (t==(mr_small)(m-1)) pp=TRUE;
            muldiv(t,t,(mr_small)0,m,&t);
            if (t==1 && !pp) return 0;
        }
        if (t==(mr_small)(m-1)) break;
        if (!pp) return 0;   /* m is not prime */
    }
    y=z;
    r=e;
    v=spmd(x,(q+1)/2,m);
    w=spmd(x,q,m);
    while (w!=1)
    {
        t=w;
        for (n=0;t!=1;n++) muldiv(t,t,(mr_small)0,m,&t);
        if (n>=r) return 0;
        y=spmd(y,(mr_utype)(1<<(r-n-1)),m);
        muldiv(v,y,(mr_small)0,m,&v);
        muldiv(y,y,(mr_small)0,m,&y);
        muldiv(w,y,(mr_small)0,m,&w);
        r=n;
    }
    return (mr_utype)v;
}

