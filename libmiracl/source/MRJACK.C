/*
 *   MIRACL Jacobi symbol routine
 *   mrjack.c
 *
 *   See "Prime numbers and Computer methods for Factorisation", 
 *   Hans Reisel, Birkhauser 1985, page 286
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

int jack(_MIPD_ big x,big n)
{ /* find jacobi symbol for x wrt n. Only defined for *
   * positive n, n odd. Otherwise returns 0     */
    int m,n8,i2,u4;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM || size(x)==0 || size(n) <1) return 0;
    copy(x,mr_mip->w1);
    copy(n,mr_mip->w2);

    divide(_MIPP_ mr_mip->w1,mr_mip->w2,mr_mip->w2);
    if (size(mr_mip->w1)<0) add_r(_MIPP_ mr_mip->w1,mr_mip->w2,mr_mip->w1);

    MR_IN(3)

    if (subdiv(_MIPP_ mr_mip->w2,2,mr_mip->w3)==0)
    { /* n is even */
        MR_OUT
        return 0;
    }
    m=0;
    while(!mr_mip->ERNUM && size(mr_mip->w2)>1)
    { /* main loop */
        if (size(mr_mip->w1)==0)
        { /* gcd(x,n) > 0 */
            MR_OUT
            return 0;
        }
        n8=subdiv(_MIPP_ mr_mip->w2,8,mr_mip->w3);
        i2=0;
        while (subdiv(_MIPP_ mr_mip->w1,2,mr_mip->w3)==0)
        { /* extract powers of 2 */
            i2++;
            copy(mr_mip->w3,mr_mip->w1);
        }
        if ((i2%2)==1) m+=(n8*n8-1)/8;
        u4=subdiv(_MIPP_ mr_mip->w1,4,mr_mip->w3);
        m+=(n8-1)*(u4-1)/4;
        copy(mr_mip->w2,mr_mip->w3);
        divide(_MIPP_ mr_mip->w3,mr_mip->w1,mr_mip->w1);
        copy(mr_mip->w1,mr_mip->w2);
        copy(mr_mip->w3,mr_mip->w1);
        m%=2;
    }
    MR_OUT
    if (m%2==0) return 1;
    else return (-1);
} 

