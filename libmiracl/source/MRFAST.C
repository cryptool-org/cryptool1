/*
 *   MIRACL fast fourier multiplication routine, using 3 prime method.
 *   mrfast.c  - only faster for very high precision multiplication
 *               of numbers > about 4096 bits  (see below)
 *   See "The Fast Fourier Transform in a Finite Field"  by J.M. Pollard,
 *   Mathematics of Computation, Vol. 25, No. 114, April 1971, pp365-374
 *   Also Knuth Vol. 2, Chapt. 4.3.3
 *
 *   Takes time preportional to 9+15N+9N.lg(N) to multiply two different 
 *   N digit numbers. This reduces to 6+18N+6N.lg(N) when squaring.
 *   The classic method takes N.N and N(N+1)/2 respectively
 *
 *   Fast Polynomial arithmetic 
 * 
 *   See "A New Polynomial Factorisation Algorithm and its Implementation"
 *   by Victor Shoup, Jl. Symbolic Computation 1996
 *   Uses FFT method for fast arithmetic of large degree polynomials
 *
 *   Copyright (c) 1988-1999 Shamus Software Ltd.
 */

#include <stdio.h>
#include <stdlib.h>
#include <miracl.h>

int mr_fft_init(_MIPD_ int logn,big m1,big m2,BOOL cr)
{ /* logn is number of bits, m1 and m2 are the largest elements 
     that will arise in each number to be multiplied */
    mr_small kk;
    int i,j,newn,pr;
    mr_utype p,proot;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

    newn=(1<<logn);
    mr_mip->check=OFF;
    multiply(_MIPP_ m1,m2,mr_mip->w5);
    premult(_MIPP_ mr_mip->w5,2*newn+1,mr_mip->w5);
    kk=((mr_small)1<<(MIRACL-2-logn));
    if (mr_mip->base!=0) while (kk*newn>mr_mip->base) kk>>=1;
    pr=0;
    while (size(mr_mip->w5)>0)
    { /* find out how many primes will be needed */
        do
        { 
            kk--;
            p=kk*newn+1;
        } while(spmd((mr_small)2,p-1,p)!=1);
        mr_sdiv(_MIPP_ mr_mip->w5,p,mr_mip->w5);
        pr++;
    }
   mr_mip->check=ON;
/* if nothing has changed, don't recalculate */
    if (logn<=mr_mip->logN && pr==mr_mip->nprimes) return pr;
    fft_reset(_MIPPO_ );


    mr_mip->prime=(mr_utype *)mr_alloc(_MIPP_ pr,sizeof(mr_utype));
    mr_mip->inverse=(mr_utype *)mr_alloc(_MIPP_ pr,sizeof(mr_utype));
    mr_mip->roots=(mr_utype**)mr_alloc(_MIPP_ pr,sizeof(mr_utype *));
    mr_mip->t= (mr_utype **)mr_alloc(_MIPP_ pr,sizeof(mr_utype *));
    mr_mip->cr=(mr_utype *)mr_alloc(_MIPP_ pr,sizeof(mr_utype));
    mr_mip->w=(mr_utype *)mr_alloc(_MIPP_ newn,sizeof(mr_utype));

    kk=((mr_small)1<<(MIRACL-2-logn));
    if (mr_mip->base!=0) while (kk*newn>mr_mip->base) kk>>=1;
    for (i=0;i<pr;i++)
    { /* find the primes again */
        mr_mip->roots[i]=(mr_utype *)mr_alloc(_MIPP_ newn,sizeof(mr_utype));
        mr_mip->t[i]=(mr_utype *)mr_alloc(_MIPP_ newn,sizeof(mr_utype));

        do
        { 
            kk--;
            p=kk*newn+1;
        } while(spmd((mr_small)2,p-1,p)!=1);

        proot=p-1;
        for (j=1;j<logn;j++) proot=sqrmp(proot,p); 
        mr_mip->roots[i][0]=proot;   /* build residue table */
        for (j=1;j<newn;j++) mr_mip->roots[i][j]=smul(mr_mip->roots[i][j-1],proot,p);
        mr_mip->inverse[i]=invers((mr_small)newn,p);
        mr_mip->prime[i]=p;
    }

    mr_mip->logN=logn;

    mr_mip->nprimes=pr;
/* set up chinese remainder structure */
    if (cr)
        if (!scrt_init(_MIPP_ &mr_mip->chin,pr,mr_mip->prime)) fft_reset(_MIPPO_ );
    return pr;
}

void fft_reset(_MIPDO_ )
{ /* reclaim any space used by FFT */
    int i;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

    if (mr_mip->degree!=0)
    { /* clear any precomputed tables */
        for (i=0;i<mr_mip->nprimes;i++)
        {
            mr_free(_MIPP_ mr_mip->s1[i]);
            mr_free(_MIPP_ mr_mip->s2[i]);
        }
        mr_free(_MIPP_ mr_mip->s1);
        mr_free(_MIPP_ mr_mip->s2);
        mr_mip->degree=0;
    }

    if (mr_mip->logN!=0)
    { /* clear away old stuff */
        for (i=0;i<mr_mip->nprimes;i++) 
        {
            mr_free(_MIPP_ mr_mip->roots[i]);
            mr_free(_MIPP_ mr_mip->t[i]);
        }
        mr_free(_MIPP_ mr_mip->w);
        mr_free(_MIPP_ mr_mip->cr);
        mr_free(_MIPP_ mr_mip->t);
        mr_free(_MIPP_ mr_mip->roots);
        mr_free(_MIPP_ mr_mip->inverse);
        mr_free(_MIPP_ mr_mip->prime);
        mr_mip->nprimes=0;
        mr_mip->logN=0;
    }
/* clear CRT structure */
    if (mr_mip->chin.NP!=0) scrt_end(_MIPP_ &mr_mip->chin);
}

void mr_dif_fft(_MIPD_ int logn,int pr,mr_utype *data)
{ /* decimate-in-frequency fourier transform */
    int mmax,m,j,k,istep,i,ii,jj,newn,offset;
    mr_utype w,temp,prime,*roots;
#ifdef MR_NOASM
    mr_large dble;
#endif
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    prime=mr_mip->prime[pr];
    roots=mr_mip->roots[pr];

    newn=(1<<logn);
    offset=(mr_mip->logN-logn);
    mmax=newn;
    for (k=0;k<logn;k++) {
        istep=mmax;
        mmax>>=1; 
        ii=newn;
        jj=newn/istep;
        ii-=jj;
        for (i=0;i<newn;i+=istep)
        { /* special case root=1 */ 
            j=i+mmax;
            temp=data[i]-data[j];
            if (temp<0) temp+=prime;
            data[i]+=data[j];
            if (data[i]>prime) data[i]-=prime;
            data[j]=temp;
        }
        for (m=1;m<mmax;m++) {

            w=roots[(ii<<offset)-1];
            ii-=jj;
#if INLINE_ASM == 3

/*  esi = i
    edi = j
    ebx = data
    edx = temp
    ecx = prime
*/    

        ASM mov   ecx,DWORD PTR prime
        ASM mov   ebx,DWORD PTR data
        ASM mov   esi,DWORD PTR m
    hop1:
        ASM cmp   esi,DWORD PTR newn
        ASM jge   hop0
        ASM mov   edi,esi
        ASM add   edi,DWORD PTR mmax

        ASM mov   edx,[ebx+4*esi]
        ASM add   edx,ecx
        ASM sub   edx,[ebx+4*edi]
        ASM mov   eax,[ebx+4*esi]
        ASM add   eax,[ebx+4*edi]
        ASM cmp   eax,ecx
        ASM jl    hop2
        ASM sub   eax,ecx
    hop2:
        ASM mov   [ebx+4*esi],eax 

        ASM mov   eax,DWORD PTR w      
        ASM mul   edx                  
        ASM div   ecx
        ASM mov   [ebx+4*edi],edx 

        ASM add   esi,DWORD PTR istep
        ASM jmp   hop1
    hop0:
        ASM nop
#endif
#if INLINE_ASM == 4
    ASM ("
           movl %0,%%ecx\n
           movl %1,%%ebx\n
           movl %2,%%esi\n
         hop1:\n
           cmpl %3,%%esi\n
           jge hop0\n
           movl %%esi,%%edi\n
           addl %4,%%edi\n

           movl (%%ebx,%%esi,4),%%edx\n
           addl %%ecx,%%edx\n
           subl (%%ebx,%%edi,4),%%edx\n
           movl (%%ebx,%%esi,4),%%eax\n
           addl (%%ebx,%%edi,4),%%eax\n
           cmpl %%ecx,%%eax\n
           jl hop2\n
           subl %%ecx,%%eax\n
         hop2:\n
           movl %%eax,(%%ebx,%%esi,4)\n
           movl %5,%%eax\n
           mull %%edx\n
           divl %%ecx\n
           movl %%edx,(%%ebx,%%edi,4)\n
           addl %6,%%esi\n
           jmp hop1\n
         hop0:\n
           nop\n
         "
         :
         : "g"(prime),"g"(data),"g"(m),"g"(newn),"g"(mmax),"g"(w),"g"(istep)
         : "eax","edi","esi","edi","ebx","ecx","edx","memory"
    );
#endif
#ifndef INLINE_ASM
            for (i=m;i<newn;i+=istep) {
                j=i+mmax;
                temp=prime+data[i]-data[j];
                data[i]+=data[j];
                if (data[i]>=prime) data[i]-=prime;

#ifdef MR_NOASM
                dble=(mr_large)w*temp;
                data[j]=(mr_utype)(dble-(mr_large)prime*(dble/prime));
#else
                muldiv(w,temp,(mr_small)0,prime,(mr_small *)&data[j]);
#endif
            }
#endif
        }
    }
}

void mr_dit_fft(_MIPD_ int logn,int pr,mr_utype *data)
{ /* decimate-in-time inverse fourier transform */
    int mmax,m,j,k,i,istep,ii,jj,newn,offset;
    mr_utype w,temp,prime,*roots;
#ifdef MR_NOASM
    mr_large dble;
#endif
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    prime=mr_mip->prime[pr];
    roots=mr_mip->roots[pr];
    offset=(mr_mip->logN-logn);

    newn=(1<<logn);
    mmax=1;
    for (k=0;k<logn;k++) {
        istep=(mmax<<1); 
        ii=0;
        jj=newn/istep;
        ii+=jj;
        for (i=0;i<newn;i+=istep)
        { /* special case root=1 */
            j=i+mmax;
            temp=data[j];
            data[j]=data[i]-temp;
            if (data[j]<0) data[j]+=prime;
            data[i]+=temp;
            if (data[i]>prime) data[i]-=prime;
        }
        for (m=1;m<mmax;m++) {
            w=roots[(ii<<offset)-1];
            ii+=jj;
#if INLINE_ASM == 3

/*  esi = i
    edi = j
    ebx = data
    edx = temp
    ecx = prime
*/    


        ASM mov   ebx,DWORD PTR data
        ASM mov   ecx,DWORD PTR prime
        ASM mov   esi,DWORD PTR m
hop4:
        ASM cmp   esi,DWORD PTR newn
        ASM jge   hop5
        ASM mov   edi,esi
        ASM add   edi,DWORD PTR mmax

        ASM mov   eax,[ebx+4*edi]
        ASM mul   DWORD PTR w
        ASM div   ecx

        ASM cmp   [ebx+4*esi],ecx
        ASM jl    hop3
        ASM sub   [ebx+4*esi],ecx
hop3:   
        ASM mov   eax,[ebx+4*esi]
        ASM add   [ebx+4*esi],edx
        ASM add   eax,ecx
        ASM sub   eax,edx
        ASM mov   [ebx+4*edi],eax

        ASM add   esi,DWORD PTR istep
        ASM jmp   hop4
hop5:
        ASM nop
#endif
#if INLINE_ASM == 4
    ASM ("
           movl %0,%%ebx\n
           movl %1,%%ecx\n
           movl %2,%%esi\n
         hop4:\n
           cmpl %3,%%esi\n
           jge hop5\n
           movl %%esi,%%edi\n
           addl %4,%%edi\n

           movl (%%ebx,%%edi,4),%%eax\n
           mull %5\n
           divl %%ecx\n

           cmpl %%ecx,(%%ebx,%%esi,4)\n
           jl hop3\n
           subl %%ecx,(%%ebx,%%esi,4)\n
         hop3:\n
           movl (%%ebx,%%esi,4),%%eax\n
           addl %%edx,(%%ebx,%%esi,4)\n
           addl %%ecx,%%eax\n
           subl %%edx,%%eax\n
           movl %%eax,(%%ebx,%%edi,4)\n

           addl %6,%%esi\n
           jmp hop4\n
         hop5:\n
            nop\n
         "
         :
         : "g"(data),"g"(prime),"g"(m),"g"(newn),"g"(mmax),"g"(w),"g"(istep)
         : "eax","edi","esi","edi","ebx","ecx","edx","memory"
        );
#endif
#ifndef INLINE_ASM
            for (i=m;i<newn;i+=istep) {
                j=i+mmax;
#ifdef MR_NOASM
                dble=(mr_large)w*data[j];
                temp=(mr_utype)(dble-(mr_large)prime*(dble/prime));
#else
                muldiv(w,data[j],(mr_small)0,prime,(mr_small *)&temp);
#endif
                if (data[i]>=prime) data[i]-=prime;
                data[j]=prime+data[i]-temp;
                data[i] += temp;
            }
#endif
        }
        mmax=istep;
    }
}

static void modxn_1(_MIPD_ int n,int deg,big *x)
{  /* set X (of degree deg) =X mod x^n-1 = X%x^n + X/x^n */
    int i;
    for (i=0;n+i<=deg;i++)
    {
        nres_modadd(_MIPP_ x[i],x[n+i],x[i]);
        zero(x[n+i]);
    }
}

BOOL mr_poly_rem(_MIPD_ int dg,big *G,big *R)
{ /* G is a polynomial of degree dg - G is overwritten */
    int i,j,newn,logn,np,n;
    mr_utype p,inv,fac;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    n=mr_mip->degree;  /* degree of modulus */
    if (n==0) return FALSE; /* the preset tables have been destroyed */
    np=mr_mip->nprimes;

    newn=1; logn=0;
    while (2*n>newn) { newn<<=1; logn++; }

    for (i=0;i<np;i++)
    {
        p=mr_mip->prime[i];
        for (j=n;j<=dg;j++)
            mr_mip->t[i][j-n]=mr_sdiv(_MIPP_ G[j],p,mr_mip->w1); 
        for (j=dg-n+1;j<newn;j++) mr_mip->t[i][j]=0;
        mr_dif_fft(_MIPP_ logn,i,mr_mip->t[i]);
        for (j=0;j<newn;j++)
            muldiv(mr_mip->t[i][j],mr_mip->s1[i][j],(mr_small)0,p,(mr_small *)&mr_mip->t[i][j]);
        mr_dit_fft(_MIPP_ logn,i,mr_mip->t[i]);
        inv=mr_mip->inverse[i];
        if (mr_mip->logN > logn)
        { /* adjust 1/N log p for N/2, N/4 etc */
            fac=(1<<(mr_mip->logN-logn));
            inv=smul(fac,inv,p);
        }
        for (j=0;j<n;j++)
            muldiv(mr_mip->t[i][j+n-1],inv,(mr_small)0,p,(mr_small *)&mr_mip->t[i][j+n-1]);
    }

    mr_mip->check=OFF;
    mr_shift(_MIPP_ mr_mip->modulus,(int)mr_mip->modulus[0],mr_mip->w6);
       /* w6 = N.R */
    for (j=0;j<n;j++)
    {
        for (i=0;i<np;i++)
            mr_mip->cr[i]=mr_mip->t[i][j+n-1];
        scrt(_MIPP_ &mr_mip->chin,mr_mip->cr,mr_mip->w7);
        divide(_MIPP_ mr_mip->w7,mr_mip->w6,mr_mip->w6);  /* R[j] may be too big for redc */ 
        redc(_MIPP_ mr_mip->w7,R[j]);
    }
    mr_mip->check=ON;

    for (i=0;i<np;i++)
    {
        p=mr_mip->prime[i];
        for (j=0;j<n;j++)
            mr_mip->t[i][j]=mr_sdiv(_MIPP_ R[j],p,mr_mip->w1);
        for (j=n;j<1+newn/2;j++) mr_mip->t[i][j]=0;

        mr_dif_fft(_MIPP_ logn-1,i,mr_mip->t[i]);  /* Note: Half size */
        for (j=0;j<newn/2;j++)
            muldiv(mr_mip->t[i][j],mr_mip->s2[i][j],(mr_small)0,p,(mr_small *)&mr_mip->t[i][j]);

        mr_dit_fft(_MIPP_ logn-1,i,mr_mip->t[i]);

        inv=mr_mip->inverse[i];
        if (mr_mip->logN > logn-1)
        {
            fac=(1<<(mr_mip->logN-logn+1));
            inv=smul(fac,inv,p);
        }
        for (j=0;j<n;j++)
            muldiv(mr_mip->t[i][j],inv,(mr_small)0,p,(mr_small *)&mr_mip->t[i][j]);

    }

    modxn_1(_MIPP_ newn/2,dg,G);    /* G=G mod 2^x - 1 */

    mr_mip->check=OFF;
    mr_shift(_MIPP_ mr_mip->modulus,(int)mr_mip->modulus[0],mr_mip->w6);
       /* w6 = N.R */
    for (j=0;j<n;j++)
    {
        for (i=0;i<np;i++)
            mr_mip->cr[i]=mr_mip->t[i][j];
        scrt(_MIPP_ &mr_mip->chin,mr_mip->cr,mr_mip->w7);
        divide(_MIPP_ mr_mip->w7,mr_mip->w6,mr_mip->w6);  /* R[j] may be too big for redc */ 
        redc(_MIPP_ mr_mip->w7,R[j]);
        nres_modsub(_MIPP_ G[j],R[j],R[j]);

    }
    mr_mip->check=ON;

    return TRUE;
}

void mr_polymod_set(_MIPD_ int n, big *rf,big *f)
{ /* n is degree of f */
    int i,j,np,newn,logn,degree;
    mr_utype p;
    big *F;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    degree=2*n;
    newn=1; logn=0;
    while (degree>newn) { newn<<=1; logn++; }

    if (mr_mip->degree!=0) 
    {
        for (i=0;i<mr_mip->nprimes;i++)
        {
            mr_free(_MIPP_ mr_mip->s1[i]);
            mr_free(_MIPP_ mr_mip->s2[i]);
        }
        mr_free(_MIPP_ mr_mip->s1);
        mr_free(_MIPP_ mr_mip->s2);
    }

    if (mr_mip->logN<logn)
        np=mr_fft_init(_MIPP_ logn,mr_mip->modulus,mr_mip->modulus,TRUE);
    else np=mr_mip->nprimes;

    mr_mip->degree=n;
    mr_mip->s1=(mr_utype **)mr_alloc(_MIPP_ np,sizeof(mr_utype *));
    mr_mip->s2=(mr_utype **)mr_alloc(_MIPP_ np,sizeof(mr_utype *));
    
    F=(big *)mr_alloc(_MIPP_ n+1,sizeof(big));
    for (i=0;i<=n;i++) 
    {
        F[i]=mirvar(_MIPP_ 0);
        if (f[i]!=NULL) copy(f[i],F[i]);
    }

    modxn_1(_MIPP_ newn/2,n,F);

    for (i=0;i<np;i++)
    {
      /* reserve space for precomputed tables.   */
      /* Note that s2 is half the size of s1     */
        mr_mip->s1[i]=(mr_utype *)mr_alloc(_MIPP_ newn,sizeof(mr_utype));
        mr_mip->s2[i]=(mr_utype *)mr_alloc(_MIPP_ 1+newn/2,sizeof(mr_utype));

        p=mr_mip->prime[i];
        for (j=0;j<n;j++)
        {
            if (rf[j]==NULL) mr_mip->s1[i][j]=0;
            else mr_mip->s1[i][j]=mr_sdiv(_MIPP_ rf[j],p,mr_mip->w1);
        }
        mr_dif_fft(_MIPP_ logn,i,mr_mip->s1[i]);
        
       for (j=0;j<=n;j++)
           mr_mip->s2[i][j]=mr_sdiv(_MIPP_ F[j],p,mr_mip->w1);
       mr_dif_fft(_MIPP_ logn-1,i,mr_mip->s2[i]);
    }
    for (i=0;i<=n;i++) mr_free(_MIPP_ F[i]);
    mr_free(_MIPP_ F);
}

int mr_ps_zzn_mul(_MIPD_ int deg,big *x,big *y,big *z)
{
    int i,j,newn,logn,np;
    mr_utype inv,p,fac;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    newn=1; logn=0;
    while (2*deg>newn) { newn <<=1; logn++; }
    if (mr_mip->logN<logn)
        np=mr_fft_init(_MIPP_ logn,mr_mip->modulus,mr_mip->modulus,TRUE);
    else np=mr_mip->nprimes;

    for (i=0;i<np;i++)
    {
        p=mr_mip->prime[i];
        for (j=0;j<deg;j++)
        {
            if (x[j]==NULL) mr_mip->w[j]=0;
            else mr_mip->w[j]=mr_sdiv(_MIPP_ x[j],p,mr_mip->w1);
        }
        for (j=deg;j<newn;j++) mr_mip->w[j]=0;

        mr_dif_fft(_MIPP_ logn,i,mr_mip->w);  
        for (j=0;j<deg;j++)
        {
            if (y[j]==NULL) mr_mip->t[i][j]=0;
            else mr_mip->t[i][j]=mr_sdiv(_MIPP_ y[j],p,mr_mip->w1);
        }  
        for (j=deg;j<newn;j++) mr_mip->t[i][j]=0;
        mr_dif_fft(_MIPP_ logn,i,mr_mip->t[i]);
  /* multiply FFTs */
        for (j=0;j<newn;j++)
            muldiv(mr_mip->w[j],mr_mip->t[i][j],(mr_small)0,p,(mr_small *)&mr_mip->t[i][j]);
        mr_dit_fft(_MIPP_ logn,i,mr_mip->t[i]);           /* np*N*lgN */

        inv=mr_mip->inverse[i];
        if (mr_mip->logN > logn)
        {
            fac=(1<<(mr_mip->logN-logn));
            inv=smul(fac,inv,p);
        }
        for (j=0;j<deg;j++)                   /* np*N */
            muldiv(mr_mip->t[i][j],inv,(mr_small)0,p,(mr_small *)&mr_mip->t[i][j]);
    }
    mr_mip->check=OFF;
    mr_shift(_MIPP_ mr_mip->modulus,(int)mr_mip->modulus[0],mr_mip->w6);
    for (j=0;j<deg;j++)
    {
        for (i=0;i<np;i++)
            mr_mip->cr[i]=mr_mip->t[i][j];
        scrt(_MIPP_ &mr_mip->chin,mr_mip->cr,mr_mip->w7);
        divide(_MIPP_ mr_mip->w7,mr_mip->w6,mr_mip->w6);
        redc(_MIPP_ mr_mip->w7,z[j]);
    }
    mr_mip->check=ON;
    return np;
}

int mr_ps_big_mul(_MIPD_ int deg,big *x,big *y,big *z)
{ /* Multiply two power series with large integer parameters */
    int i,j,newn,logn,np;
    mr_utype inv,p,fac;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    newn=1; logn=0;
    while (2*deg>newn) { newn <<=1; logn++; }

    zero(mr_mip->w2);
    zero(mr_mip->w4);

/* find biggest element in each series */
    for (i=0;i<deg;i++)
    {
        if (x[i]!=NULL) 
        {
            absol(x[i],mr_mip->w3);
            if (compare(mr_mip->w3,mr_mip->w2)>0) copy(mr_mip->w3,mr_mip->w2);
        }
        if (y[i]!=NULL)
        {
            absol(y[i],mr_mip->w3);
            if (compare(mr_mip->w3,mr_mip->w4)>0) copy(mr_mip->w3,mr_mip->w4);
        }
    }
    premult(_MIPP_ mr_mip->w4,2,mr_mip->w4);     /* range is +ve and -ve */
                                          /* so extra factor of 2 included */

    np=mr_fft_init(_MIPP_ logn,mr_mip->w4,mr_mip->w2,TRUE); 
    convert(_MIPP_ 1,mr_mip->w3);
/* compute coefficients modulo fft primes */    
    for (i=0;i<np;i++)
    {
        p=mr_mip->prime[i];
        mr_pmul(_MIPP_ mr_mip->w3,p,mr_mip->w3); 
        for (j=0;j<deg;j++)
        {
            if (x[j]==NULL) mr_mip->w[j]=0;
            else 
            {
                if (size(x[j])>=0)
                {
                    copy(x[j],mr_mip->w1);
                    mr_mip->w[j]=mr_sdiv(_MIPP_ mr_mip->w1,p,mr_mip->w1);
                }
                else
                {
                    negate(x[j],mr_mip->w1);
                    mr_mip->w[j]=p-mr_sdiv(_MIPP_ mr_mip->w1,p,mr_mip->w1);
                }
            }
        }
        for (j=deg;j<newn;j++) mr_mip->w[j]=0;

        mr_dif_fft(_MIPP_ logn,i,mr_mip->w);  
        for (j=0;j<deg;j++)
        {
            if (y[j]==NULL) mr_mip->t[i][j]=0;
            else 
            {
                if (size(y[j])>=0)
                {
                    copy(y[j],mr_mip->w1);
                    mr_mip->t[i][j]=mr_sdiv(_MIPP_ mr_mip->w1,p,mr_mip->w1);
                }
                else
                {
                    negate(y[j],mr_mip->w1);
                    mr_mip->t[i][j]=p-mr_sdiv(_MIPP_ mr_mip->w1,p,mr_mip->w1);
                }
            }
        }  
        for (j=deg;j<newn;j++) mr_mip->t[i][j]=0;
        mr_dif_fft(_MIPP_ logn,i,mr_mip->t[i]);
  /* multiply FFTs */
        for (j=0;j<newn;j++)
            muldiv(mr_mip->w[j],mr_mip->t[i][j],(mr_small)0,p,(mr_small *)&mr_mip->t[i][j]);
        mr_dit_fft(_MIPP_ logn,i,mr_mip->t[i]);           /* np*N*lgN */

        inv=mr_mip->inverse[i];
        if (mr_mip->logN > logn)
        {
            fac=(1<<(mr_mip->logN-logn));
            inv=smul(fac,inv,p);
        }
        for (j=0;j<deg;j++)                   /* np*N */
            muldiv(mr_mip->t[i][j],inv,(mr_small)0,p,(mr_small *)&mr_mip->t[i][j]);
    }
  /* w3 is product of chinese primes */
    decr(_MIPP_ mr_mip->w3,1,mr_mip->w4);
    subdiv(_MIPP_ mr_mip->w4,2,mr_mip->w4); /* find mid-point of range */
  
    for (j=0;j<deg;j++)
    {
        for (i=0;i<np;i++)
            mr_mip->cr[i]=mr_mip->t[i][j];
        scrt(_MIPP_ &mr_mip->chin,mr_mip->cr,z[j]); /* N*3*np*np/2  */
        if (compare(z[j],mr_mip->w4)>=0)
        { /* In higher half of range, so number is negative */
            subtract(_MIPP_ mr_mip->w3,z[j],z[j]);
            negate(z[j],z[j]);
        }
    }            /* np*np*N/4 */
    return np;
}

int mr_poly_mul(_MIPD_ int degx,big *x,int degy,big *y,big *z)
{ /*  Multiply two polynomials. The big arrays are of size degree */
    int i,j,newn,logn,np,degree;
    mr_utype inv,p,fac;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    degree=degx+degy;
    if (x==y) 
    {
        mr_poly_sqr(_MIPP_ degx,x,z);
        return degree;
    }
    newn=1; logn=0;
    while (degree+1>newn) { newn<<=1; logn++; }

    if (mr_mip->logN<logn)
        np=mr_fft_init(_MIPP_ logn,mr_mip->modulus,mr_mip->modulus,TRUE);
    else np=mr_mip->nprimes;

/* compute coefficients modulo fft primes */    
    for (i=0;i<np;i++)
    {                                              
        p=mr_mip->prime[i];
        for (j=0;j<=degx;j++)
        {
            if (x[j]==NULL) mr_mip->w[j]=0;
            else mr_mip->w[j]=mr_sdiv(_MIPP_ x[j],p,mr_mip->w1);      /* np*np*N/2 muldivs */
        }
        for (j=degx+1;j<newn;j++) mr_mip->w[j]=0;
        mr_dif_fft(_MIPP_ logn,i,mr_mip->w);              /* np*N*lgN     */

        for (j=0;j<=degy;j++)
        {
            if (y[j]==NULL) mr_mip->t[i][j]=0;
            else mr_mip->t[i][j]=mr_sdiv(_MIPP_ y[j],p,mr_mip->w1);   /* np*np*N/2   */
        }
        for (j=degy+1;j<newn;j++) mr_mip->t[i][j]=0;
        mr_dif_fft(_MIPP_ logn,i,mr_mip->t[i]);           /* np*N*lgN */

   /* multiply FFTs */
        for (j=0;j<newn;j++)                       /* np*N */
            muldiv(mr_mip->w[j],mr_mip->t[i][j],(mr_small)0,p,(mr_small *)&mr_mip->t[i][j]);
        mr_dit_fft(_MIPP_ logn,i,mr_mip->t[i]);           /* np*N*lgN */

        inv=mr_mip->inverse[i];
        if (mr_mip->logN > logn)
        {
            fac=(1<<(mr_mip->logN-logn));
            inv=smul(fac,inv,p);
        }
        for (j=0;j<=degree;j++)                   /* np*N */
            muldiv(mr_mip->t[i][j],inv,(mr_small)0,p,(mr_small *)&mr_mip->t[i][j]);
    }
    mr_mip->check=OFF;
    mr_shift(_MIPP_ mr_mip->modulus,(int)mr_mip->modulus[0],mr_mip->w6);
       /* w6 = N.R */
    for (j=0;j<=degree;j++)
    {
        for (i=0;i<np;i++)
            mr_mip->cr[i]=mr_mip->t[i][j];
        scrt(_MIPP_ &mr_mip->chin,mr_mip->cr,mr_mip->w7); /* N*3*np*np/2 */
        divide(_MIPP_ mr_mip->w7,mr_mip->w6,mr_mip->w6);  /* z[j] may be too big for redc */ 
        redc(_MIPP_ mr_mip->w7,z[j]);
    }                                        /* np*np*N/4 */
    mr_mip->check=ON;
    return degree;
}

int mr_poly_sqr(_MIPD_ int degx,big *x,big *z)
{ /*  Multiply two polynomials. The big arrays are of size degree */
    int i,j,newn,logn,np,degree;
    mr_utype inv,p,fac;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    degree=2*degx;
    newn=1; logn=0;
    while (degree+1>newn) { newn<<=1; logn++; }

    if (mr_mip->logN<logn)
        np=mr_fft_init(_MIPP_ logn,mr_mip->modulus,mr_mip->modulus,TRUE);
    else np=mr_mip->nprimes;

/* compute coefficients modulo fft primes */    
    for (i=0;i<np;i++)
    {
        p=mr_mip->prime[i];
        for (j=0;j<=degx;j++)
        {
            if (x[j]==NULL) mr_mip->t[i][j]=0;
            else mr_mip->t[i][j]=mr_sdiv(_MIPP_ x[j],p,mr_mip->w1);
        }
        for (j=degx+1;j<newn;j++) mr_mip->t[i][j]=0;
        mr_dif_fft(_MIPP_ logn,i,mr_mip->t[i]);

   /* multiply FFTs */
        for (j=0;j<newn;j++)
            muldiv(mr_mip->t[i][j],mr_mip->t[i][j],(mr_small)0,p,(mr_small *)&mr_mip->t[i][j]);
        mr_dit_fft(_MIPP_ logn,i,mr_mip->t[i]);

        inv=mr_mip->inverse[i];
        if (mr_mip->logN > logn)
        { /* adjust 1/N log p for smaller N  */
            fac=(1<<(mr_mip->logN-logn));
            inv=smul(fac,inv,p);
        }
        for (j=0;j<=degree;j++)
            muldiv(mr_mip->t[i][j],inv,(mr_small)0,p,(mr_small *)&mr_mip->t[i][j]);
    }
    mr_mip->check=OFF;
    mr_shift(_MIPP_ mr_mip->modulus,(int)mr_mip->modulus[0],mr_mip->w6);
       /* w6 = N.R */
    for (j=0;j<=degree;j++)
    { /* apply CRT to each column */
        for (i=0;i<np;i++)
            mr_mip->cr[i]=mr_mip->t[i][j];

        scrt(_MIPP_ &mr_mip->chin,mr_mip->cr,mr_mip->w7);
        divide(_MIPP_ mr_mip->w7,mr_mip->w6,mr_mip->w6);  /* z[j] may be too big for redc */ 
        redc(_MIPP_ mr_mip->w7,z[j]);
    }
    mr_mip->check=ON;

    return degree;
}

static BOOL init_it(_MIPD_ int logn)
{ /* find primes, table of roots, inverses etc for new N */
    mr_small x[3];
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
   
    x[0]=2; x[1]=0; x[2]=1; 
    if (mr_fft_init(_MIPP_ logn,x,x,FALSE)!=3) return FALSE;

    mr_mip->const1=invers(mr_mip->prime[0],mr_mip->prime[1]);
    mr_mip->const2=invers(mr_mip->prime[0],mr_mip->prime[2]);
    mr_mip->const3=invers(mr_mip->prime[1],mr_mip->prime[2]);
    if (mr_mip->base==0) mr_mip->msw=muldvd(mr_mip->prime[0],mr_mip->prime[1],(mr_small)0,&mr_mip->lsw);
    else                 mr_mip->msw=muldiv(mr_mip->prime[0],mr_mip->prime[1],(mr_small)0,mr_mip->base,&mr_mip->lsw);
    mr_mip->logN=logn;
    return TRUE;
}

void fft_mult(_MIPD_ big x,big y,big z)
{ /* "fast" O(n.log n) multiplication */
    int i,pr,xl,yl,zl,newn,logn;
    mr_small v1,v2,v3,ic,c1,c2,sz,p,fac,inv;
    mr_utype *work,*dptr,*d0,*d1,*d2,t;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    if (y[0]==0 || x[0]==0) 
    {
        zero(z);
        return;
    }

    MR_IN(72)

    if (mr_notint(x) || mr_notint(y))
    {
        mr_berror(_MIPP_ MR_ERR_INT_OP);
        MR_OUT
        return;
    }  
    sz=((x[0]&MR_MSBIT)^(y[0]&MR_MSBIT));
    xl=(int)(x[0]&MR_OBITS);
    yl=(int)(y[0]&MR_OBITS);
    zl=xl+yl;
    if (xl<256 || yl<256)
    { /* not worth it! */
        multiply(_MIPP_ x,y,z);
        MR_OUT
        return;
    }
    if (zl>mr_mip->nib && mr_mip->check)
    {
        mr_berror(_MIPP_ MR_ERR_OVERFLOW);
        MR_OUT
        return;
    }
    newn=1; logn=0;
    while (zl>newn) { newn<<=1; logn++;}
    if (logn>mr_mip->logN)     /*  2^(N+1) settings can be used for 2^N */
    { /* numbers too big for current settings */
        if (!init_it(_MIPP_ logn)) 
        {
            mr_berror(_MIPP_ MR_ERR_OUT_OF_MEMORY);
            MR_OUT
            return;
        }
    }
    if (newn>2*mr_mip->nib)
    {
        mr_berror(_MIPP_ MR_ERR_OVERFLOW);
        MR_OUT
        return;
    }

    d0=mr_mip->t[0]; d1=mr_mip->t[1]; d2=mr_mip->t[2];
    work=mr_mip->w;

    fac=(1<<(mr_mip->logN-logn));
    
    for (pr=0;pr<3;pr++)
    { /* multiply mod each prime */
        p=mr_mip->prime[pr];
        inv=mr_mip->inverse[pr];  
        if (fac!=1) inv=smul(fac,inv,p);  /* adjust 1/N mod p */
        
        dptr=mr_mip->t[pr];
        for (i=1;i<=xl;i++) dptr[i-1]=x[i]%p;
        for (i=xl;i<newn;i++) dptr[i]=0;

        mr_dif_fft(_MIPP_ logn,pr,dptr);
        if (x!=y)
        {
            for (i=1;i<=yl;i++) work[i-1]=y[i]%p;
            for (i=yl;i<newn;i++) work[i]=0;
            mr_dif_fft(_MIPP_ logn,pr,work);
        }
        else work=dptr;
        for (i=0;i<newn;i++)
        {  /* "multiply" Fourier transforms */
            muldiv(dptr[i],work[i],(mr_small)0,p,(mr_small *)&dptr[i]);
        }
        mr_dit_fft(_MIPP_ logn,pr,dptr);

        for (i=0;i<newn;i++)
        {  /* convert to mixed radix form     *
            * using chinese remainder thereom *
            * but first multiply by 1/N mod p */
            muldiv(dptr[i],inv,(mr_small)0,p,(mr_small *)&dptr[i]); 
            if (pr==1)
            {
                t=d1[i]-d0[i];
                while (t<0) t+=mr_mip->prime[1];
                muldiv(t,mr_mip->const1,(mr_small)0,mr_mip->prime[1],(mr_small *)&d1[i]);
            } 
            if (pr==2)
            {
                t=d2[i]-d0[i];
                while (t<0) t+=mr_mip->prime[2];
                muldiv(t,mr_mip->const2,(mr_small)0,mr_mip->prime[2],(mr_small *)&t);
                t-=d1[i];
                while (t<0) t+=mr_mip->prime[2];
                muldiv(t,mr_mip->const3,(mr_small)0,mr_mip->prime[2],(mr_small *)&d2[i]);
            }
        }    
    }

    zero(z);
    c1=c2=0;
    if (mr_mip->base==0) for (i=0;i<zl;i++)
    { /* propagate carries */
        v1=d0[i];
        v2=d1[i];
        v3=d2[i];
        v2=muldvd(v2,mr_mip->prime[0],v1,&v1);
        c1+=v1;
        if (c1<v1) v2++;
        ic=c2+muldvd(mr_mip->lsw,v3,c1,&z[i+1]);
        c2=muldvd(mr_mip->msw,v3,ic,&c1);
        c1+=v2;
        if (c1<v2) c2++;
    }
    else for (i=0;i<zl;i++)
    { /* propagate carries */
        v1=d0[i];
        v2=d1[i];
        v3=d2[i];
        v2=muldiv(v2,mr_mip->prime[0],v1+c1,mr_mip->base,&v1);
        ic=c2+muldiv(mr_mip->lsw,v3,v1,mr_mip->base,&z[i+1]);
        c2=muldiv(mr_mip->msw,v3,v2+ic,mr_mip->base,&c1);
    }
    z[0]=(sz|zl); /* set length and sign of result */
    mr_lzero(z);
    MR_OUT
}

/*
main()
{
    big x,y,z,w;
    int i,j,k;
    mirsys(500,0);
    x=mirvar(0);
    y=mirvar(0);
    z=mirvar(0);
    w=mirvar(0);

    bigdig(64*10,2,x);
    bigdig(64*10,2,y);
    multiply(x,y,z);
    cotnum(z,stdout);

    fft_mult(x,y,w);
    cotnum(w,stdout);
    if (compare(z,w)!=0) printf("Problems\n");



    bigdig(32*10,2,x);
    bigdig(32*10,2,y);
    multiply(x,y,z);
    cotnum(z,stdout);

    fft_mult(x,y,w);
    cotnum(w,stdout);
    if (compare(z,w)!=0) printf("Problems\n");

    bigdig(16*10,2,x);
    bigdig(16*10,2,y);
    multiply(x,y,z);
    cotnum(z,stdout);

    fft_mult(x,y,w);
    cotnum(w,stdout);
    if (compare(z,w)!=0) printf("Problems\n");
}
*/

