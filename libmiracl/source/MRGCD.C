/*
 *   MIRACL Greatest Common Divisor module.
 *   mrgcd.c
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>
#define abs(x)  ((x)<0? (-(x)) : (x))

int egcd(_MIPD_ big x,big y,big z)
{ /* greatest common divisor z=gcd(x,y) by Euclids  *
   * method using Lehmers algorithm for big numbers */
    int q,r,a,b,c,d,n;
    mr_small sr,m;
#ifdef mr_dltype
    mr_large u,v,lq,lr;
#else
    mr_small u,v,lq,lr;
#endif
    big t;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return 0;

    MR_IN(12)

    copy(x,mr_mip->w1);
    copy(y,mr_mip->w2);
    insign(PLUS,mr_mip->w1);
    insign(PLUS,mr_mip->w2);
    a=b=c=d=0;
    while (size(mr_mip->w2)!=0)
    {
        if (b==0)
        { /* update w1 and w2 */
            divide(_MIPP_ mr_mip->w1,mr_mip->w2,mr_mip->w2);
            t=mr_mip->w1,mr_mip->w1=mr_mip->w2,mr_mip->w2=t;   /* swap(w1,w2) */
        }
        else
        {
            premult(_MIPP_ mr_mip->w1,c,z);
            premult(_MIPP_ mr_mip->w1,a,mr_mip->w1);
            premult(_MIPP_ mr_mip->w2,b,mr_mip->w0);
            premult(_MIPP_ mr_mip->w2,d,mr_mip->w2);
            add_r(_MIPP_ mr_mip->w1,mr_mip->w0,mr_mip->w1);
            add_r(_MIPP_ mr_mip->w2,z,mr_mip->w2);
        }
        if (mr_mip->ERNUM || size(mr_mip->w2)==0) break;
        n=(int)mr_mip->w1[0];
        if (mr_mip->w2[0]==1)
        { /* special case if mr_mip->w2 is now small */
            sr=mr_sdiv(_MIPP_ mr_mip->w1,mr_mip->w2[1],mr_mip->w1);
            if (sr==0)
            {
                copy(mr_mip->w2,mr_mip->w1);
                break;
            }
            zero(mr_mip->w1);
            mr_mip->w1[0]=1;
            mr_mip->w1[1]=sr;
            while ((sr=mr_mip->w2[1]%mr_mip->w1[1])!=0)
                  mr_mip->w2[1]=mr_mip->w1[1],mr_mip->w1[1]=sr;
            break;
        }
        a=1;
        b=0;
        c=0;
        d=1;
        m=mr_mip->w1[n]+1;
        if (mr_mip->base==0)
        {
#ifdef mr_dltype
 /* use double length types if available */
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
 /* use double length types if they are available */
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
            }
#else
            u=muldiv(mr_mip->w1[n],mr_mip->base,mr_mip->w1[n-1],m,&sr);
            v=muldiv(mr_mip->w2[n],mr_mip->base,mr_mip->w2[n-1],m,&sr);
#endif
        }
        forever
        { /* work only with most significant piece */
            if (((v+c)==0) || ((v+d)==0)) break;
            lq=(u+a)/(v+c);
            if (lq!=(u+b)/(v+d)) break;
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
    copy(mr_mip->w1,z);
    MR_OUT
    return (size(mr_mip->w1));
}

