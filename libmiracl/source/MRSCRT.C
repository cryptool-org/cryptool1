/*
 *   MIRACL Chinese Remainder Thereom routines (for use with small moduli) 
 *   mrscrt.c
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <stdio.h>
#include <stdlib.h>
#include <miracl.h>

BOOL scrt_init(_MIPD_ small_chinese *c,int r,mr_utype *moduli)
{ /* calculate CRT constants - returns FALSE if there is a problem */
    int i,j,k;
    if (r<1) return FALSE;
    if (r==1)
    {
        c->NP=1;
        c->M=(mr_utype *)mr_alloc(_MIPP_ r,sizeof(mr_utype));
        if (c->M==NULL) return FALSE;
        c->M[0]=moduli[0];
        return TRUE;
    }
    for (i=0;i<r;i++) if (moduli[i]<2) return FALSE;
    c->M=(mr_utype *)mr_alloc(_MIPP_ r,sizeof(mr_utype));
    if (c->M==NULL) return FALSE;
    c->C=(mr_utype *)mr_alloc(_MIPP_ r*(r-1)/2,sizeof(mr_utype));
    if (c->C==NULL)
    { /* no room */
        mr_free(_MIPP_ c->M);
        return FALSE;
    }
    c->V=(mr_utype *)mr_alloc(_MIPP_ r,sizeof(mr_utype));
    if (c->V==NULL)
    { /* no room */
        mr_free(_MIPP_ c->M);
        mr_free(_MIPP_ c->C);
        return FALSE;
    }
    for (k=0,i=0;i<r;i++)
    {
        c->M[i]=moduli[i];
        for (j=0;j<i;j++,k++)
            c->C[k]=invers(c->M[j],c->M[i]);
    }
    c->NP=r;
    return TRUE;
}

void scrt(_MIPD_ small_chinese *c,mr_utype *u,big x)
{ /* Chinese Remainder Thereom                  *
   * Calculate x given remainders u[i] mod M[i] */
    int i,j,k;
    mr_utype *V,*C,*M;
    mr_small t;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    V=c->V;
    C=c->C;
    M=c->M;
    if (c->NP<1) return;
    if (c->NP==1)
    {
        t=smul(1,u[0],M[0]);
        convert(_MIPP_ 1,mr_mip->w5);
        mr_pmul(_MIPP_ mr_mip->w5,t,x);
        return;
    }
    V[0]=u[0];
    for (k=0,i=1;i<c->NP;i++)
    { /* Knuth P. 274 */
        V[i]=u[i] - V[0];
        V[i]=smul(V[i],C[k],M[i]);
        k++;

#if INLINE_ASM == 3

        ASM mov ebx,DWORD PTR V
        ASM mov esi,DWORD PTR M
        ASM mov edi,DWORD PTR C
        ASM mov ecx,1
        ASM mov edx,DWORD PTR i
        ASM mov esi,[esi+4*edx]
     s1:
        ASM cmp ecx,edx
        ASM jge s2

        ASM mov eax,[ebx+4*edx]
        ASM push edx

        ASM sub eax,[ebx+4*ecx]
        ASM cdq
        ASM idiv esi
        ASM mov eax,edx
        ASM add eax,esi

        ASM mov edx,DWORD PTR k
        ASM mul DWORD PTR [edi+4*edx]
        ASM div esi

        ASM mov eax,edx

        ASM pop edx
        ASM mov [ebx+4*edx],eax   
        ASM inc DWORD PTR k
        ASM inc ecx
        ASM jmp s1
     s2:
        ASM nop

#endif

#if INLINE_ASM == 4
    ASM ("
           movl %0,%%ebx\n
           movl %1,%%esi\n
           movl %2,%%edi\n
           movl $1,%%ecx\n
           movl %3,%%edx\n
           movl (%%esi,%%edx,4),%%esi\n
         s1:\n
           cmpl %%edx,%%ecx\n
           jge s2\n

           movl (%%ebx,%%edx,4),%%eax\n
           pushl %%edx\n

           subl (%%ebx,%%ecx,4),%%eax\n

           cltd \n
           idivl %%esi\n
           movl %%edx,%%eax\n
           addl %%esi,%%eax\n

           movl %4,%%edx\n
           mull (%%edi,%%edx,4)\n
           divl %%esi\n

           movl %%edx,%%eax\n

           popl %%edx\n
           movl %%eax,(%%ebx,%%edx,4)\n
           incl %4\n
           incl %%ecx\n
           jmp s1\n
         s2:\n
           nop\n
         "
         :
         :"g"(V),"g"(M),"g"(C),"g"(i),"g"(k)
         :"eax","ebx","ecx","edx","esi","edi","memory"
        );
#endif

#ifndef INLINE_ASM
        for (j=1;j<i;j++,k++)
        {
            V[i]-=V[j];
            V[i]=smul(V[i],C[k],M[i]);
        }
#endif
    }

    convert(_MIPP_ 1,x);
    mr_pmul(_MIPP_ x,(mr_small)V[0],x);
    convert(_MIPP_ 1,mr_mip->w5);
    for (j=1;j<c->NP;j++)
    {
        mr_pmul(_MIPP_ mr_mip->w5,(mr_small)(M[j-1]),mr_mip->w5);
        mr_pmul(_MIPP_ mr_mip->w5,(mr_small)(V[j]),mr_mip->w0);
        mr_padd(_MIPP_ x,mr_mip->w0,x);         
    } 
}

void scrt_end(_MIPD_ small_chinese *c)
{ /* clean up after CRT */
    if (c->NP<1) 
    {
        c->NP=0;
        return;
    }
    if (c->NP==1)
    {
        mr_free(_MIPP_ c->M);
        c->NP=0;
        return;
    }
    mr_free(_MIPP_ c->M);
    mr_free(_MIPP_ c->V);
    mr_free(_MIPP_ c->C);
    c->NP=0;
}

