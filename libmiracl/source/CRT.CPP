/*
 *   MIRACL Chinese Remainder Thereom routines (for use with crt.h) 
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#if !defined(_MSC_VER) || _MSC_VER <= 1200  
#include <iostream.h>
#else
#include <iostream>
#endif

#include <crt.h>

Crt::Crt(int r,Big *moduli)
{ /* constructor */
    big *b=(big *)mr_alloc(r,sizeof(big));
    for (int i=0;i<r;i++) b[i]=moduli[i].getbig();
    type=BIGS;
    crt_init(&bc,r,b);
    mr_free(b);
}

Crt::Crt(int r,mr_utype *moduli)
{ /* constructor */
    type=SMALLS; 
    scrt_init(&sc,r,moduli);
}

Big Crt::eval(Big *u)
{           
    Big x;
    big *b=(big *)mr_alloc(bc.NP,sizeof(big));
    for (int i=0;i<bc.NP;i++) b[i]=u[i].getbig();
    crt(&bc,b,x.getbig());
    mr_free(b); 
    return x;
}

Big Crt::eval(mr_utype *u)
{
    Big x;
    scrt(&sc,u,x.getbig());
    return x;
}

