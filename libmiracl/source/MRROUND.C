/*
 *   MIRACL euclidean mediant rounding routine
 *   mrround.c
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

#ifdef MR_FLASH

#define abs(x)  ((x)<0? (-(x)) : (x))

static int euclid(_MIPD_ big x,int num)
{ /* outputs next c.f. quotient from gcd(w5,w6) */
    mr_small sr,m;
#ifdef mr_dltype
    mr_large lr,lq;
#else
    mr_small lr,lq;
#endif
    big t;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (num==0)
    {
        mr_mip->oldn=(-1);
        mr_mip->carryon=FALSE;
        mr_mip->last=FALSE;
        if (compare(mr_mip->w6,mr_mip->w5)>0)
        { /* ensure w5>w6 */
            t=mr_mip->w5,mr_mip->w5=mr_mip->w6,mr_mip->w6=t;
            return (mr_mip->q=0);
        }
    }
    else if (num==mr_mip->oldn || mr_mip->q<0) return mr_mip->q;
    mr_mip->oldn=num;
    if (mr_mip->carryon) goto middle;
start:
    if (size(mr_mip->w6)==0) return (mr_mip->q=(-1));
    mr_mip->ndig=(int)mr_mip->w5[0];
    mr_mip->carryon=TRUE;
    mr_mip->a=1;
    mr_mip->b=0;
    mr_mip->c=0;
    mr_mip->d=1;
    if (mr_mip->ndig==1)
    {
        mr_mip->last=TRUE;
        mr_mip->u=mr_mip->w5[1];
        mr_mip->v=mr_mip->w6[1];
    }
    else
    {
        m=mr_mip->w5[mr_mip->ndig]+1;
        if (mr_mip->base==0)
        {
#ifdef mr_dltype
 /* use double length types if available */
            if (mr_mip->ndig>2 && m!=0)
            { /* squeeze out as much significance as possible */
                MR_TOP(mr_mip->u)=muldvm(mr_mip->w5[mr_mip->ndig],mr_mip->w5[mr_mip->ndig-1],m,&sr);
                MR_BOT(mr_mip->u)=muldvm(sr,mr_mip->w5[mr_mip->ndig-2],m,&sr);
                MR_TOP(mr_mip->v)=muldvm(mr_mip->w6[mr_mip->ndig],mr_mip->w6[mr_mip->ndig-1],m,&sr);
                MR_BOT(mr_mip->v)=muldvm(sr,mr_mip->w6[mr_mip->ndig-2],m,&sr);
            }
            else
            {
                MR_TOP(mr_mip->u)=mr_mip->w5[mr_mip->ndig];
                MR_BOT(mr_mip->u)=mr_mip->w5[mr_mip->ndig-1];
                MR_TOP(mr_mip->v)=mr_mip->w6[mr_mip->ndig];
                MR_BOT(mr_mip->v)=mr_mip->w6[mr_mip->ndig-1];
                if (mr_mip->ndig==2) mr_mip->last=TRUE;
            }
#else
            if (m==0)
            {
                mr_mip->u=mr_mip->w5[mr_mip->ndig];
                mr_mip->v=mr_mip->w6[mr_mip->ndig];
            }
            else
            {
                mr_mip->u=muldvm(mr_mip->w5[mr_mip->ndig],mr_mip->w5[mr_mip->ndig-1],m,&sr);
                mr_mip->v=muldvm(mr_mip->w6[mr_mip->ndig],mr_mip->w6[mr_mip->ndig-1],m,&sr);
            }
#endif
        }
        else
        {
#ifdef mr_dltype
 /* use double length types if available */
            if (mr_mip->ndig>2)
            { /* squeeze out as much significance as possible */
                mr_mip->u=muldiv(mr_mip->w5[mr_mip->ndig],mr_mip->base,mr_mip->w5[mr_mip->ndig-1],m,&sr);
                mr_mip->u=mr_mip->u*mr_mip->base+muldiv(sr,mr_mip->base,mr_mip->w5[mr_mip->ndig-2],m,&sr);
                mr_mip->v=muldiv(mr_mip->w6[mr_mip->ndig],mr_mip->base,mr_mip->w6[mr_mip->ndig-1],m,&sr);
                mr_mip->v=mr_mip->v*mr_mip->base+muldiv(sr,mr_mip->base,mr_mip->w6[mr_mip->ndig-2],m,&sr);
            }
            else
            {
                mr_mip->u=(mr_large)mr_mip->base*mr_mip->w5[mr_mip->ndig]+mr_mip->w5[mr_mip->ndig-1];
                mr_mip->v=(mr_large)mr_mip->base*mr_mip->w6[mr_mip->ndig]+mr_mip->w6[mr_mip->ndig-1];
                mr_mip->last=TRUE;
            }
#else
            mr_mip->u=muldiv(mr_mip->w5[mr_mip->ndig],mr_mip->base,mr_mip->w5[mr_mip->ndig-1],m,&sr);
            mr_mip->v=muldiv(mr_mip->w6[mr_mip->ndig],mr_mip->base,mr_mip->w6[mr_mip->ndig-1],m,&sr);
#endif
        }
    }
    mr_mip->ku=mr_mip->u;
    mr_mip->kv=mr_mip->v;
middle:
    forever
    { /* work only with most significant piece */
        if (mr_mip->last)
        {
            if (mr_mip->v==0) return (mr_mip->q=(-1));
            lq=mr_mip->u/mr_mip->v;
        }
        else
        {
            if (((mr_mip->v+mr_mip->c)==0) || ((mr_mip->v+mr_mip->d)==0)) break;
            lq=(mr_mip->u+mr_mip->a)/(mr_mip->v+mr_mip->c);
            if (lq!=(mr_mip->u+mr_mip->b)/(mr_mip->v+mr_mip->d)) break;
        }
#ifdef mr_dltype
        if (lq>=(mr_large)(MR_TOOBIG/abs(mr_mip->d))) break;
#else
        if (lq>=(mr_small)(MR_TOOBIG/abs(mr_mip->d))) break;
#endif
        mr_mip->q=(int)lq;
        mr_mip->r=mr_mip->a-mr_mip->q*mr_mip->c;
        mr_mip->a=mr_mip->c;
        mr_mip->c=mr_mip->r;
        mr_mip->r=mr_mip->b-mr_mip->q*mr_mip->d;
        mr_mip->b=mr_mip->d;
        mr_mip->d=mr_mip->r;
        lr=mr_mip->u-lq*mr_mip->v;
        mr_mip->u=mr_mip->v;
        mr_mip->v=lr;
        return mr_mip->q;
    }
    mr_mip->carryon=FALSE;
    if (mr_mip->b==0)
    { /* update w5 and w6 */
        mr_mip->check=OFF;
        divide(_MIPP_ mr_mip->w5,mr_mip->w6,mr_mip->w7);
        mr_mip->check=ON;
        if (mr_lent(mr_mip->w7)>mr_mip->nib) return (mr_mip->q=(-2));
        t=mr_mip->w5,mr_mip->w5=mr_mip->w6,mr_mip->w6=t;   /* swap(w5,w6) */
        copy(mr_mip->w7,x);
        return (mr_mip->q=size(x));
    }
    else
    {
        mr_mip->check=OFF;
        premult(_MIPP_ mr_mip->w5,mr_mip->c,mr_mip->w7);
        premult(_MIPP_ mr_mip->w5,mr_mip->a,mr_mip->w5);
        premult(_MIPP_ mr_mip->w6,mr_mip->b,mr_mip->w0);
        premult(_MIPP_ mr_mip->w6,mr_mip->d,mr_mip->w6);
        add_r(_MIPP_ mr_mip->w5,mr_mip->w0,mr_mip->w5);
        add_r(_MIPP_ mr_mip->w6,mr_mip->w7,mr_mip->w6);
        mr_mip->check=ON;
    }
    goto start;
}


void round(_MIPD_ big num,big den,flash z)
{ /* reduces and rounds the fraction num/den into z */
    int s;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    if (size(num)==0) 
    {
        zero(z);
        return;
    }

    MR_IN(34)

    if (size(den)==0)
    {
        mr_berror(_MIPP_ MR_ERR_FLASH_OVERFLOW);
        MR_OUT
        return;
    }
    copy(num,mr_mip->w5);
    copy(den,mr_mip->w6);
    s=exsign(mr_mip->w5)*exsign(mr_mip->w6);
    insign(PLUS,mr_mip->w5);
    insign(PLUS,mr_mip->w6);
    if (compare(mr_mip->w5,mr_mip->w6)==0)
    {
        convert(_MIPP_ s,z);
        MR_OUT
        return;
    }
    if (size(mr_mip->w6)==1)
    {
        if ((int)mr_mip->w5[0]>mr_mip->nib)
        {
            mr_berror(_MIPP_ MR_ERR_FLASH_OVERFLOW);
            MR_OUT
            return;
        }
        copy(mr_mip->w5,z);
        insign(s,z);
        MR_OUT
        return;
    }
    build(_MIPP_ z,euclid);
    insign(s,z);
    MR_OUT
}

#endif

