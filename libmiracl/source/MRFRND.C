/*
 *   MIRACL flash random number routine 
 *   mrfrnd.c
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

#ifdef MR_FLASH

void frand(_MIPD_ flash x)
{ /* generates random flash number 0<x<1 */
    int i;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(46)

    zero(mr_mip->w6);
    mr_mip->w6[0]=mr_mip->nib;
    for (i=1;i<=mr_mip->nib;i++) 
    { /* generate a full width random number */
        if (mr_mip->base==0) mr_mip->w6[i]=brand(_MIPPO_ );
        else                 mr_mip->w6[i]=brand(_MIPPO_ )%mr_mip->base;
    }
    mr_mip->check=OFF;
    bigrand(_MIPP_ mr_mip->w6,mr_mip->w5);
    mr_mip->check=ON;
    round(_MIPP_ mr_mip->w5,mr_mip->w6,x);

    MR_OUT
}

#endif

