/*
 *   MIRACL Extended Greatest Common Divisor module.
 *   mrxgcd.c
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>
#define abs(x)  ((x)<0? (-(x)) : (x))

int xgcd(_MIPD_ big x,big y,big xd,big yd,big z)
{ /* greatest common divisor by Euclids method  *
   * extended to also calculate xd and yd where *
   *      z = x.xd + y.yd = gcd(x,y)            *
   * if xd, yd not distinct, only xd calculated *
   * z only returned if distinct from xd and yd *
   * xd will always be positive, yd negative    */
    int q,r,a,b,c,d,s,n;
    mr_small m,sr;
#ifdef mr_dltype
    mr_large u,v,lq,lr;
#else
    mr_small u,v,lq,lr;
#endif

    BOOL last;
    big t;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return 0;

    MR_IN(30)

    copy(x,mr_mip->w1);
    copy(y,mr_mip->w2);
    s=exsign(mr_mip->w1);
    insign(PLUS,mr_mip->w1);
    insign(PLUS,mr_mip->w2);
/*    copy(mr_mip->w1,mr_mip->w3);
    copy(mr_mip->w2,mr_mip->w4);  */
    convert(_MIPP_ 1,mr_mip->w3);
    zero(mr_mip->w4);
    last=FALSE;
    a=b=c=d=0;
    while (size(mr_mip->w2)!=0)
    {
        if (b==0)
        { /* update mr_mip->w1 and mr_mip->w2 */
            divide(_MIPP_ mr_mip->w1,mr_mip->w2,mr_mip->w5);
            t=mr_mip->w1,mr_mip->w1=mr_mip->w2,mr_mip->w2=t;    /* swap(mr_mip->w1,mr_mip->w2) */
            multiply(_MIPP_ mr_mip->w4,mr_mip->w5,mr_mip->w0);
            subtract(_MIPP_ mr_mip->w3,mr_mip->w0,mr_mip->w3);
            t=mr_mip->w3,mr_mip->w3=mr_mip->w4,mr_mip->w4=t;    /* swap(xd,yd) */
        }
        else
        {
            premult(_MIPP_ mr_mip->w1,c,mr_mip->w5);
            premult(_MIPP_ mr_mip->w1,a,mr_mip->w1);
            premult(_MIPP_ mr_mip->w2,b,mr_mip->w0);
            premult(_MIPP_ mr_mip->w2,d,mr_mip->w2);
            add_r(_MIPP_ mr_mip->w1,mr_mip->w0,mr_mip->w1);
            add_r(_MIPP_ mr_mip->w2,mr_mip->w5,mr_mip->w2);
            premult(_MIPP_ mr_mip->w3,c,mr_mip->w5);
            premult(_MIPP_ mr_mip->w3,a,mr_mip->w3);
            premult(_MIPP_ mr_mip->w4,b,mr_mip->w0);
            premult(_MIPP_ mr_mip->w4,d,mr_mip->w4);
            add_r(_MIPP_ mr_mip->w3,mr_mip->w0,mr_mip->w3);
            add_r(_MIPP_ mr_mip->w4,mr_mip->w5,mr_mip->w4);
        }
        if (mr_mip->ERNUM || size(mr_mip->w2)==0) break;
        n=(int)mr_mip->w1[0];
        a=1;
        b=0;
        c=0;
        d=1;
        if (n==1)
        {
            last=TRUE;
            u=mr_mip->w1[1];
            v=mr_mip->w2[1];
        }
        else
        {
            m=mr_mip->w1[n]+1;
            if (mr_mip->base==0)
            {
#ifdef mr_dltype
 /* use double length type if available */
                if (n>2 && m!=0)
                { /* squeeze out as much significance as possible */
                    MR_TOP(u)=muldvm(mr_mip->w1[n],mr_mip->w1[n-1],m,&sr);
                    MR_BOT(u)=muldvm(sr,mr_mip->w1[n-2],m,&sr);
                    MR_TOP(v)=muldvm(mr_mip->w2[n],mr_mip->w2[n-1],m,&sr);
                    MR_BOT(v)=muldvm(sr,mr_mip->w2[n-2],m,&sr);
                }
                else
                {
                    MR_TOP(u)=mr_mip->w1[n];
                    MR_BOT(u)=mr_mip->w1[n-1];
                    MR_TOP(v)=mr_mip->w2[n];
                    MR_BOT(v)=mr_mip->w2[n-1];
                    if (n==2) last=TRUE;
                }
#else
                if (m==0)
                {
                    u=mr_mip->w1[n];
                    v=mr_mip->w2[n];
                }
                else
                {
                    u=muldvm(mr_mip->w1[n],mr_mip->w1[n-1],m,&sr);
                    v=muldvm(mr_mip->w2[n],mr_mip->w2[n-1],m,&sr);
                }
#endif
            }
            else
            {
#ifdef mr_dltype
 /* use double length type if available */
                if (n>2)
                { /* squeeze out as much significance as possible */
                    u=muldiv(mr_mip->w1[n],mr_mip->base,mr_mip->w1[n-1],m,&sr);
                    u=u*mr_mip->base+muldiv(sr,mr_mip->base,mr_mip->w1[n-2],m,&sr);
                    v=muldiv(mr_mip->w2[n],mr_mip->base,mr_mip->w2[n-1],m,&sr);
                    v=v*mr_mip->base+muldiv(sr,mr_mip->base,mr_mip->w2[n-2],m,&sr);
                }
                else
                {
                    u=(mr_large)mr_mip->base*mr_mip->w1[n]+mr_mip->w1[n-1];
                    v=(mr_large)mr_mip->base*mr_mip->w2[n]+mr_mip->w2[n-1];
                    last=TRUE;
                }
#else
                u=muldiv(mr_mip->w1[n],mr_mip->base,mr_mip->w1[n-1],m,&sr);
                v=muldiv(mr_mip->w2[n],mr_mip->base,mr_mip->w2[n-1],m,&sr);
#endif
            }
        }
        forever
        { /* work only with most significant piece */
            if (last)
            {
                if (v==0) break;
                lq=u/v;
            }
            else
            {
                if (((v+c)==0) || ((v+d)==0)) break;
                lq=(u+a)/(v+c);
                if (lq!=(u+b)/(v+d)) break;
            }
#ifdef mr_dltype
            if (lq>=(mr_large)(MR_TOOBIG/abs(d))) break;
#else
            if (lq>=(mr_small)(MR_TOOBIG/abs(d))) break;
#endif
            q=(int)lq;
            r=a-q*c;
            a=c;
            c=r;
            r=b-q*d;
            b=d;
            d=r;
            lr=u-lq*v;
            u=v;
            v=lr;
        }
    }
    if (s==MINUS) negate(mr_mip->w3,mr_mip->w3);
    if (size(mr_mip->w3)<=0) add_r(_MIPP_ mr_mip->w3,y,mr_mip->w3);
    if (xd!=yd)
    {
        negate(x,mr_mip->w2);
        mad(_MIPP_ mr_mip->w2,mr_mip->w3,mr_mip->w1,y,mr_mip->w4,mr_mip->w4);
        copy(mr_mip->w4,yd);
    }
    copy(mr_mip->w3,xd);
    if (z!=xd && z!=yd) copy(mr_mip->w1,z);
    MR_OUT
    return (size(mr_mip->w1));
}


