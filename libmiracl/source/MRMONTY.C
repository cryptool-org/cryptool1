/*
 *   MIRACL Montgomery's method for modular arithmetic without division.
 *   mrmonty.c 
 *
 *   Programs to implement Montgomery's method
 *   See "Modular Multiplication Without Trial Division", Math. Comp. 
 *   Vol 44, Number 170, April 1985, Pages 519-521
 *   NOTE - there is an important correction to this paper mentioned as a
 *   footnote in  "Speeding the Pollard and Elliptic Curve Methods", 
 *   Math. Comput., Vol. 48, January 1987, 243-264
 *
 *   The advantage of this approach is that no division required in order
 *   to compute a modular reduction - useful if division is slow
 *   e.g. on a SPARC processor, or a DSP.
 *
 *   NOTE:- nres_modmult() *might* use mr_mip->w7
 *   
 *   The disadvantage is that numbers must first be converted to an internal
 *   "n-residue" form.
 *
 *   Copyright (c) 1988-1999 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

#define mr_abs(x)  ((x)<0? (-(x)) : (x))

mr_small prepare_monty(_MIPD_ big n)
{ /* prepare Montgomery modulus */ 
    mr_small nn[2];
#ifdef MR_KCM
    int nl;
#endif
#ifdef MR_PENTIUM
    mr_small ndash;
    mr_small base;
    int control=0x1FFF;
#endif
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

    if (mr_mip->ERNUM) return (mr_small)0;
/* Is it set-up already? */
    if (mr_mip->modulus!=NULL)
        if (compare(n,mr_mip->modulus)==0) return mr_mip->ndash;

    MR_IN(80)

    if (size(n)<=2) 
    {
        mr_berror(_MIPP_ MR_ERR_BAD_MODULUS);
        MR_OUT
        return (mr_small)0;
    }
    zero(mr_mip->w6);

#ifdef MR_PENTIUM

mr_mip->ACTIVE=FALSE;
if (mr_mip->base!=0)
    if (MR_PENTIUM==0 || MR_PENTIUM==n[0]) mr_mip->ACTIVE=TRUE;
#endif

#ifdef MR_COMBA

    mr_mip->ACTIVE=FALSE;
    if (MR_COMBA==n[0] && mr_mip->base==0) mr_mip->ACTIVE=TRUE;

#endif

#ifdef MR_KCM
  
/* test for base==0 & n[0]=MR_KCM.2^x */

    mr_mip->ACTIVE=FALSE;
    if (mr_mip->base==0)
    {
        nl=(int)n[0];
        while (nl>=MR_KCM)
        {
            if (nl==MR_KCM)
            {
                mr_mip->ACTIVE=TRUE;
                break;
            }
            nl/=2;
        }
    }  
    if (mr_mip->ACTIVE)
    {
        mr_mip->w6[0]=n[0]+1;
        mr_mip->w6[n[0]+1]=1;
        if (xgcd(_MIPP_ n,mr_mip->w6,mr_mip->w14,mr_mip->w14,mr_mip->w14)!=1)
        { /* problems */
            mr_berror(_MIPP_ MR_ERR_BAD_MODULUS);
            MR_OUT
            return (mr_small)0;
        }
    }
    else
    {
#endif
        mr_mip->w6[0]=2;
        mr_mip->w6[1]=0;
        mr_mip->w6[2]=1;    /* w6 = base */
        nn[0]=1;
        nn[1]=n[1];    /* nn = n mod base */
        if (xgcd(_MIPP_ nn,mr_mip->w6,mr_mip->w14,mr_mip->w14,mr_mip->w14)!=1)
        { /* problems */
            mr_berror(_MIPP_ MR_ERR_BAD_MODULUS);
            MR_OUT
            return (mr_small)0;
        }
#ifdef MR_KCM
    }
    if (mr_mip->big_ndash==NULL) mr_mip->big_ndash=mirvar(_MIPP_ 0);
    copy(mr_mip->w14,mr_mip->big_ndash);
#endif
    mr_mip->ndash=mr_mip->base-mr_mip->w14[1]; /* = N' mod b */
    if (mr_mip->modulus==NULL) mr_mip->modulus=mirvar(_MIPP_ 0);
    copy(n,mr_mip->modulus);

#ifdef MR_PENTIUM
/* prime the FP stack */
    if (mr_mip->ACTIVE)
    {
        ndash=mr_mip->ndash;
        base=mr_mip->base;
        ASM
        {
            finit
            fldcw WORD PTR control
            fild DWORD PTR ndash
            fld1
            fild DWORD PTR base
            fdiv
            fild DWORD PTR base
        }
    }
#endif

    MR_OUT
    return mr_mip->ndash;
}

void nres(_MIPD_ big x,big y)
{ /* convert x to n-residue format */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(81)

    if (mr_mip->modulus==NULL)
    {
        mr_berror(_MIPP_ MR_ERR_NO_MODULUS);
        MR_OUT
        return;
    }
    copy(x,y);
    divide(_MIPP_ y,mr_mip->modulus,mr_mip->modulus);
    if (size(y)<0) add_r(_MIPP_ y,mr_mip->modulus,y);
    mr_mip->check=OFF;

    mr_shift(_MIPP_ y,(int)mr_mip->modulus[0],mr_mip->w0);
    divide(_MIPP_ mr_mip->w0,mr_mip->modulus,mr_mip->modulus);
    mr_mip->check=ON;
    copy(mr_mip->w0,y);

    MR_OUT
}

void redc(_MIPD_ big x,big y)
{ /* Montgomery's REDC function p. 520 */
  /* also used to convert n-residues back to normal form */
    mr_small carry,delay_carry,m,ndash;
    int i,j,rn,rn2p1;
    big w0,modulus;
#ifdef MR_NOASM
    mr_large dble;
#endif
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(82)

    w0=mr_mip->w0;        /* get these into local variables (for inline assembly) */
    modulus=mr_mip->modulus;
    ndash=mr_mip->ndash;

    copy(x,w0);
    delay_carry=0;
    rn=(int)modulus[0];
    rn2p1=rn+rn+1;
    if (mr_mip->base==0) for (i=1;i<=rn;i++)
    {
       /* inline - substitutes for loop below */
#if INLINE_ASM == 1
            ASM cld
            ASM mov cx,rn
            ASM mov si,i
            ASM shl si,1
#ifdef MR_LMM
            ASM push ds
            ASM push es
            ASM les bx,DWORD PTR w0
            ASM add bx,si
            ASM mov ax,es:[bx]
            ASM mul WORD PTR ndash
            ASM mov di,ax
            ASM lds si,DWORD PTR modulus
#else
            ASM mov bx,w0
            ASM add bx,si
            ASM mov ax,[bx]
            ASM mul WORD PTR ndash
            ASM mov di,ax
            ASM mov si,modulus
#endif
            ASM inc si
            ASM inc si
            ASM push bp
            ASM xor bp,bp
          m1:
            ASM lodsw
            ASM mul di
            ASM add ax,bp
            ASM adc dx,0
#ifdef MR_LMM
            ASM add es:[bx],ax
#else
            ASM add [bx],ax
#endif
            ASM adc dx,0
            ASM inc bx
            ASM inc bx
            ASM mov bp,dx
            ASM loop m1

            ASM pop bp
            ASM mov ax,delay_carry     
#ifdef MR_LMM
            ASM add es:[bx],ax
            ASM mov ax,0
            ASM adc ax,0
            ASM add es:[bx],dx
            ASM pop es
            ASM pop ds
#else
            ASM add [bx],ax
            ASM mov ax,0
            ASM adc ax,0
            ASM add [bx],dx
#endif
            ASM adc ax,0
            ASM mov delay_carry,ax
#endif
#if INLINE_ASM == 2
            ASM cld
            ASM mov cx,rn
            ASM mov si,i
            ASM shl si,2
#ifdef MR_LMM
            ASM push ds
            ASM push es
            ASM les bx,DWORD PTR w0
            ASM add bx,si
            ASM mov eax,es:[bx]
            ASM mul DWORD PTR ndash
            ASM mov edi,eax
            ASM lds si,DWORD PTR modulus
#else
            ASM mov bx,w0
            ASM add bx,si
            ASM mov eax,[bx]
            ASM mul DWORD PTR ndash
            ASM mov edi,eax
            ASM mov si,modulus
#endif
            ASM add si,4
            ASM push ebp
            ASM xor ebp,ebp
          m1:
            ASM lodsd
            ASM mul edi
            ASM add eax,ebp
            ASM adc edx,0
#ifdef MR_LMM
            ASM add es:[bx],eax
#else
            ASM add [bx],eax
#endif
            ASM adc edx,0
            ASM add bx,4
            ASM mov ebp,edx
            ASM loop m1

            ASM pop ebp
            ASM mov eax,delay_carry    
#ifdef MR_LMM
            ASM add es:[bx],eax
            ASM mov eax,0
            ASM adc eax,0
            ASM add es:[bx],edx
            ASM pop es
            ASM pop ds
#else 
            ASM add [bx],eax
            ASM mov eax,0
            ASM adc eax,0
            ASM add [bx],edx
#endif
            ASM adc eax,0
            ASM mov delay_carry,eax

#endif
#if INLINE_ASM == 3
            ASM mov ecx,rn
            ASM mov esi,i
            ASM shl esi,2
            ASM mov ebx,w0
            ASM add ebx,esi
            ASM mov eax,[ebx]
            ASM mul DWORD PTR ndash
            ASM mov edi,eax
            ASM mov esi,modulus
            ASM add esi,4
            ASM sub ebx,esi
            ASM sub ebx,4
            ASM push ebp
            ASM xor ebp,ebp
          m1:
            ASM mov eax,[esi]
            ASM add esi,4
            ASM mul edi
            ASM add eax,ebp
            ASM mov ebp,[esi+ebx]
            ASM adc edx,0
            ASM add ebp,eax
            ASM adc edx,0
            ASM mov [esi+ebx],ebp
            ASM dec ecx
            ASM mov ebp,edx
            ASM jnz m1

            ASM pop ebp
            ASM mov eax,delay_carry     
            ASM add [esi+ebx+4],eax
            ASM mov eax,0
            ASM adc eax,0
            ASM add [esi+ebx+4],edx
            ASM adc eax,0
            ASM mov delay_carry,eax

#endif
#if INLINE_ASM == 4
   ASM ("
           movl %0,%%ecx\n
           movl %1,%%esi\n
           shll $2,%%esi\n
           movl %2,%%ebx\n
           addl %%esi,%%ebx\n
           movl (%%ebx),%%eax\n
           mull %3\n
           movl %%eax,%%edi\n
           movl %4,%%esi\n
           addl $4,%%esi\n
           subl %%esi,%%ebx\n
           subl $4,%%ebx\n
           pushl %%ebp\n
           xorl %%ebp,%%ebp\n
         m1:\n
           movl (%%esi),%%eax\n
           addl $4,%%esi\n 
           mull %%edi\n
           addl %%ebp,%%eax\n
           movl (%%esi,%%ebx),%%ebp\n
           adcl $0,%%edx\n
           addl %%eax,%%ebp\n 
           adcl $0,%%edx\n
           movl %%ebp,(%%esi,%%ebx)\n
           decl %%ecx\n
           movl %%edx,%%ebp\n
           jnz m1\n   

           popl %%ebp\n
           movl %5,%%eax\n
           addl %%eax,4(%%esi,%%ebx)\n
           movl $0,%%eax\n
           adcl $0,%%eax\n
           addl %%edx,4(%%esi,%%ebx)\n
           adcl $0,%%eax\n
           movl %%eax,%5\n
        "
        :
        :"g"(rn),"g"(i),"g"(w0),"g"(ndash),"g"(modulus),"g"(delay_carry)
        :"eax","edi","esi","ebx","ecx","edx","memory"
       );
#endif

#ifndef INLINE_ASM
        muldvd(w0[i],ndash,0,&m);   /* Note that after this time   */
        carry=0;                       /* around the loop, w0[i]=0    */

        for (j=1;j<=rn;j++)
        {
#ifdef MR_NOASM 
            dble=(mr_large)m*modulus[j]+carry+w0[i+j-1];
            w0[i+j-1]=(mr_small)dble;
            carry=MR_TOP(dble);
#else
            muldvd2(m,modulus[j],&carry,&w0[i+j-1]);
#endif
        }
        w0[rn+i]+=delay_carry;
        if (w0[rn+i]<delay_carry) delay_carry=1;
        else delay_carry=0;
        w0[rn+i]+=carry;
        if (w0[rn+i]<carry) delay_carry=1; 
#endif
    }
    else for (i=1;i<=rn;i++) 
    {
        muldiv(w0[i],ndash,0,mr_mip->base,&m);

        carry=0;
        for (j=1;j<=rn;j++)
          carry=muldiv(modulus[j],m,w0[i+j-1]+carry,mr_mip->base,&w0[i+j-1]);
        w0[rn+i]+=(delay_carry+carry);
        delay_carry=0;
        if (w0[rn+i]>=mr_mip->base)
        {
            w0[rn+i]-=mr_mip->base;
            delay_carry=1; 
        }
    }
    w0[rn2p1]=delay_carry;
    w0[0]=rn2p1;
    mr_shift(_MIPP_ w0,(-rn),w0);
    mr_lzero(w0);
    
    if (compare(w0,modulus)>=0) mr_psub(_MIPP_ w0,modulus,y);
    else copy(w0,y);
    MR_OUT
}

void nres_dotprod(_MIPD_ int n,big *x,big*y,big w)
{
    int i;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

    if (mr_mip->ERNUM) return;
    MR_IN(120)
    mr_mip->check=OFF;
    zero(mr_mip->w7);
    for (i=0;i<n;i++)
    {
        multiply(_MIPP_ x[i],y[i],mr_mip->w0);
        mr_padd(_MIPP_ mr_mip->w7,mr_mip->w0,mr_mip->w7);
    }
    mr_shift(_MIPP_ mr_mip->modulus,(int)mr_mip->modulus[0],mr_mip->w6);
        /* w6 = N.R */
    divide(_MIPP_ mr_mip->w7,mr_mip->w6,mr_mip->w6);
    redc(_MIPP_ mr_mip->w7,w);

    mr_mip->check=ON;
    MR_OUT
}

void nres_negate(_MIPD_ big x, big w)
{
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(92)
    if (size(x)==0) zero(w);
    else mr_psub(_MIPP_ mr_mip->modulus,x,w);    
    MR_OUT
}

void nres_modadd(_MIPD_ big x,big y,big w)
{ /* modular addition */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

#ifdef MR_COMBA
    if (mr_mip->ACTIVE)
    {
        comba_add(_MIPP_ x,y,w);
        return;
    }
    else
    {
#endif
        if (mr_mip->ERNUM) return;

        MR_IN(90)

        mr_padd(_MIPP_ x,y,w);
        if (compare(w,mr_mip->modulus)>=0) mr_psub(_MIPP_ w,mr_mip->modulus,w);

        MR_OUT
#ifdef MR_COMBA
    }
#endif

}

void nres_modsub(_MIPD_ big x,big y,big w)
{ /* modular subtraction */

#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
#ifdef MR_COMBA
    if (mr_mip->ACTIVE)
    {
        comba_sub(_MIPP_ x,y,w);
        return;
    }
    else
    {
#endif
        if (mr_mip->ERNUM) return;

        MR_IN(91)

        if (compare(x,y)>=0)
            mr_psub(_MIPP_ x,y,w);
        else
        {
            mr_psub(_MIPP_ y,x,w);
            mr_psub(_MIPP_ mr_mip->modulus,w,w);
        }
        MR_OUT
#ifdef MR_COMBA
    }
#endif

}

int nres_moddiv(_MIPD_ big x,big y,big w)
{ /* Modular division using n-residues w=x/y mod n */
    int gcd;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return 0;

    MR_IN(85)

    if (x==y)
    { /* Illegal parameter usage */
        mr_berror(_MIPP_ MR_ERR_BAD_PARAMETERS);
        MR_OUT
        return 0;
    }
    redc(_MIPP_ y,mr_mip->w6);
    gcd=xgcd(_MIPP_ mr_mip->w6,mr_mip->modulus,mr_mip->w6,mr_mip->w6,mr_mip->w6);
    mad(_MIPP_ x,mr_mip->w6,x,mr_mip->modulus,mr_mip->modulus,w);
    MR_OUT
    return gcd;
}

void nres_premult(_MIPD_ big x,int k,big w)
{ /* multiply n-residue by small ordinary integer */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(102)

    premult(_MIPP_ x,k,w);
    divide(_MIPP_ w,mr_mip->modulus,mr_mip->modulus);
    if (size(w)<0) add_r(_MIPP_ w,mr_mip->modulus,w);

    MR_OUT
}

void nres_modmult(_MIPD_ big x,big y,big w)
{ /* Modular multiplication using n-residues w=x*y mod n */

#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
#ifdef MR_COMBA
    if (mr_mip->ACTIVE)
    {
        if (x==y) comba_square(_MIPP_ x,mr_mip->w0);
        else      comba_mult(_MIPP_ x,y,mr_mip->w0);
        comba_redc(_MIPP_ mr_mip->w0,w);
    }
    else
    {
#endif
#ifdef MR_KCM
    if (mr_mip->ACTIVE)
    {
        if (x==y) kcm_sqr(_MIPP_ x,mr_mip->w0);
        else      kcm_mul(_MIPP_ x,y,mr_mip->w0);
        kcm_redc(_MIPP_ mr_mip->w0,w);
    }
    else
    { 
#endif
        if (mr_mip->ERNUM) return;

        MR_IN(83)

        mr_mip->check=OFF;
        multiply(_MIPP_ x,y,mr_mip->w0);
        redc(_MIPP_ mr_mip->w0,w);
        mr_mip->check=ON;
        MR_OUT
#ifdef MR_COMBA
}
#endif
#ifdef MR_KCM
}
#endif

}

/* Montgomery's trick for finding multiple   *
 * simultaneous modular inverses             *
 * Based on the observation that             *
 *           1/x = yz*(1/xyz)                *
 *           1/y = xz*(1/xyz)                *
 *           1/z = xy*(1/xyz)                *
 * Why are all of Peter Montgomery's clever  *
 * algorithms always described as "tricks" ??*/

BOOL nres_multi_inverse(_MIPD_ int m,big *x,big *w)
{ /* find w[i]=1/x[i] mod n, for i=0 to m-1 *
   * x and w MUST be distinct               */
    int i;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (m==0) return TRUE;
    if (m<0) return FALSE;
    MR_IN(118)

    if (x==w)
    {
        mr_berror(_MIPP_ MR_ERR_BAD_PARAMETERS);
        MR_OUT
        return FALSE;
    }

    if (m==1)
    {
        convert(_MIPP_ 1,w[0]);
        nres(_MIPP_ w[0],w[0]);
        nres_moddiv(_MIPP_ w[0],x[0],w[0]);
        MR_OUT
        return TRUE;
    }

    convert(_MIPP_ 1,w[0]);
    copy(x[0],w[1]);
    for (i=2;i<m;i++)
        nres_modmult(_MIPP_ w[i-1],x[i-1],w[i]); 

    nres_modmult(_MIPP_ w[m-1],x[m-1],mr_mip->w6);  /* y=x[0]*x[1]*x[2]....x[m-1] */
    if (size(mr_mip->w6)==0)
    {
        mr_berror(_MIPP_ MR_ERR_DIV_BY_ZERO);
        MR_OUT
        return FALSE;
    }

    redc(_MIPP_ mr_mip->w6,mr_mip->w6);
    redc(_MIPP_ mr_mip->w6,mr_mip->w6);
    xgcd(_MIPP_ mr_mip->w6,mr_mip->modulus,mr_mip->w6,mr_mip->w6,mr_mip->w6);

/* Now y=1/y */

    copy(x[m-1],mr_mip->w5);
    nres_modmult(_MIPP_ w[m-1],mr_mip->w6,w[m-1]);

    for (i=m-2;;i--)
    {
        if (i==0)
        {
            nres_modmult(_MIPP_ mr_mip->w5,mr_mip->w6,w[0]);
            break;
        }
        nres_modmult(_MIPP_ w[i],mr_mip->w5,w[i]);
        nres_modmult(_MIPP_ w[i],mr_mip->w6,w[i]);
        nres_modmult(_MIPP_ mr_mip->w5,x[i],mr_mip->w5);
    }

    MR_OUT 
    return TRUE;   
}

