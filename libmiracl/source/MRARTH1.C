/*
 *   MIRACL arithmetic routines 1 - multiplying and dividing BIG NUMBERS by  
 *   integer numbers.
 *   mrarth1.c
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

void mr_pmul(_MIPD_ big x,mr_small sn,big z)
{ 
    int m,xl;
    mr_small carry,sx;
#ifdef MR_NOASM
    mr_large dble;
#endif
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (x!=z)
    {
        zero(z);
        if (sn==0) return;
    }
    else if (sn==0)
    {
        zero(z);
        return;
    }
    
    m=0;
    carry=0;
    sx=x[0]&MR_MSBIT;
    xl=(int)(x[0]&MR_OBITS);
    if (mr_mip->base==0) 
    {
/* inline 8086 assembly - substitutes for loop below */
#if INLINE_ASM == 1
        ASM cld
        ASM mov cx,xl
        ASM or cx,cx
        ASM je out1
#ifdef MR_LMM
        ASM push ds
        ASM push es
        ASM les di,DWORD PTR z
        ASM lds si,DWORD PTR x
#else
        ASM mov ax,ds
        ASM mov es,ax
        ASM mov di,z
        ASM mov si,x
#endif
        ASM mov bx,sn
        ASM inc si
        ASM inc si
        ASM inc di
        ASM inc di
        ASM push bp
        ASM xor bp,bp
    tcl1:
        ASM lodsw
        ASM mul bx
        ASM add ax,bp
        ASM adc dx,0
        ASM stosw
        ASM mov bp,dx
        ASM loop tcl1

        ASM mov ax,bp
        ASM pop bp
#ifdef MR_LMM
        ASM pop es
        ASM pop ds
#endif
        ASM mov carry,ax
     out1: 
#endif
#if INLINE_ASM == 2
        ASM cld
        ASM mov cx,xl
        ASM or cx,cx
        ASM je out1
#ifdef MR_LMM
        ASM push ds
        ASM push es
        ASM les di,DWORD PTR z
        ASM lds si,DWORD PTR x
#else
        ASM mov ax,ds
        ASM mov es,ax
        ASM mov di,z
        ASM mov si,x
#endif
        ASM mov ebx,sn
        ASM add si,4
        ASM add di,4
        ASM push ebp
        ASM xor ebp,ebp
    tcl1:
        ASM lodsd
        ASM mul ebx
        ASM add eax,ebp
        ASM adc edx,0
        ASM stosd
        ASM mov ebp,edx
        ASM loop tcl1

        ASM mov eax,ebp
        ASM pop ebp
#ifdef MR_LMM
        ASM pop es
        ASM pop ds
#endif
        ASM mov carry,eax
     out1: 
#endif
#if INLINE_ASM == 3
        ASM mov ecx,xl
        ASM or ecx,ecx
        ASM je out1
        ASM mov ebx,sn
        ASM mov edi,z
        ASM mov esi,x
        ASM add esi,4
        ASM add edi,4
        ASM push ebp
        ASM xor ebp,ebp
    tcl1:
        ASM mov eax,[esi]
        ASM add esi,4
        ASM mul ebx
        ASM add eax,ebp
        ASM adc edx,0
        ASM mov [edi],eax
        ASM add edi,4
        ASM mov ebp,edx
        ASM dec ecx
        ASM jnz tcl1

        ASM mov eax,ebp
        ASM pop ebp
        ASM mov carry,eax
     out1: 
#endif
#if INLINE_ASM == 4

        ASM ("
           movl %4,%%ecx\n
           orl  %%ecx,%%ecx\n
           je 1f\n
           movl %3,%%ebx\n
           movl %1,%%edi\n
           movl %2,%%esi\n
           addl $4,%%esi\n
           addl $4,%%edi\n
           pushl %%ebp\n
           xorl %%ebp,%%ebp\n  
        0:\n  
           movl (%%esi),%%eax\n
           addl $4,%%esi\n
           mull %%ebx\n
           addl %%ebp,%%eax\n
           adcl $0,%%edx\n
           movl %%eax,(%%edi)\n
           addl $4,%%edi\n
           movl %%edx,%%ebp\n
           decl %%ecx\n
           jnz 0b\n
 
           movl %%ebp,%%eax\n
           popl %%ebp\n
           movl %%eax,%0\n
        1:"  
        :"=g"(carry)
        :"g"(z),"g"(x),"g"(sn),"g"(xl)
        :"eax","edi","esi","ebx","ecx","edx","memory"
        );

#endif
#ifndef INLINE_ASM
        for (m=1;m<=xl;m++)
#ifdef MR_NOASM
        {
            dble=(mr_large)x[m]*sn+carry;
            carry=MR_TOP(dble);
            z[m]=(mr_small)dble;
        }
#else
            carry=muldvd(x[m],sn,carry,&z[m]);
#endif
#endif
        
        if (carry>0)
        {
            m=xl+1;
            if (m>mr_mip->nib && mr_mip->check)
            {
                mr_berror(_MIPP_ MR_ERR_OVERFLOW);
                return;
            }
            z[m]=carry;
            z[0]=m;
        }
        else z[0]=xl;
    }
    else while (m<xl || carry>0)
    { /* multiply each digit of x by n */ 
        m++;
        if (m>mr_mip->nib && mr_mip->check)
        {
            mr_berror(_MIPP_ MR_ERR_OVERFLOW);
            return;
        }
#ifdef MR_NOASM
        dble=(mr_large)x[m]*sn+carry;
        carry=(mr_small)(dble/mr_mip->base);
        z[m]=(mr_small)(dble-(mr_large)carry*mr_mip->base);
#else
        carry=muldiv(x[m],sn,carry,mr_mip->base,&z[m]);
#endif
        z[0]=m;
    }
    if (z[0]!=0) z[0]|=sx;
}

void premult(_MIPD_ big x,int n,big z)
{ /* premultiply a big number by an int z=x.n */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(9)


#ifdef MR_FLASH
    if (mr_notint(x))
    {
        mr_berror(_MIPP_ MR_ERR_INT_OP);
        MR_OUT
        return;
    }
#endif
    if (n==0)  /* test for some special cases  */
    {
        zero(z);
        MR_OUT
        return;
    }
    if (n==1)
    {
        copy(x,z);
        MR_OUT
        return;
    }
    if (n<0)
    {
        n=(-n);
        mr_pmul(_MIPP_ x,(mr_small)n,z);
        if (z[0]!=0) z[0]^=MR_MSBIT;
    }
    else mr_pmul(_MIPP_ x,(mr_small)n,z);
    MR_OUT
}

mr_small mr_sdiv(_MIPD_ big x,mr_small sn,big z)
{
    int i,xl;
    mr_small sr;
#ifdef MR_NOASM
    mr_large dble;
#endif
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    sr=0;
    xl=(int)(x[0]&MR_OBITS);
    if (x!=z) zero(z);
    if (mr_mip->base==0) 
    {
/* inline - substitutes for loop below */
#if INLINE_ASM == 1
        ASM std
        ASM mov cx,xl
        ASM or cx,cx
        ASM je out2
        ASM mov bx,cx
        ASM shl bx,1
#ifdef MR_LMM
        ASM push ds
        ASM push es
        ASM les di,DWORD PTR z
        ASM lds si,DWORD PTR x
#else
        ASM mov ax,ds
        ASM mov es,ax
        ASM mov di,z
        ASM mov si,x
#endif
        ASM add si,bx
        ASM add di,bx
        ASM mov bx,sn
        ASM push bp
        ASM xor bp,bp
    tcl2:
        ASM mov dx,bp
        ASM lodsw
        ASM div bx
        ASM mov bp,dx
        ASM stosw
        ASM loop tcl2

        ASM mov ax,bp
        ASM pop bp
#ifdef MR_LMM
        ASM pop es
        ASM pop ds
#endif
        ASM mov sr,ax
     out2:
        ASM cld
#endif
#if INLINE_ASM == 2
        ASM std
        ASM mov cx,xl
        ASM or cx,cx
        ASM je out2
        ASM mov bx,cx
        ASM shl bx,2
#ifdef MR_LMM
        ASM push ds
        ASM push es
        ASM les di,DWORD PTR z
        ASM lds si,DWORD PTR x
#else
        ASM mov ax,ds
        ASM mov es,ax
        ASM mov di, z
        ASM mov si, x
#endif
        ASM add si,bx
        ASM add di,bx
        ASM mov ebx,sn
        ASM push ebp
        ASM xor ebp,ebp
    tcl2:
        ASM mov edx,ebp
        ASM lodsd
        ASM div ebx
        ASM mov ebp,edx
        ASM stosd
        ASM loop tcl2

        ASM mov eax,ebp
        ASM pop ebp
#ifdef MR_LMM
        ASM pop es
        ASM pop ds
#endif
        ASM mov sr,eax
     out2: 
        ASM cld
#endif
#if INLINE_ASM == 3
        ASM mov ecx,xl
        ASM or ecx,ecx
        ASM je out2
        ASM mov ebx,ecx
        ASM shl ebx,2
        ASM mov esi, x
        ASM add esi,ebx
        ASM mov edi, z
        ASM add edi,ebx
        ASM mov ebx,sn
        ASM push ebp
        ASM xor ebp,ebp
    tcl2:
        ASM mov edx,ebp
        ASM mov eax,[esi]
        ASM sub esi,4
        ASM div ebx
        ASM mov ebp,edx
        ASM mov [edi],eax
        ASM sub edi,4
        ASM dec ecx
        ASM jnz tcl2

        ASM mov eax,ebp
        ASM pop ebp
        ASM mov sr,eax
     out2:
        ASM nop
#endif
#if INLINE_ASM == 4

        ASM ("
           movl %4,%%ecx\n
           orl  %%ecx,%%ecx\n
           je 3f\n
           movl %%ecx,%%ebx\n
           shll $2,%%ebx\n
           movl %2,%%esi\n
           addl %%ebx,%%esi\n
           movl %1,%%edi\n
           addl %%ebx,%%edi\n
           movl %3,%%ebx\n
           pushl %%ebp\n
           xorl %%ebp,%%ebp\n  
         2:\n  
           movl %%ebp,%%edx\n
           movl (%%esi),%%eax\n
           subl $4,%%esi\n
           divl %%ebx\n
           movl %%edx,%%ebp\n
           movl %%eax,(%%edi)\n
           subl $4,%%edi\n
           decl %%ecx\n
           jnz 2b\n
 
           movl %%ebp,%%eax\n
           popl %%ebp\n
           movl %%eax,%0\n
        3:
           nop"  
        :"=g"(sr)
        :"g"(z),"g"(x),"g"(sn),"g"(xl)
        :"eax","edi","esi","ebx","ecx","edx","memory"
        );
#endif
#ifndef INLINE_ASM
        for (i=xl;i>0;i--)
        {
#ifdef MR_NOASM
            MR_BOT(dble)=x[i];
            MR_TOP(dble)=sr;
            z[i]=(mr_small)(dble/sn);
            sr=(mr_small)(dble-(mr_large)z[i]*sn);
#else
            z[i]=muldvm(sr,x[i],sn,&sr);
#endif
        }
#endif
    }
    else for (i=xl;i>0;i--)
    { /* divide each digit of x by n */
#ifdef MR_NOASM
        dble=(mr_large)sr*mr_mip->base+x[i];
        z[i]=(mr_small)(dble/sn);
        sr=(mr_small)(dble-(mr_large)z[i]*sn);
#else
        z[i]=muldiv(sr,mr_mip->base,x[i],sn,&sr);
#endif
    }
    z[0]=x[0];
    mr_lzero(z);
    return sr;
}
         
int subdiv(_MIPD_ big x,int n,big z)
{  /*  subdivide a big number by an int   z=x/n  *
    *  returns int remainder                     */ 
    mr_small sx;
    int r;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return 0;

    MR_IN(10)
#ifdef MR_FLASH
    if (mr_notint(x)) mr_berror(_MIPP_ MR_ERR_INT_OP);
#endif
    if (n==0) mr_berror(_MIPP_ MR_ERR_DIV_BY_ZERO);
    if (mr_mip->ERNUM) 
    {
        MR_OUT
        return 0;
    }
    if (n==1) /* special case */
    {
        copy(x,z);
        MR_OUT
        return 0;
    }
    sx=(x[0]&MR_MSBIT);
    if (n<0)
    {
        n=(-n);
        r=(int)mr_sdiv(_MIPP_ x,(mr_small)n,z);
        if (z[0]!=0) z[0]^=MR_MSBIT;
    }
    else r=(int)mr_sdiv(_MIPP_ x,(mr_small)n,z);
    MR_OUT
    if (sx==0) return r;
    else       return (-r);
}

int remain(_MIPD_ big x,int n)
{ /* return integer remainder when x divided by n */
    int r;
    mr_small sx;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return FALSE;

    MR_IN(88);

    sx=(x[0]&MR_MSBIT);
    if (n==2 && mr_mip->base%2==0)
    { /* fast odd/even check if base is even */
        MR_OUT
        if (x[1]%2==0) return 0;
        else
        {
            if (sx==0) return 1;
            else       return (-1);
        } 
    }
    copy(x,mr_mip->w0);
    r=subdiv(_MIPP_ mr_mip->w0,n,mr_mip->w0);
    MR_OUT
    return r;
}

BOOL subdivisible(_MIPD_ big x,int n)
{
    if (remain(_MIPP_ x,n)==0) return TRUE;
    else                return FALSE;
}

void bytes_to_big(_MIPD_ int len,char *ptr,big x)
{ /* convert len bytes into a big           *
   * The first byte is the Most significant */
    int i;
    unsigned int dig;
    unsigned char ch;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    MR_IN(140);

    zero(x);
    for (i=0;i<len;i++)
    {
        if (mr_mip->ERNUM) break;
        premult(_MIPP_ x,256,x);
        ch=(unsigned char)ptr[i];
        dig=ch;  
        incr(_MIPP_ x,(int)dig,x);
    }

    MR_OUT
} 

int big_to_bytes(_MIPD_ int max,big x,char *ptr)
{ /* convert big into octet string */
    int i,len;
    unsigned int dig;
    unsigned char ch;

#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return 0;
    MR_IN(141);

    copy(x,mr_mip->w1);
    for (len=0;;len++)
    {
        if (size(mr_mip->w1)==0 || mr_mip->ERNUM) break;    
        if (max>0 && len>max)
        {
            mr_berror(_MIPP_ MR_ERR_TOO_BIG);
            MR_OUT
            return 0; 
        }
        dig=(unsigned int)subdiv(_MIPP_ mr_mip->w1,256,mr_mip->w1);
        ch=(unsigned char)dig;
        for (i=len;i>0;i--) ptr[i]=ptr[i-1];
        ptr[0]=(char)ch;
    }

    MR_OUT
    return len;
}

