/*
 *   MIRACL elliptic curve routines
 *   mrcurve.c
 *
 *   Assumes Weierstrass equation y^2 = x^3 + Ax + B
 *   See IEEE P1363 Draft Standard 
 *
 *   Uses Montgomery's representation internally
 *
 *   Works particularly well with fixed length Comba multiplier
 *   e.g. #define MR_COMBA 5 for 5x32 = 160 bit modulus
 *        on 32-bit computer
 *
 *   Copyright (c) 1997-1999 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

#define mr_abs(x)  ((x)<0? (-(x)) : (x))

/* initialise elliptic curve */

void ecurve_init(_MIPD_ big a,big b,big p,int type)
{ /* Initialize the active ecurve    *
   * Asize indicate size of A        *
   * Bsize indicate size of B        */
    int as;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(93)

    prepare_monty(_MIPP_ p);

    mr_mip->Asize=size(a);
    if (mr_abs(mr_mip->Asize)==MR_TOOBIG)
    {
        if (mr_mip->Asize>=0)
        { /* big positive number - check it isn't minus something small */
           copy(a,mr_mip->w1);
           divide(_MIPP_ mr_mip->w1,p,p);
           subtract(_MIPP_ p,mr_mip->w1,mr_mip->w1);
           as=size(mr_mip->w1);
           if (as<MR_TOOBIG) mr_mip->Asize=-as;
           else
           {
               if (mr_mip->A==NULL) mr_mip->A=mirvar(_MIPP_ 0);
               nres(_MIPP_ a,mr_mip->A);
           }
        }
        else
        {
               if (mr_mip->A==NULL) mr_mip->A=mirvar(_MIPP_ 0);
               nres(_MIPP_ a,mr_mip->A);
        }
    }
    mr_mip->Bsize=size(b);
    if (mr_abs(mr_mip->Bsize)==MR_TOOBIG)
    {
        if (mr_mip->B==NULL) mr_mip->B=mirvar(_MIPP_ 0);
        nres(_MIPP_ b,mr_mip->B);

    }
    mr_mip->coord=type;
    MR_OUT
    return;
}

epoint* epoint_init(_MIPDO_ )
{ /* initialise epoint to point at infinity. */
    epoint *p;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return NULL;

    MR_IN(96)

    p=mr_alloc(_MIPP_ 1,sizeof(epoint));
    p->X=mirvar(_MIPP_ 0);
    p->Y=mirvar(_MIPP_ 0);
    p->Z=NULL;            /* only initialise when written to */
    p->marker=MR_EPOINT_INFINITY;

    MR_OUT

    return p;
}

void epoint_free(_MIPD_ epoint *p)
{ /* clean up point */
    mirkill(_MIPP_ p->X);
    mirkill(_MIPP_ p->Y);
    if (p->Z!=NULL) mirkill(_MIPP_ p->Z);
    mr_free(_MIPP_ p);
}        

BOOL epoint_set(_MIPD_ big x,big y,int cb,epoint *p)
{ /* initialise a point on active ecurve            *
   * if x or y == NULL, set to point at infinity    *
   * if x==y, a y co-ordinate is calculated - if    *
   * possible - and cb suggests LSB 0/1  of y       *
   * (which "decompresses" y). Otherwise, check     *
   * validity of given (x,y) point, ignoring cb.    *
   * Returns TRUE for valid point, otherwise FALSE. */
  
    BOOL valid;

#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return FALSE;

    MR_IN(97)

    if (x==NULL || y==NULL)
    {
        convert(_MIPP_ 1,mr_mip->w1);
        nres(_MIPP_ mr_mip->w1,p->X);
        nres(_MIPP_ mr_mip->w1,p->Y);
        p->marker=MR_EPOINT_INFINITY;
        MR_OUT
        return TRUE;
    }

/* find x^3+Ax+B */
    nres(_MIPP_ x,p->X);
    nres_modmult(_MIPP_ p->X,p->X,mr_mip->w3);
    nres_modmult(_MIPP_ mr_mip->w3,p->X,mr_mip->w3);
    if (mr_abs(mr_mip->Asize)==MR_TOOBIG)
        nres_modmult(_MIPP_ p->X,mr_mip->A,mr_mip->w1);
    else
        nres_premult(_MIPP_ p->X,mr_mip->Asize,mr_mip->w1);
    nres_modadd(_MIPP_ mr_mip->w3,mr_mip->w1,mr_mip->w3);
    if (mr_abs(mr_mip->Bsize)==MR_TOOBIG)
        nres_modadd(_MIPP_ mr_mip->w3,mr_mip->B,mr_mip->w3);
    else
    {
        convert(_MIPP_ mr_mip->Bsize,mr_mip->w1);
        nres(_MIPP_ mr_mip->w1,mr_mip->w1);
        nres_modadd(_MIPP_ mr_mip->w3,mr_mip->w1,mr_mip->w3);
    }
    valid=FALSE;
    if (x!=y)
    { /* compare with y^2 */
        nres(_MIPP_ y,p->Y);
        nres_modmult(_MIPP_ p->Y,p->Y,mr_mip->w1);
        if (compare(mr_mip->w1,mr_mip->w3)==0) valid=TRUE;
    }
    else
    { /* no y supplied - calculate one. Find square root */

        valid=nres_sqroot(_MIPP_ mr_mip->w3,p->Y);

    /* check LSB - have we got the right root? */
        redc(_MIPP_ p->Y,mr_mip->w1);
        if (remain(_MIPP_ mr_mip->w1,2)!=cb) 
            mr_psub(_MIPP_ mr_mip->modulus,p->Y,p->Y);

    } 
    if (valid)
    {
        if (p->Z!=NULL)
        {
            convert(_MIPP_ 1,mr_mip->w1);
            nres(_MIPP_ mr_mip->w1,p->Z);
        }
        p->marker=MR_EPOINT_NORMALIZED;
        MR_OUT
        return TRUE;
    }

    MR_OUT
    return FALSE;
}

int epoint_get(_MIPD_ epoint* p,big x,big y)
{ /* Get point co-ordinates in affine, normal form       *
   * (converted from projective, Montgomery form)        *
   * if x==y, supplies x only. Return value is Least     *
   * Significant Bit of y (useful for point compression) */

    int lsb;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

    if (p->marker==MR_EPOINT_INFINITY)
    {
        zero(x);
        zero(y);
        return 0;
    }
    if (mr_mip->ERNUM) return 0;

    MR_IN(98)

    if (epoint_norm(_MIPP_ p)<0) 
    { /* not possible ! */
        MR_OUT
        return (-1);
    }

    redc(_MIPP_ p->X,x);
    redc(_MIPP_ p->Y,mr_mip->w1);

    if (x!=y) copy(mr_mip->w1,y);
    lsb=remain(_MIPP_ mr_mip->w1,2); 
    MR_OUT
    return lsb;
}

BOOL epoint_norm(_MIPD_ epoint *p)
{ /* normalise a point */
    
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->coord==MR_AFFINE) return TRUE;
    if (p->marker!=MR_EPOINT_GENERAL) return TRUE;

    if (mr_mip->ERNUM) return FALSE;

    MR_IN(117)

    convert(_MIPP_ 1,mr_mip->w8);
    nres(_MIPP_ mr_mip->w8,mr_mip->w8);  

    if (nres_moddiv(_MIPP_ mr_mip->w8,p->Z,mr_mip->w8)>1) /* 1/Z  */
    {
        MR_OUT
        return FALSE;
    }
    
    nres_modmult(_MIPP_ mr_mip->w8,mr_mip->w8,mr_mip->w1);/* 1/ZZ */
    nres_modmult(_MIPP_ p->X,mr_mip->w1,p->X);            /* X/ZZ */
    nres_modmult(_MIPP_ mr_mip->w1,mr_mip->w8,mr_mip->w1);/* 1/ZZZ */
    nres_modmult(_MIPP_ p->Y,mr_mip->w1,p->Y);            /* Y/ZZZ */

    convert(_MIPP_ 1,mr_mip->w8);
    nres(_MIPP_ mr_mip->w8,p->Z);
   
    p->marker=MR_EPOINT_NORMALIZED;
    MR_OUT
    return TRUE;
}

/*

static BOOL epoint_multi_norm(_MIPD_ int m,epoint **p)
{ 
    int i;
    big x[11],w[11];
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    for (i=0;i<m;i++) 
    {  
        w[i]=mirvar(_MIPP_ 0);
        x[i]=p[i]->Z;
    }
    if (!nres_multi_inverse(_MIPP_ m,x,w)) 
    {
       for (i=0;i<m;i++) mirkill(_MIPP_ w[i]); 
       return FALSE;
    }

    convert(_MIPP_ 1,mr_mip->w1);
    nres(_MIPP_ mr_mip->w1,mr_mip->w1);

    for (i=0;i<m;i++)
    {
        nres_modmult(_MIPP_ w[i],w[i],mr_mip->w2);      
        nres_modmult(_MIPP_ w[i],mr_mip->w2,mr_mip->w3);
        nres_modmult(_MIPP_ p[i]->X,mr_mip->w2,p[i]->X);
        nres_modmult(_MIPP_ p[i]->Y,mr_mip->w3,p[i]->Y);
        copy(mr_mip->w1,p[i]->Z);
        p[i]->marker=MR_EPOINT_NORMALIZED;
    }
    return TRUE;
}

*/

void ecurve_multi_add(_MIPD_ int m,epoint **x,epoint**w)
{ /* adds m points together simultaneously, w[i]+=x[i] */
    int i,*flag;
    big *A,*B,*C;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;    

    MR_IN(122)
    if (mr_mip->coord==MR_AFFINE)
    { /* this can be done faster */
        A=(big *)mr_alloc(_MIPP_ m,sizeof(big));
        B=(big *)mr_alloc(_MIPP_ m,sizeof(big));
        C=(big *)mr_alloc(_MIPP_ m,sizeof(big));
        flag=(int *)mr_alloc(_MIPP_ m,sizeof(int));

        convert(_MIPP_ 1,mr_mip->w3);
        nres(_MIPP_ mr_mip->w3,mr_mip->w3);    /* unity */
      
        for (i=0;i<m;i++)
        {
            A[i]=mirvar(_MIPP_ 0);
            B[i]=mirvar(_MIPP_ 0);
            C[i]=mirvar(_MIPP_ 0);
            flag[i]=0;
            if (compare(x[i]->X,w[i]->X)==0 && compare(x[i]->Y,w[i]->Y)==0) 
            { /* doubling */
                if (x[i]->marker==MR_EPOINT_INFINITY || size(x[i]->Y)==0)
                {
                    flag[i]=1;       /* result is infinity */
                    copy(mr_mip->w3,B[i]);
                    continue;    
                }
                nres_modmult(_MIPP_ x[i]->X,x[i]->X,A[i]);
                nres_premult(_MIPP_ A[i],3,A[i]);  /* 3*x^2 */
                if (mr_abs(mr_mip->Asize) == MR_TOOBIG)
                    nres_modadd(_MIPP_ A[i],mr_mip->A,A[i]);
                else
                {
                    convert(_MIPP_ mr_mip->Asize,mr_mip->w2);
                    nres(_MIPP_ mr_mip->w2,mr_mip->w2);
                    nres_modadd(_MIPP_ A[i],mr_mip->w2,A[i]);
                }                                       /* 3*x^2+A */
                nres_premult(_MIPP_ x[i]->Y,2,B[i]);
            }
            else
            {
                if (x[i]->marker==MR_EPOINT_INFINITY)
                {
                    flag[i]=2;              /* w[i] unchanged */
                    copy(mr_mip->w3,B[i]);
                    continue;
                }
                if (w[i]->marker==MR_EPOINT_INFINITY)
                {
                    flag[i]=3;              /* w[i] = x[i] */
                    copy(mr_mip->w3,B[i]);
                    continue;
                }
                nres_modsub(_MIPP_ x[i]->X,w[i]->X,B[i]);
                if (size(B[i])==0)
                { /* point at infinity */
                    flag[i]=1;       /* result is infinity */
                    copy(mr_mip->w3,B[i]);
                    continue;    
                }
                nres_modsub(_MIPP_ x[i]->Y,w[i]->Y,A[i]);
            }   
        }
        nres_multi_inverse(_MIPP_ m,B,C);  /* only one inversion needed */
        for (i=0;i<m;i++)
        {
            if (flag[i]==1)
            { /* point at infinity */
                epoint_set(_MIPP_ NULL,NULL,0,w[i]);
                continue;
            }
            if (flag[i]==2)
            {
                continue;
            }
            if (flag[i]==3)
            {
                epoint_copy(_MIPP_ x[i],w[i]);
                continue;
            }
            nres_modmult(_MIPP_ A[i],C[i],mr_mip->w8);

            nres_modmult(_MIPP_ mr_mip->w8,mr_mip->w8,mr_mip->w7); /* m^2 */
            nres_modsub(_MIPP_ mr_mip->w7,x[i]->X,mr_mip->w1);
            nres_modsub(_MIPP_ mr_mip->w1,w[i]->X,mr_mip->w1);
       
            nres_modsub(_MIPP_ w[i]->X,mr_mip->w1,mr_mip->w2);
            nres_modmult(_MIPP_ mr_mip->w2,mr_mip->w8,mr_mip->w2);
            nres_modsub(_MIPP_ mr_mip->w2,w[i]->Y,w[i]->Y);
            copy(mr_mip->w1,w[i]->X);
            w[i]->marker=MR_EPOINT_GENERAL;

            mr_free(_MIPP_ C[i]);
            mr_free(_MIPP_ B[i]);
            mr_free(_MIPP_ A[i]);
        }
        mr_free(_MIPP_ flag);
        mr_free(_MIPP_ C); mr_free(_MIPP_ B); mr_free(_MIPP_ A);
    }
    else
    { /* no speed-up */
        for (i=0;i<m;i++) ecurve_add(_MIPP_ x[i],w[i]);
    }
    MR_OUT
}

static void ecurve_double(_MIPD_ epoint *p)
{ /* double epoint on active ecurve */

#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (p->marker==MR_EPOINT_INFINITY) 
    { /* 2 times infinity == infinity ! */
        return;
    }

    if (mr_mip->coord==MR_AFFINE)
    {
        if (size(p->Y)==0) 
        { /* set to point at infinity */
            epoint_set(_MIPP_ NULL,NULL,0,p);
            return;
        }
        nres_modmult(_MIPP_ p->X,p->X,mr_mip->w8);    /* w8=x^2   */
        nres_premult(_MIPP_ mr_mip->w8,3,mr_mip->w8); /* w8=3*x^2 */
        if (mr_abs(mr_mip->Asize) == MR_TOOBIG)
            nres_modadd(_MIPP_ mr_mip->w8,mr_mip->A,mr_mip->w8);
        else
        {
            convert(_MIPP_ mr_mip->Asize,mr_mip->w2);
            nres(_MIPP_ mr_mip->w2,mr_mip->w2);
            nres_modadd(_MIPP_ mr_mip->w8,mr_mip->w2,mr_mip->w8);
        }                                     /* w8=3*x^2+A */
        nres_premult(_MIPP_ p->Y,2,mr_mip->w6);      /* w6=2y */
        nres_moddiv(_MIPP_ mr_mip->w8,mr_mip->w6,mr_mip->w8);  /* w8 is slope m */

        nres_modmult(_MIPP_ mr_mip->w8,mr_mip->w8,mr_mip->w7); /* w7=m^2 */
        nres_premult(_MIPP_ p->X,2,mr_mip->w1);
        nres_modsub(_MIPP_ mr_mip->w7,mr_mip->w1,mr_mip->w1); /* w1=m^2-2x */
        
        nres_modsub(_MIPP_ p->X,mr_mip->w1,mr_mip->w2);
        nres_modmult(_MIPP_ mr_mip->w2,mr_mip->w8,mr_mip->w2);
        nres_modsub(_MIPP_ mr_mip->w2,p->Y,p->Y);
        copy(mr_mip->w1,p->X);
        
        return;
    }

    if (p->Z==NULL)
    {
        p->Z=mirvar(_MIPP_ 1);
        nres(_MIPP_ p->Z,p->Z);
    }

    if (size(p->Y)==0)
    { /* set to point at infinity */
        epoint_set(_MIPP_ NULL,NULL,0,p);
        return;
    }
    convert(_MIPP_ 1,mr_mip->w1);
    if (p->marker==MR_EPOINT_NORMALIZED) nres(_MIPP_ mr_mip->w1,mr_mip->w2);
    else nres_modmult(_MIPP_ p->Z,p->Z,mr_mip->w2);
    if (mr_abs(mr_mip->Asize) < MR_TOOBIG)
    {
        if (mr_mip->Asize==(-3))
        { /* a is -3. Goody. */
            nres_modsub(_MIPP_ p->X,mr_mip->w2,mr_mip->w3);
            nres_modadd(_MIPP_ p->X,mr_mip->w2,mr_mip->w4);
            nres_modmult(_MIPP_ mr_mip->w3,mr_mip->w4,mr_mip->w3);
            nres_modadd(_MIPP_ mr_mip->w3,mr_mip->w3,mr_mip->w4);
            nres_modadd(_MIPP_ mr_mip->w4,mr_mip->w3,mr_mip->w4);
        }
        else
        { /* a is small */
            if (mr_mip->Asize!=0)
            { /* a is non zero! */
                nres_modmult(_MIPP_ mr_mip->w2,mr_mip->w2,mr_mip->w3);
                nres_premult(_MIPP_ mr_mip->w3,mr_mip->Asize,mr_mip->w3);
            }
            nres_modmult(_MIPP_ p->X,p->X,mr_mip->w1);
            nres_modadd(_MIPP_ mr_mip->w1,mr_mip->w1,mr_mip->w4);
            nres_modadd(_MIPP_ mr_mip->w4,mr_mip->w1,mr_mip->w4);
            if (mr_mip->Asize!=0) nres_modadd(_MIPP_ mr_mip->w4,mr_mip->w3,mr_mip->w4);
        }
    }
    else
    { /* a is not special */
        nres_modmult(_MIPP_ mr_mip->w2,mr_mip->w2,mr_mip->w3);
        nres_modmult(_MIPP_ mr_mip->w3,mr_mip->A,mr_mip->w3);
        nres_modmult(_MIPP_ p->X,p->X,mr_mip->w1);
        nres_modadd(_MIPP_ mr_mip->w1,mr_mip->w1,mr_mip->w4);
        nres_modadd(_MIPP_ mr_mip->w4,mr_mip->w1,mr_mip->w4);
        nres_modadd(_MIPP_ mr_mip->w4,mr_mip->w3,mr_mip->w4);        
    }
    nres_modmult(_MIPP_ p->Y,p->Z,p->Z);
    nres_modadd(_MIPP_ p->Z,p->Z,p->Z);
    nres_modmult(_MIPP_ p->Y,p->Y,mr_mip->w2);
    nres_modmult(_MIPP_ p->X,mr_mip->w2,mr_mip->w3);
    nres_modadd(_MIPP_ mr_mip->w3,mr_mip->w3,mr_mip->w3);
    nres_modadd(_MIPP_ mr_mip->w3,mr_mip->w3,mr_mip->w3);
    nres_modmult(_MIPP_ mr_mip->w4,mr_mip->w4,mr_mip->w1);
    nres_modadd(_MIPP_ mr_mip->w3,mr_mip->w3,p->X);
    nres_modsub(_MIPP_ mr_mip->w1,p->X,p->X);
    nres_modmult(_MIPP_ mr_mip->w2,mr_mip->w2,mr_mip->w2);
    nres_modadd(_MIPP_ mr_mip->w2,mr_mip->w2,mr_mip->w2);
    nres_modadd(_MIPP_ mr_mip->w2,mr_mip->w2,mr_mip->w2);
    nres_modadd(_MIPP_ mr_mip->w2,mr_mip->w2,mr_mip->w2);
    nres_modsub(_MIPP_ mr_mip->w3,p->X,mr_mip->w3);
    nres_modmult(_MIPP_ mr_mip->w3,mr_mip->w4,mr_mip->w3);
    nres_modsub(_MIPP_ mr_mip->w3,mr_mip->w2,p->Y);
  
    p->marker=MR_EPOINT_GENERAL;
}
   
static BOOL ecurve_padd(_MIPD_ epoint *p,epoint *pa)
{ /* primitive add two epoints on the active ecurve - pa+=p;   *
   * note that if p is normalized, its Z coordinate isn't used */
 
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->coord==MR_AFFINE)
    {
        nres_modsub(_MIPP_ p->Y,pa->Y,mr_mip->w8);
        nres_modsub(_MIPP_ p->X,pa->X,mr_mip->w6);
        if (size(mr_mip->w6)==0) 
        { /* divide by 0 */
            if (size(mr_mip->w8)==0) 
            { /* should have doubled ! */
                return FALSE; 
            }
            else
            { /* point at infinity */
                epoint_set(_MIPP_ NULL,NULL,0,pa);
                return TRUE;
            }
        }
        nres_moddiv(_MIPP_ mr_mip->w8,mr_mip->w6,mr_mip->w8);

        nres_modmult(_MIPP_ mr_mip->w8,mr_mip->w8,mr_mip->w7); /* w7=m^2 */
        nres_modsub(_MIPP_ mr_mip->w7,p->X,mr_mip->w1); /* w1=m^2-x1-x2 */
        nres_modsub(_MIPP_ mr_mip->w1,pa->X,mr_mip->w1);
        

        nres_modsub(_MIPP_ pa->X,mr_mip->w1,mr_mip->w2);
        nres_modmult(_MIPP_ mr_mip->w2,mr_mip->w8,mr_mip->w2);
        nres_modsub(_MIPP_ mr_mip->w2,pa->Y,pa->Y);
        copy(mr_mip->w1,pa->X);

        pa->marker=MR_EPOINT_NORMALIZED;
        return TRUE;
    }

    if (pa->Z==NULL) 
    {
        pa->Z=mirvar(_MIPP_ 1);
        nres(_MIPP_ pa->Z,pa->Z);
    }
    if (p->marker!=MR_EPOINT_NORMALIZED)    
    {
        nres_modmult(_MIPP_ p->Z,p->Z,mr_mip->w6);
        nres_modmult(_MIPP_ pa->X,mr_mip->w6,mr_mip->w1);
        nres_modmult(_MIPP_ mr_mip->w6,p->Z,mr_mip->w6);
        nres_modmult(_MIPP_ pa->Y,mr_mip->w6,mr_mip->w2);
    }
    else
    {
        copy(pa->X,mr_mip->w1);
        copy(pa->Y,mr_mip->w2);
    }
    nres_modmult(_MIPP_ pa->Z,pa->Z,mr_mip->w6);
    nres_modmult(_MIPP_ p->X,mr_mip->w6,mr_mip->w4);
    nres_modmult(_MIPP_ mr_mip->w6,pa->Z,mr_mip->w6);
    nres_modmult(_MIPP_ p->Y,mr_mip->w6,mr_mip->w5);
    nres_modsub(_MIPP_ mr_mip->w1,mr_mip->w4,mr_mip->w1);
    nres_modsub(_MIPP_ mr_mip->w2,mr_mip->w5,mr_mip->w2);

    if (size(mr_mip->w1)==0)
    {
        if (size(mr_mip->w2)==0)
        { /* should have doubled ! */
           return FALSE; 
        }
        else
        { /* point at infinity */
            epoint_set(_MIPP_ NULL,NULL,0,pa);
            return TRUE;
        }
    }
    nres_modadd(_MIPP_ mr_mip->w4,mr_mip->w4,mr_mip->w6);
    nres_modadd(_MIPP_ mr_mip->w1,mr_mip->w6,mr_mip->w4);
    nres_modadd(_MIPP_ mr_mip->w5,mr_mip->w5,mr_mip->w6);
    nres_modadd(_MIPP_ mr_mip->w2,mr_mip->w6,mr_mip->w5);
    
    if (p->marker!=MR_EPOINT_NORMALIZED)
    { 
        nres_modmult(_MIPP_ pa->Z,p->Z,mr_mip->w3);
        nres_modmult(_MIPP_ mr_mip->w3,mr_mip->w1,pa->Z);
    }
    else nres_modmult(_MIPP_ pa->Z,mr_mip->w1,pa->Z);
    nres_modmult(_MIPP_ mr_mip->w1,mr_mip->w1,mr_mip->w6);
    nres_modmult(_MIPP_ mr_mip->w1,mr_mip->w6,mr_mip->w1);
    nres_modmult(_MIPP_ mr_mip->w6,mr_mip->w4,mr_mip->w6);
    nres_modmult(_MIPP_ mr_mip->w2,mr_mip->w2,mr_mip->w4);

    nres_modsub(_MIPP_ mr_mip->w4,mr_mip->w6,pa->X);

    nres_modsub(_MIPP_ mr_mip->w6,pa->X,mr_mip->w6);
    nres_modsub(_MIPP_ mr_mip->w6,pa->X,mr_mip->w6);
    nres_modmult(_MIPP_ mr_mip->w2,mr_mip->w6,mr_mip->w2);
    nres_modmult(_MIPP_ mr_mip->w1,mr_mip->w5,mr_mip->w1);
    nres_modsub(_MIPP_ mr_mip->w2,mr_mip->w1,mr_mip->w5);

/* divide by 2 */
    if (subdiv(_MIPP_ mr_mip->w5,2,pa->Y)!=0)
    {
        mr_padd(_MIPP_ mr_mip->modulus,mr_mip->w5,pa->Y);
        subdiv(_MIPP_ pa->Y,2,pa->Y);
    }
    pa->marker=MR_EPOINT_GENERAL;
    return TRUE;                                      
}

void epoint_copy(_MIPD_ epoint *a,epoint *b)
{   
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (a==b) return;
    copy(a->X,b->X);
    copy(a->Y,b->Y);
    if (a->Z==NULL)
    {
         if (b->Z!=NULL)
         {
            convert(_MIPP_ 1,mr_mip->w2);
            nres(_MIPP_ mr_mip->w2,b->Z);
         }
    }
    else 
    {
        if (b->Z==NULL)
        {
           if (a->marker==MR_EPOINT_GENERAL) 
           {
               b->Z=mirvar(_MIPP_ 0);
               copy(a->Z,b->Z);
           } 
        }
        else copy(a->Z,b->Z);
    }
    b->marker=a->marker;
    return;
}

BOOL epoint_comp(_MIPD_ epoint *a,epoint *b)
{
    int ia,ib;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return FALSE;
    if (a==b) return TRUE;

    MR_IN(105)

    ia=epoint_get(_MIPP_ a,mr_mip->w9,mr_mip->w9);
    ib=epoint_get(_MIPP_ b,mr_mip->w10,mr_mip->w10);

    MR_OUT
    if (ia==ib && compare(mr_mip->w9,mr_mip->w10)==0) return TRUE;
    return FALSE;
}

void ecurve_add(_MIPD_ epoint *p,epoint *pa)
{  /* pa=pa+p; */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(94)

    if (p==pa) 
    {
        ecurve_double(_MIPP_ pa);
        MR_OUT
        return;
    }
    if (pa->marker==MR_EPOINT_INFINITY)
    {
        epoint_copy(_MIPP_ p,pa);
        MR_OUT 
        return;
    }
    if (p->marker==MR_EPOINT_INFINITY) 
    {
        MR_OUT
        return;
    }

    if (!ecurve_padd(_MIPP_ p,pa)) ecurve_double(_MIPP_ pa);
    MR_OUT
}

void epoint_negate(_MIPD_ epoint *p)
{ /* negate a point */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    if (p->marker==MR_EPOINT_INFINITY) return;

    MR_IN(121)
    mr_psub(_MIPP_ mr_mip->modulus,p->Y,p->Y);
    MR_OUT
}

void ecurve_sub(_MIPD_ epoint *p,epoint *pa)
{
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(104)

    if (p==pa)
    {
        epoint_set(_MIPP_ NULL,NULL,0,pa);
        MR_OUT
        return;
    } 
    if (p->marker==MR_EPOINT_INFINITY) 
    {
        MR_OUT
        return;
    }

    epoint_negate(_MIPP_ p);
    ecurve_add(_MIPP_ p,pa);
    epoint_negate(_MIPP_ p);

    MR_OUT
}

void ecurve_mult(_MIPD_ big e,epoint *pa,epoint *pt)
{ /* pt=e*pa; */
    int i,j,n,ch,ce,nb,nbs,nzs;
    epoint *p;
    epoint *table[11];
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(95)

    if (size(e)==0) 
    { /* multiplied by 0 */
        epoint_set(_MIPP_ NULL,NULL,0,pt);
        MR_OUT
        return;
    }
    copy(e,mr_mip->w9);
    epoint_norm(_MIPP_ pa);
    epoint_copy(_MIPP_ pa,pt);

    if (size(mr_mip->w9)<0)
    { /* pt = -pt */
        negate(mr_mip->w9,mr_mip->w9);
        epoint_negate(_MIPP_ pt);
    }

    if (size(mr_mip->w9)==1)
    { 
        MR_OUT
        return;
    }

    premult(_MIPP_ mr_mip->w9,3,mr_mip->w10);      /* h=3*e */
    p=epoint_init(_MIPPO_ );

    epoint_copy(_MIPP_ pt,p);

    if (mr_mip->base==mr_mip->base2)
    {
        table[0]=epoint_init(_MIPPO_ );
        epoint_copy(_MIPP_ p,table[0]);
        ecurve_double(_MIPP_ p);

        for (i=1;i<=10;i++)
        { /* precomputation */
            table[i]=epoint_init(_MIPPO_ );
            epoint_copy(_MIPP_ table[i-1],table[i]);
            ecurve_add(_MIPP_ p,table[i]);
        }

  /* note that normalising this table doesn't really help */
        nb=logb2(_MIPP_ mr_mip->w10);

        for (i=nb-2;i>=1;)
        { /* add/subtract */
            if (mr_mip->user!=NULL) (*mr_mip->user)();
            n=mr_naf_window(_MIPP_ mr_mip->w9,mr_mip->w10,i,&nbs,&nzs);
            for (j=0;j<nbs;j++)
                ecurve_double(_MIPP_ pt);
            if (n>0) ecurve_add(_MIPP_ table[n/2],pt);
            if (n<0) ecurve_sub(_MIPP_ table[(-n)/2],pt);
            i-=nbs;
            if (nzs)
            {
                for (j=0;j<nzs;j++) ecurve_double(_MIPP_ pt);
                i-=nzs;
            }
        }
        for (i=10;i>=0;i--) epoint_free(_MIPP_ table[i]);
    }
    else
    { 
        expint(_MIPP_ 2,logb2(_MIPP_ mr_mip->w10)-1,mr_mip->w11);
        mr_psub(_MIPP_ mr_mip->w10,mr_mip->w11,mr_mip->w10);
        subdiv(_MIPP_ mr_mip->w11,2,mr_mip->w11);
        while (size(mr_mip->w11) > 1)
        { /* add/subtract method */
            if (mr_mip->user!=NULL) (*mr_mip->user)();

            ecurve_double(_MIPP_ pt);
            ce=compare(mr_mip->w9,mr_mip->w11); /* e(i)=1? */
            ch=compare(mr_mip->w10,mr_mip->w11); /* h(i)=1? */
            if (ch>=0) 
            {  /* h(i)=1 */
                if (ce<0) ecurve_add(_MIPP_ p,pt);
                mr_psub(_MIPP_ mr_mip->w10,mr_mip->w11,mr_mip->w10);
            }
            if (ce>=0) 
            {  /* e(i)=1 */
                if (ch<0) ecurve_sub(_MIPP_ p,pt);
                mr_psub(_MIPP_ mr_mip->w9,mr_mip->w11,mr_mip->w9);  
            }
            subdiv(_MIPP_ mr_mip->w11,2,mr_mip->w11);
        }
    }
    epoint_free(_MIPP_ p);
    MR_OUT
}

void ecurve_multn(_MIPD_ int n,big *y,epoint **x,epoint *w)
{ /* pt=e[o]*p[0]+e[1]*p[1]+ .... e[n-1]*p[n-1]   */
    int i,j,k,m,nb,ea;
    epoint **G;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(113)

    m=1<<n;
    G=(epoint **)mr_alloc(_MIPP_ m,sizeof(epoint*));

    for (i=0,k=1;i<n;i++)
    {
        for (j=0; j < (1<<i) ;j++)
        {
            G[k]=epoint_init(_MIPPO_ );
            epoint_copy(_MIPP_ x[i],G[k]);
            if (j!=0) ecurve_add(_MIPP_ G[j],G[k]);
            k++;
        }
    }

    nb=0;
    for (j=0;j<n;j++) if ((k=logb2(_MIPP_ y[j])) > nb) nb=k;

    epoint_set(_MIPP_ NULL,NULL,0,w);            /* w=0 */
    
    if (mr_mip->base==mr_mip->base2)
    {
        for (i=nb-1;i>=0;i--)
        {
            if (mr_mip->user!=NULL) (*mr_mip->user)();
            ea=0;
            k=1;
            for (j=0;j<n;j++)
            {
                if (mr_testbit(_MIPP_ y[j],i)) ea+=k;
                k<<=1;
            }
            ecurve_double(_MIPP_ w);
            if (ea!=0) ecurve_add(_MIPP_ G[ea],w);
        }    
    }
    else mr_berror(_MIPP_ MR_ERR_NOT_SUPPORTED);

    for (i=1;i<m;i++) epoint_free(_MIPP_ G[i]);
    mr_free(_MIPP_ G);
    MR_OUT
}

void ecurve_mult2(_MIPD_ big e,epoint *p,big ea,epoint *pa,epoint *pt)
{ /* pt=e*p+ea*pa; */
    int e1,h1,e2,h2;
    epoint *p1,*p2,*ps,*pd;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(103)

    if (size(e)==0) 
    {
        ecurve_mult(_MIPP_ ea,pa,pt);
        MR_OUT
        return;
    }

    p2=epoint_init(_MIPPO_ );
    epoint_norm(_MIPP_ pa);
    epoint_copy(_MIPP_ pa,p2);
    copy(ea,mr_mip->w9);
    if (size(mr_mip->w9)<0)
    { /* p2 = -p2 */
        negate(mr_mip->w9,mr_mip->w9);
        epoint_negate(_MIPP_ p2);
    }
    premult(_MIPP_ mr_mip->w9,3,mr_mip->w10);      /* 3*ea */

    p1=epoint_init(_MIPPO_ );
    epoint_norm(_MIPP_ p);
    epoint_copy(_MIPP_ p,p1);
    copy(e,mr_mip->w12);
    if (size(mr_mip->w12)<0)
    { /* p1= -p1 */
        negate(mr_mip->w12,mr_mip->w12);
        epoint_negate(_MIPP_ p1);
    }
    premult(_MIPP_ mr_mip->w12,3,mr_mip->w13);    /* 3*e */

    epoint_set(_MIPP_ NULL,NULL,0,pt);            /* pt=0 */

    if (compare(mr_mip->w10,mr_mip->w13)>=0)
         expint(_MIPP_ 2,logb2(_MIPP_ mr_mip->w10)-1,mr_mip->w11);
    else expint(_MIPP_ 2,logb2(_MIPP_ mr_mip->w13)-1,mr_mip->w11);

    ps=epoint_init(_MIPPO_ );
    pd=epoint_init(_MIPPO_ );

    epoint_copy(_MIPP_ p1,ps);
    ecurve_add(_MIPP_ p2,ps);                    /* ps=p1+p2 */
    epoint_copy(_MIPP_ p1,pd);
    ecurve_sub(_MIPP_ p2,pd);                    /* pd=p1-p2 */
    epoint_norm(_MIPP_ ps);
    epoint_norm(_MIPP_ pd);
    while (size(mr_mip->w11) > 1)
    { /* add/subtract method */
        if (mr_mip->user!=NULL) (*mr_mip->user)();

        ecurve_double(_MIPP_ pt);

        e1=h1=e2=h2=0;
        if (compare(mr_mip->w9,mr_mip->w11)>=0)
        { /* e1(i)=1? */
            e2=1;  
            mr_psub(_MIPP_ mr_mip->w9,mr_mip->w11,mr_mip->w9);
        }
        if (compare(mr_mip->w10,mr_mip->w11)>=0)
        { /* h1(i)=1? */
            h2=1;  
            mr_psub(_MIPP_ mr_mip->w10,mr_mip->w11,mr_mip->w10);
        } 
        if (compare(mr_mip->w12,mr_mip->w11)>=0)
        { /* e2(i)=1? */
            e1=1;   
            mr_psub(_MIPP_ mr_mip->w12,mr_mip->w11,mr_mip->w12);
        }
        if (compare(mr_mip->w13,mr_mip->w11)>=0) 
        { /* h2(i)=1? */
            h1=1;  
            mr_psub(_MIPP_ mr_mip->w13,mr_mip->w11,mr_mip->w13);
        }

        if (e1!=h1)
        {
            if (e2==h2)
            {
                if (h1==1) ecurve_add(_MIPP_ p1,pt);
                else       ecurve_sub(_MIPP_ p1,pt);
            }
            else
            {
                if (h1==1)
                {
                    if (h2==1) ecurve_add(_MIPP_ ps,pt);
                    else       ecurve_add(_MIPP_ pd,pt);
                }
                else
                {
                    if (h2==1) ecurve_sub(_MIPP_ pd,pt);
                    else       ecurve_sub(_MIPP_ ps,pt);
                }
            }
        }
        else if (e2!=h2)
        {
            if (h2==1) ecurve_add(_MIPP_ p2,pt);
            else       ecurve_sub(_MIPP_ p2,pt);
        }

        subdiv(_MIPP_ mr_mip->w11,2,mr_mip->w11);
    }
    epoint_free(_MIPP_ p1);
    epoint_free(_MIPP_ p2);
    epoint_free(_MIPP_ ps);
    epoint_free(_MIPP_ pd);
    MR_OUT
}

