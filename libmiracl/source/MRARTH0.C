/*
 *   MIRACL arithmetic routines 0 - Add and subtract routines 
 *   mrarth0.c
 *
 *   Copyright (c) 1988-1995 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

void mr_padd(_MIPD_ big x,big y,big z)
{ /*  add two  big numbers, z=x+y where *
   *  x and y are positive              */
    int lx,ly,lz,la,i;
    mr_small carry,psum;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    lx = (int)x[0];
    ly = (int)y[0];
    
    if (ly>lx)
    {
        lz=ly;
        la=lx;
        if (x!=z) copy(y,z); 
        else la=ly;  
    }
    else
    {
        lz=lx;
        la=ly;
        if (y!=z) copy(x,z);
        else la=lx;
    }
    carry=0;
    z[0]=lz;
    if (lz<mr_mip->nib || !mr_mip->check) z[0]++;
    if (mr_mip->base==0) for (i=1;i<=la || carry>0;i++)
    { /* add by columns */
        if (mr_mip->check && i>mr_mip->nib)
        {
            mr_berror(_MIPP_ MR_ERR_OVERFLOW);
            return;
        }
        psum=x[i]+y[i]+carry;
        if (psum>x[i]) carry=0;
        if (psum<x[i]) carry=1;
        z[i]=psum;
    }
    else for (i=1;i<=la || carry>0;i++)
    { /* add by columns */
        if (i>mr_mip->nib && mr_mip->check)
        {
            mr_berror(_MIPP_ MR_ERR_OVERFLOW);
            return;
        }
        psum=x[i]+y[i]+carry;
        carry=0;
        if (psum>=mr_mip->base)
        { /* set carry */
            carry=1;
            psum-=mr_mip->base;
        }
        z[i]=psum;
    }
    if (z[z[0]]==0) z[0]--;
}

void mr_psub(_MIPD_ big x,big y,big z)
{  /*  subtract two big numbers z=x-y      *
    *  where x and y are positive and x>y  */
    int lx,ly,i;
    mr_small borrow,pdiff;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    lx = (int)x[0];
    ly = (int)y[0];
    if (ly>lx)
    {
        mr_berror(_MIPP_ MR_ERR_NEG_RESULT);
        return;
    }
    if (y!=z) copy(x,z);
    else ly=lx;
    z[0]=lx;
    borrow=0;
    if (mr_mip->base==0) for (i=1;i<=ly || borrow>0;i++)
    { /* subtract by columns */
        if (i>lx)
        {
            mr_berror(_MIPP_ MR_ERR_NEG_RESULT);
            return;
        }
        pdiff=x[i]-y[i]-borrow;
        if (pdiff<x[i]) borrow=0;
        if (pdiff>x[i]) borrow=1;
        z[i]=pdiff;
    }
    else for (i=1;i<=ly || borrow>0;i++)
    { /* subtract by columns */
        if (i>lx)
        {
            mr_berror(_MIPP_ MR_ERR_NEG_RESULT);
            return;
        }
        pdiff=y[i]+borrow;
        borrow=0;
        if (x[i]>=pdiff) pdiff=x[i]-pdiff;
        else
        { /* set borrow */
            pdiff=mr_mip->base+x[i]-pdiff;
            borrow=1;
        }
        z[i]=pdiff;
    }
    mr_lzero(z);
}

static void select(_MIPD_ big x,int d,big y,big z)
{ /* perform required add or subtract operation */
    int sx,sy,sz,jf,xgty;
#ifdef MR_FLASH
    if (mr_notint(x) || mr_notint(y))
    {
        mr_berror(_MIPP_ MR_ERR_INT_OP);
        return;
    }
#endif
    sx=exsign(x);
    sy=exsign(y);
    x[0]&=MR_OBITS;  /* force operands to be positive */
    y[0]&=MR_OBITS;
    xgty=compare(x,y);
    jf=(1+sx)+(1+d*sy)/2;
    switch (jf)
    { /* branch according to signs of operands */
    case 0:
        if (xgty>=0)
            mr_padd(_MIPP_ x,y,z);
        else
            mr_padd(_MIPP_ y,x,z);
        sz=MINUS;
        break;
    case 1:
        if (xgty<=0)
        {
            mr_psub(_MIPP_ y,x,z);
            sz=PLUS;
        }
        else
        {
            mr_psub(_MIPP_ x,y,z);
            sz=MINUS;
        }
        break;
    case 2:
        if (xgty>=0)
        {
            mr_psub(_MIPP_ x,y,z);
            sz=PLUS;
        }
        else
        {
            mr_psub(_MIPP_ y,x,z);
            sz=MINUS;
        }
        break;
    case 3:
        if (xgty>=0)
            mr_padd(_MIPP_ x,y,z);
        else
            mr_padd(_MIPP_ y,x,z);
        sz=PLUS;
        break;
    }
    if (sz<0) z[0]^=MR_MSBIT;         /* set sign of result         */
    if (x!=z && sx<0) x[0]^=MR_MSBIT; /* restore signs to operands  */
    if (y!=z && y!=x && sy<0) y[0]^=MR_MSBIT;
}

void add_r(_MIPD_ big x,big y,big z)
{  /* add two signed big numbers together z=x+y */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(27)

    select(_MIPP_ x,PLUS,y,z);

    MR_OUT
}

void subtract(_MIPD_ big x,big y,big z)
{ /* subtract two big signed numbers z=x-y */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(28)

    select(_MIPP_ x,MINUS,y,z);

    MR_OUT
}

void incr(_MIPD_ big x,int n,big z)
{  /* add int to big number: z=x+n */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(7)

    convert(_MIPP_ n,mr_mip->w0);
    select(_MIPP_ x,PLUS,mr_mip->w0,z);

    MR_OUT
}

void decr(_MIPD_ big x,int n,big z)
{  /* subtract int from big number: z=x-n */   
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(8)

    convert(_MIPP_ n,mr_mip->w0);
    select(_MIPP_ x,MINUS,mr_mip->w0,z);

    MR_OUT
}

