/*
 *   MIRACL arithmetic routines 2 - multiplying and dividing BIG NUMBERS.
 *   mrarth2.c
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

mr_small normalise(_MIPD_ big x,big y)
{ /* normalise divisor */
    mr_small norm,r;
    int len;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

    MR_IN(4)

    if (x!=y) copy(x,y);
    len=(int)(y[0]&MR_OBITS);
    if (mr_mip->base==0)
    {
        if ((r=y[len]+1)==0) norm=1;
#ifdef MR_NOASM
        else norm=(mr_small)(((mr_large)1 << MIRACL)/r);
#else
        else norm=muldvm((mr_small)1,(mr_small)0,r,&r);
#endif
        if (norm!=1) mr_pmul(_MIPP_ y,norm,y);
    }
    else
    {
        norm=mr_mip->base/(y[len]+1);   
        if (norm!=1) mr_pmul(_MIPP_ y,norm,y);
    }
    MR_OUT
    return norm;
}

void multiply(_MIPD_ big x,big y,big z)
{  /*  multiply two big numbers: z=x.y  */
    int i,xl,yl,j,ti;
    mr_small carry,sz;
    big w0;
#ifdef MR_NOASM
    mr_large dble;
#endif
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    if (y[0]==0 || x[0]==0) 
    {
        zero(z);
        return;
    }
    w0=mr_mip->w0;    /* local pointer */

    MR_IN(5)

#ifdef MR_FLASH
    if (mr_notint(x) || mr_notint(y))
    {
        mr_berror(_MIPP_ MR_ERR_INT_OP);
        MR_OUT
        return;
    }
#endif
    sz=((x[0]&MR_MSBIT)^(y[0]&MR_MSBIT));
    xl=(int)(x[0]&MR_OBITS);
    yl=(int)(y[0]&MR_OBITS);
    zero(w0);
    if (mr_mip->check && xl+yl>mr_mip->nib)
    {
        mr_berror(_MIPP_ MR_ERR_OVERFLOW);
        MR_OUT
        return;
    }
    if (mr_mip->base==0)
    {
        if (x==y)
        { /* fast squaring */
            for (i=1;i<xl;i++)
            {  /* long multiplication */
           /* inline - substitutes for loop below */
#if INLINE_ASM == 1
                ASM cld
                ASM mov dx,i
                ASM mov cx,xl
                ASM sub cx,dx
                ASM shl dx,1
#ifdef MR_LMM
                ASM push ds
                ASM push es
                ASM les bx,DWORD PTR w0
                ASM lds si,DWORD PTR x
                ASM add si,dx
                ASM mov di,[si]
#else
                ASM mov bx,w0
                ASM mov si,x
                ASM add si,dx
                ASM mov di,[si]
#endif
                ASM add bx,dx
                ASM add bx,dx 
                ASM inc si
                ASM inc si
                ASM push bp
                ASM xor bp,bp
              tcl4:
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
                ASM loop tcl4

#ifdef MR_LMM
                ASM mov es:[bx],bp
                ASM pop bp
                ASM pop es
                ASM pop ds
#else
                ASM mov [bx],bp
                ASM pop bp
#endif
#endif
#if INLINE_ASM == 2
                ASM cld
                ASM mov dx,i
                ASM mov cx,xl
                ASM sub cx,dx
                ASM shl dx,2
#ifdef MR_LMM
                ASM push ds
                ASM push es
                ASM les bx,DWORD PTR w0
                ASM lds si,DWORD PTR x
                ASM add si,dx
                ASM mov edi,[si]
#else
                ASM mov bx,w0
                ASM mov si,x
                ASM add si,dx
                ASM mov edi,[si]
#endif
                ASM add bx,dx
                ASM add bx,dx
                ASM add si,4
                ASM push ebp
                ASM xor ebp,ebp
              tcl4:
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
                ASM loop tcl4

#ifdef MR_LMM
                ASM mov es:[bx],ebp
                ASM pop ebp
                ASM pop es
                ASM pop ds
#else
                ASM mov [bx],ebp
                ASM pop ebp
#endif
#endif
#if INLINE_ASM == 3
                ASM mov esi,i
                ASM mov ecx,xl
                ASM sub ecx,esi
                ASM shl esi,2
                ASM mov edx, x
                ASM mov ebx,edx
                ASM add ebx,esi
                ASM mov edi,[ebx]
                ASM mov ebx,w0
                ASM add ebx,esi
                ASM add esi,edx
                ASM sub ebx,edx
                ASM add esi,4
                ASM sub ebx,8
                ASM push ebp
                ASM xor ebp,ebp
              tcl4:
                ASM mov eax,[esi]   /* optimized for Pentium */
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
                ASM jnz tcl4

                ASM mov [esi+ebx+4],ebp
                ASM pop ebp
#endif
#if INLINE_ASM == 4
   ASM ("
           movl %0,%%esi\n
           movl %1,%%ecx\n
           subl %%esi,%%ecx\n
           shll $2,%%esi\n
           movl %2,%%edx\n
           movl %%edx,%%ebx\n
           addl %%esi,%%ebx\n
           movl (%%ebx),%%edi\n
           movl %3,%%ebx\n
           addl %%esi,%%ebx\n
           addl %%edx,%%esi\n
           subl %%edx,%%ebx\n
           addl $4,%%esi\n
           subl $8,%%ebx\n
           pushl %%ebp\n
           xorl %%ebp,%%ebp\n
         tcl4:\n
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
           jnz tcl4\n

           movl %%ebp,4(%%esi,%%ebx)\n
           popl %%ebp\n
            
        "
        :
        :"g"(i),"g"(xl),"g"(x),"g"(w0)
        :"eax","edi","esi","ebx","ecx","edx","memory"
       );
#endif
#ifndef INLINE_ASM
                carry=0;
                for (j=i+1;j<=xl;j++)
                { /* Only do above the diagonal */
#ifdef MR_NOASM
                    dble=(mr_large)x[i]*x[j]+carry+w0[i+j-1];
                    w0[i+j-1]=(mr_small)dble;
                    carry=MR_TOP(dble);
#else
                    muldvd2(x[i],x[j],&carry,&w0[i+j-1]);
#endif
                }
                w0[xl+i]=carry;
#endif
            }
#if INLINE_ASM == 1
            ASM mov cx,xl
            ASM shl cx,1
#ifdef MR_LMM
            ASM push ds
            ASM push es
            ASM les bx,DWORD PTR w0  
#else
            ASM mov bx,w0
#endif
          tcl5:
            ASM inc bx
            ASM inc bx
#ifdef MR_LMM
            ASM rcl WORD PTR es:[bx],1
#else
            ASM rcl WORD PTR [bx],1
#endif
            ASM loop tcl5

            ASM cld
            ASM mov cx,xl
#ifdef MR_LMM
            ASM les di,DWORD PTR w0
            ASM lds si,DWORD PTR x
#else
            ASM mov di,w0
            ASM mov si,x
#endif
            ASM inc si
            ASM inc si
            ASM inc di
            ASM inc di
            ASM xor bx,bx
          tcl7:
            ASM lodsw
            ASM mul ax
            ASM add ax,bx
            ASM adc dx,0
#ifdef MR_LMM
            ASM add es:[di],ax
#else
            ASM add [di],ax
#endif
            ASM adc dx,0
            ASM xor bx,bx
            ASM inc di
            ASM inc di
#ifdef MR_LMM
            ASM add es:[di],dx
#else
            ASM add [di],dx
#endif
            ASM adc bx,0
            ASM inc di
            ASM inc di
            ASM loop tcl7
#ifdef MR_LMM
            ASM pop es
            ASM pop ds
#endif
#endif
#if INLINE_ASM == 2
            ASM mov cx,xl
            ASM shl cx,1
#ifdef MR_LMM
            ASM push ds
            ASM push es
            ASM les bx,DWORD PTR w0
#else
            ASM mov bx,w0
#endif
          tcl5:
            ASM inc bx
            ASM inc bx
            ASM inc bx
            ASM inc bx
#ifdef MR_LMM
            ASM rcl DWORD PTR es:[bx],1
#else
            ASM rcl DWORD PTR [bx],1
#endif
            ASM loop tcl5

            ASM cld
            ASM mov cx,xl
#ifdef MR_LMM
            ASM les di,DWORD PTR w0
            ASM lds si,DWORD PTR x
#else
            ASM mov di,w0
            ASM mov si,x
#endif
            ASM add si,4
            ASM add di,4
            ASM xor ebx,ebx
          tcl7:
            ASM lodsd
            ASM mul eax
            ASM add eax,ebx
            ASM adc edx,0
#ifdef MR_LMM
            ASM add es:[di],eax
#else
            ASM add [di],eax
#endif
            ASM adc edx,0
            ASM xor ebx,ebx
            ASM add di,4
#ifdef MR_LMM
            ASM add es:[di],edx
#else
            ASM add [di],edx
#endif
            ASM adc ebx,0
            ASM add di,4
            ASM loop tcl7
#ifdef MR_LMM
            ASM pop es
            ASM pop ds
#endif
#endif
#if INLINE_ASM == 3
            ASM mov ecx,xl
            ASM shl ecx,1
            ASM mov edi,w0
          tcl5:
            ASM inc edi
            ASM inc edi
            ASM inc edi
            ASM inc edi
            ASM rcl DWORD PTR [edi],1
            ASM loop tcl5

            ASM mov ecx,xl
            ASM mov esi,x
            ASM mov edi,w0
            ASM add esi,4
            ASM add edi,4
            ASM xor ebx,ebx
          tcl7:
            ASM mov eax,[esi]
            ASM add esi,4
            ASM mul eax
            ASM add eax,ebx
            ASM adc edx,0
            ASM add [edi],eax
            ASM adc edx,0
            ASM xor ebx,ebx
            ASM add edi,4
            ASM add [edi],edx
            ASM adc ebx,0
            ASM add edi,4
            ASM dec ecx
            ASM jnz tcl7
#endif
#if INLINE_ASM == 4
   ASM ("
           movl %0,%%ecx\n
           shll $1,%%ecx\n
           movl %1,%%edi\n
         tcl5:
           incl %%edi\n
           incl %%edi\n
           incl %%edi\n
           incl %%edi\n
           rcll $1,(%%edi)\n
           loop tcl5\n

           movl %0,%%ecx\n
           movl %2,%%esi\n
           movl %1,%%edi\n
           addl $4,%%esi\n
           addl $4,%%edi\n
           xorl %%ebx,%%ebx\n
          tcl7:\n
           movl (%%esi),%%eax\n
           addl $4,%%esi\n
           mull %%eax\n
           addl %%ebx,%%eax\n
           adcl $0,%%edx\n
           addl %%eax,(%%edi)\n
           adcl $0,%%edx\n
           xorl %%ebx,%%ebx\n
           addl $4,%%edi\n
           addl %%edx,(%%edi)\n
           adcl $0,%%ebx\n
           addl $4,%%edi\n
           decl %%ecx
           jnz tcl7\n                       
            
        "
        :
        :"g"(xl),"g"(w0),"g"(x)
        :"eax","edi","esi","ebx","ecx","edx","memory"
       );
#endif
#ifndef INLINE_ASM
            w0[0]=xl+xl-1;
            mr_padd(_MIPP_ w0,w0,w0);     /* double it */
            carry=0;
            for (i=1;i<=xl;i++)
            { /* add in squared elements */
                ti=i+i;
#ifdef MR_NOASM               
                dble=(mr_large)x[i]*x[i]+carry+w0[ti-1];
                w0[ti-1]=(mr_small)dble;
                carry=MR_TOP(dble);
#else
                muldvd2(x[i],x[i],&carry,&w0[ti-1]);
#endif
                w0[ti]+=carry;
                if (w0[ti]<carry) carry=1;
                else              carry=0;
            }
#endif
        }
        else for (i=1;i<=xl;i++)
        { /* long multiplication */
       /* inline - substitutes for loop below */
#if INLINE_ASM == 1
            ASM cld
            ASM mov cx,yl
            ASM mov dx,i
            ASM shl dx,1
#ifdef MR_LMM
            ASM push ds
            ASM push es
            ASM les bx,DWORD PTR w0
            ASM add bx,dx
            ASM lds si,DWORD PTR x
            ASM add si,dx
            ASM mov di,[si]
            ASM lds si,DWORD PTR y
#else
            ASM mov bx,w0
            ASM add bx,dx
            ASM mov si,x
            ASM add si,dx
            ASM mov di,[si]
            ASM mov si,y
#endif
            ASM inc si
            ASM inc si
            ASM push bp
            ASM xor bp,bp
          tcl6:
            ASM lodsw
            ASM mul di
            ASM add ax,bp
            ASM adc dx,0
#ifdef MR_LMM
            ASM add es:[bx],ax
#else
            ASM add [bx],ax
#endif
            ASM inc bx
            ASM inc bx
            ASM adc dx,0
            ASM mov bp,dx
            ASM loop tcl6

#ifdef MR_LMM
            ASM mov es:[bx],bp
            ASM pop bp
            ASM pop es
            ASM pop ds
#else
            ASM mov [bx],bp
            ASM pop bp
#endif
#endif
#if INLINE_ASM == 2
            ASM cld
            ASM mov cx,yl
            ASM mov dx,i
            ASM shl dx,2
#ifdef MR_LMM
            ASM push ds
            ASM push es
            ASM les bx,DWORD PTR w0
            ASM add bx,dx
            ASM lds si,DWORD PTR x
            ASM add si,dx
            ASM mov edi,[si]
            ASM lds si,DWORD PTR y
#else           
            ASM mov bx,w0
            ASM add bx,dx
            ASM mov si,x
            ASM add si,dx
            ASM mov edi,[si]
            ASM mov si,y
#endif
            ASM add si,4
            ASM push ebp
            ASM xor ebp,ebp
          tcl6:
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
            ASM loop tcl6

#ifdef MR_LMM
            ASM mov es:[bx],ebp
            ASM pop ebp
            ASM pop es
            ASM pop ds
#else
            ASM mov [bx],ebp
            ASM pop ebp
#endif
#endif
#if INLINE_ASM == 3
            ASM mov ecx,yl
            ASM mov esi,i
            ASM shl esi,2
            ASM mov ebx,x
            ASM add ebx,esi
            ASM mov edi,[ebx]
            ASM mov ebx,w0
            ASM add ebx,esi
            ASM mov esi,y
            ASM add esi,4
            ASM sub ebx,esi
            ASM sub ebx,4
            ASM push ebp
            ASM xor ebp,ebp
          tcl6:
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
            ASM jnz tcl6

            ASM mov [esi+ebx+4],ebp
            ASM pop ebp
#endif
#if INLINE_ASM == 4
   ASM ("
           movl %0,%%ecx\n
           movl %1,%%esi\n
           shll $2,%%esi\n
           movl %2,%%ebx\n
           addl %%esi,%%ebx\n
           movl (%%ebx),%%edi\n
           movl %3,%%ebx\n
           addl %%esi,%%ebx\n
           movl %4,%%esi\n
           addl $4,%%esi\n
           subl %%esi,%%ebx\n
           subl $4,%%ebx\n
           pushl %%ebp\n
           xorl %%ebp,%%ebp\n
         tcl6:\n
           movl (%%esi),%%eax\n
           addl $4,%%esi\n 
           mull %%edi\n
           addl %%ebp,%%eax\n
           movl (%%esi,%%ebx),%%ebp\n
           adcl $0,%%edx\n
           addl %%eax,%%ebp\n 
           adcl $0,%%edx\n
           movl %%ebp,(%%esi,%%ebx)
           decl %%ecx\n
           movl %%edx,%%ebp\n
           jnz tcl6\n   

           movl %%ebp,4(%%esi,%%ebx)\n
           popl %%ebp\n
        "
        :
        :"g"(yl),"g"(i),"g"(x),"g"(w0),"g"(y)
        :"eax","edi","esi","ebx","ecx","edx","memory"
       );
#endif
#ifndef INLINE_ASM
            carry=0;
            for (j=1;j<=yl;j++)
            { /* multiply each digit of y by x[i] */
#ifdef MR_NOASM 
                dble=(mr_large)x[i]*y[j]+carry+w0[i+j-1];
                w0[i+j-1]=(mr_small)dble;
                carry=MR_TOP(dble);
#else
                muldvd2(x[i],y[j],&carry,&w0[i+j-1]);
#endif
            }
            w0[yl+i]=carry;
#endif
        }
    }
    else
    {
        if (x==y)
        { /* squaring can be done nearly twice as fast */
            for (i=1;i<xl;i++)
            { /* long multiplication */
                carry=0;
                for (j=i+1;j<=xl;j++)
                { /* Only do above the diagonal */
#ifdef MR_NOASM
                   dble=(mr_large)x[i]*x[j]+w0[i+j-1]+carry;
                   carry=(mr_small)(dble/mr_mip->base);
                   w0[i+j-1]=(mr_small)(dble-(mr_large)carry*mr_mip->base);
#else
              carry=muldiv(x[i],x[j],w0[i+j-1]+carry,mr_mip->base,&w0[i+j-1]);
#endif
                }
                w0[xl+i]=carry;
            }
            w0[0]=xl+xl-1;
            mr_padd(_MIPP_ w0,w0,w0);     /* double it */
            carry=0;
            for (i=1;i<=xl;i++)
            { /* add in squared elements */
                ti=i+i;
#ifdef MR_NOASM
                dble=(mr_large)x[i]*x[i]+w0[ti-1]+carry;
                carry=(mr_small)(dble/mr_mip->base);
                w0[ti-1]=(mr_small)(dble-(mr_large)carry*mr_mip->base);
#else
                carry=muldiv(x[i],x[i],w0[ti-1]+carry,mr_mip->base,&w0[ti-1]);
#endif
                w0[ti]+=carry;
                carry=0;
                if (w0[ti]>=mr_mip->base)
                {
                    carry=1;
                    w0[ti]-=mr_mip->base;
                }
            }
        }
        else for (i=1;i<=xl;i++)
        { /* long multiplication */
            carry=0; 
            for (j=1;j<=yl;j++)
            { /* multiply each digit of y by x[i] */
#ifdef MR_NOASM
                dble=(mr_large)x[i]*y[j]+w0[i+j-1]+carry;
                carry=(mr_small)(dble/mr_mip->base);
                w0[i+j-1]=(mr_small)(dble-(mr_large)carry*mr_mip->base);
#else
                carry=muldiv(x[i],y[j],w0[i+j-1]+carry,mr_mip->base,&w0[i+j-1]);
#endif
            }
            w0[yl+i]=carry;
        }
    }
    w0[0]=(sz|(xl+yl)); /* set length and sign of result */
    mr_lzero(w0);
    copy(w0,z);
    MR_OUT
}

void divide(_MIPD_ big x,big y,big z)
{  /*  divide two big numbers  z=x/y : x=x mod y  *
    *  returns quotient only if  divide(x,y,x)    *
    *  returns remainder only if divide(x,y,y)    */
    mr_small carry,attemp,ldy,sdy,ra,r,d,tst,psum,sx,sy,sz;
    mr_small borrow,dig;
    int i,k,m,x0,y0,w00;
    big w0;
#ifdef MR_NOASM
    mr_large dble;
#endif
    BOOL check;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    w0=mr_mip->w0;

    MR_IN(6)

    if (x==y) mr_berror(_MIPP_ MR_ERR_BAD_PARAMETERS);
#ifdef MR_FLASH
    if (mr_notint(x) || mr_notint(y)) mr_berror(_MIPP_ MR_ERR_INT_OP);
#endif
    if (y[0]==0) mr_berror(_MIPP_ MR_ERR_DIV_BY_ZERO);
    if (mr_mip->ERNUM)
    {
        MR_OUT
        return;
    }
    sx=(x[0]&MR_MSBIT);   /*  extract signs ... */
    sy=(y[0]&MR_MSBIT);
    sz=(sx^sy);
    x[0]&=MR_OBITS;   /* ... and force operands to positive  */
    y[0]&=MR_OBITS;
    x0=(int)x[0];
    y0=(int)y[0];
    copy(x,w0);
    w00=(int)w0[0];
    if (mr_mip->check && (w00-y0+1>mr_mip->nib))
    {
        mr_berror(_MIPP_ MR_ERR_OVERFLOW);
        MR_OUT
        return;
    }
    d=0;
    if (x0==y0)
    {
        if (x0==1) /* special case - x and y are both mr_smalls */
        { 
            d=w0[1]/y[1];
            w0[1]=(w0[1]%y[1]);
            mr_lzero(w0);
        }
        else if (w0[x0]/4<y[x0])
        while (compare(w0,y)>=0)
        {  /* mr_small quotient - so do up to four subtracts instead */
            mr_psub(_MIPP_ w0,y,w0);
            d++;
        }
    }
    if (compare(w0,y)<0)
    {  /*  x less than y - so x becomes remainder */
        if (x!=z)  /* testing parameters */
        {
            copy(w0,x);
            if (x[0]!=0) x[0]|=sx;
        }
        if (y!=z)
        {
            zero(z);
            z[1]=d;
            if (d>0) z[0]=(sz|1);
        }
        y[0]|=sy;
        MR_OUT
        return;
    }
    if (y0==1)
    {  /* y is int - so use subdiv instead */
        r=mr_sdiv(_MIPP_ w0,y[1],w0);
        if (y!=z)
        {
            copy(w0,z);
            z[0]|=sz;
        }
        if (x!=z)
        {
            zero(x);
            x[1]=r;
            if (r>0) x[0]=(sx|1);
        }
        y[0]|=sy;
        MR_OUT
        return;
    }
    if (y!=z) zero(z);
    d=normalise(_MIPP_ y,y);
    check=mr_mip->check;
    mr_mip->check=OFF;
    if (mr_mip->base==0)
    {
        if (d!=1) mr_pmul(_MIPP_ w0,d,w0);
        ldy=y[y0];
        sdy=y[y0-1];
        for (k=w00;k>=y0;k--)
        {  /* long division */

#if INLINE_ASM == 1
#ifdef MR_LMM
            ASM push ds
            ASM lds bx,DWORD PTR w0
#else
            ASM mov bx,w0
#endif
            ASM mov si,k
            ASM shl si,1
            ASM add bx,si
            ASM mov dx,[bx+2]
            ASM mov ax,[bx]
            ASM cmp dx,ldy
            ASM jne tcl8
            ASM mov di,0xffff
            ASM mov si,ax
            ASM add si,ldy
            ASM jc tcl12
            ASM jmp tcl10
          tcl8:
            ASM div WORD PTR ldy
            ASM mov di,ax
            ASM mov si,dx
          tcl10:
            ASM mov ax,sdy
            ASM mul di
            ASM cmp dx,si
            ASM jb tcl12
            ASM jne tcl11
            ASM cmp ax,[bx-2]
            ASM jbe tcl12
          tcl11:
            ASM dec di
            ASM add si,ldy
            ASM jnc tcl10
          tcl12:
            ASM mov attemp,di
#ifdef MR_LMM
            ASM pop ds
#endif
#endif
/* NOTE push and pop of esi/edi should not be necessary - Borland C bug *
 * These pushes are needed here even if register variables are disabled */
#if INLINE_ASM == 2
            ASM push esi
            ASM push edi
#ifdef MR_LMM
            ASM push ds
            ASM lds bx,DWORD PTR w0
#else
            ASM mov bx,w0
#endif
            ASM mov si,k
            ASM shl si,2
            ASM add bx,si
            ASM mov edx,[bx+4]
            ASM mov eax,[bx]
            ASM cmp edx,ldy
            ASM jne tcl8
            ASM mov edi,0xffffffff
            ASM mov esi,eax
            ASM add esi,ldy
            ASM jc tcl12
            ASM jmp tcl10
          tcl8:
            ASM div DWORD PTR ldy
            ASM mov edi,eax
            ASM mov esi,edx
          tcl10:
            ASM mov eax,sdy
            ASM mul edi
            ASM cmp edx,esi
            ASM jb tcl12
            ASM jne tcl11
            ASM cmp eax,[bx-4]
            ASM jbe tcl12
          tcl11:
            ASM dec edi
            ASM add esi,ldy
            ASM jnc tcl10
          tcl12:
            ASM mov attemp,edi
#ifdef MR_LMM
            ASM pop ds
#endif
            ASM pop edi
            ASM pop esi
#endif  
#if INLINE_ASM == 3
            ASM push esi
            ASM push edi
            ASM mov ebx,w0
            ASM mov esi,k
            ASM shl esi,2
            ASM add ebx,esi
            ASM mov edx,[ebx+4]
            ASM mov eax,[ebx]
            ASM cmp edx,ldy
            ASM jne tcl8
            ASM mov edi,0xffffffff
            ASM mov esi,eax
            ASM add esi,ldy
            ASM jc tcl12
            ASM jmp tcl10
          tcl8:
            ASM div DWORD PTR ldy
            ASM mov edi,eax
            ASM mov esi,edx
          tcl10:
            ASM mov eax,sdy
            ASM mul edi
            ASM cmp edx,esi
            ASM jb tcl12
            ASM jne tcl11
            ASM cmp eax,[ebx-4]
            ASM jbe tcl12
          tcl11:
            ASM dec edi
            ASM add esi,ldy
            ASM jnc tcl10
          tcl12:
            ASM mov attemp,edi
            ASM pop edi
            ASM pop esi
#endif       
#if INLINE_ASM == 4
   ASM ("
           movl %1,%%ebx\n
           movl %2,%%esi\n
           shll $2,%%esi\n
           addl %%esi,%%ebx\n
           movl 4(%%ebx),%%edx\n
           movl (%%ebx),%%eax\n
           cmpl %3,%%edx\n
           jne tcl8\n
           movl $0xffffffff,%%edi\n
           movl %%eax,%%esi\n
           addl %3,%%esi
           jc tcl12\n
           jmp tcl10\n
         tcl8:\n
           divl %3\n
           movl %%eax,%%edi\n
           movl %%edx,%%esi\n
         tcl10:\n
           movl %4,%%eax\n
           mull %%edi\n
           cmpl %%esi,%%edx\n
           jb tcl12\n
           jne tcl11\n
           cmpl -4(%%ebx),%%eax\n
           jbe tcl12\n
         tcl11:\n
           decl %%edi\n
           addl %3,%%esi\n
           jnc tcl10\n
         tcl12:
           movl %%edi,%0\n
        "
        :"=g"(attemp)
        :"g"(w0),"g"(k),"g"(ldy),"g"(sdy)
        :"eax","edi","esi","ebx","ecx","edx","memory"
       );
#endif
#ifndef INLINE_ASM
            carry=0;
            if (w0[k+1]==ldy) /* guess next quotient digit */
            {
                attemp=(mr_small)(-1);
                ra=ldy+w0[k];
                if (ra<ldy) carry=1;
            }
#ifdef MR_NOASM
            else
            {
                MR_BOT(dble)=w0[k];
                MR_TOP(dble)=w0[k+1];
                attemp=(mr_small)(dble/ldy);
                ra=(mr_small)(dble-(mr_large)attemp*ldy);
            }
#else
            else attemp=muldvm(w0[k+1],w0[k],ldy,&ra);
#endif
            while (carry==0)
            {
#ifdef MR_NOASM
                dble=(mr_large)attemp*sdy;
                r=(mr_small)dble;
                tst=MR_TOP(dble);
#else
                tst=muldvd(sdy,attemp,(mr_small)0,&r);
#endif
                if (tst< ra || (tst==ra && r<=w0[k-1])) break;
                attemp--;  /* refine guess */
                ra+=ldy;
                if (ra<ldy) carry=1;
            }
#endif    
            m=k-y0;
            if (attemp>0)
            { /* do partial subtraction */
                borrow=0;
    /*  inline - substitutes for loop below */
#if INLINE_ASM == 1
                ASM cld
                ASM mov cx,y0
                ASM mov si,m
                ASM shl si,1
                ASM mov di,attemp
#ifdef MR_LMM
                ASM push ds
                ASM push es
                ASM les bx,DWORD PTR w0
                ASM add bx,si
                ASM lds si,DWORD PTR y
#else
                ASM mov bx,w0
                ASM add bx,si
                ASM mov si,y
#endif
                ASM inc si
                ASM inc si
                ASM push bp
                ASM xor bp,bp

             tcl3:
                ASM lodsw
                ASM mul di
                ASM add ax,bp
                ASM adc dx,0
                ASM inc bx
                ASM inc bx
#ifdef MR_LMM
                ASM sub es:[bx],ax
#else
                ASM sub [bx],ax
#endif              
                ASM adc dx,0
                ASM mov bp,dx
                ASM loop tcl3

                ASM mov ax,bp
                ASM pop bp
#ifdef MR_LMM
                ASM pop es
                ASM pop ds
#endif
                ASM mov borrow,ax
#endif
/* NOTE push and pop of esi/edi should not be necessary - Borland C bug *
 * These pushes are needed here even if register variables are disabled */
#if INLINE_ASM == 2
                ASM push esi
                ASM push edi
                ASM cld
                ASM mov cx,y0
                ASM mov si,m
                ASM shl si,2
                ASM mov edi,attemp
#ifdef MR_LMM
                ASM push ds
                ASM push es
                ASM les bx,DWORD PTR w0
                ASM add bx,si
                ASM lds si,DWORD PTR y
#else
                ASM mov bx,w0
                ASM add bx,si
                ASM mov si,y
#endif
                ASM add si,4
                ASM push ebp
                ASM xor ebp,ebp

             tcl3:
                ASM lodsd
                ASM mul edi
                ASM add eax,ebp
                ASM adc edx,0
                ASM add bx,4
#ifdef MR_LMM
                ASM sub es:[bx],eax
#else
                ASM sub [bx],eax
#endif
                ASM adc edx,0
                ASM mov ebp,edx
                ASM loop tcl3

                ASM mov eax,ebp
                ASM pop ebp
#ifdef MR_LMM
                ASM pop es
                ASM pop ds
#endif
                ASM mov borrow,eax
                ASM pop edi
                ASM pop esi
#endif
#if INLINE_ASM == 3
                ASM push esi
                ASM push edi
                ASM mov ecx,y0
                ASM mov esi,m
                ASM shl esi,2
                ASM mov edi,attemp
                ASM mov ebx,w0
                ASM add ebx,esi
                ASM mov esi,y
                ASM add esi,4
                ASM sub ebx,esi
                ASM push ebp
                ASM xor ebp,ebp

             tcl3:
                ASM mov eax,[esi]
                ASM add esi,4
                ASM mul edi
                ASM add eax,ebp
                ASM mov ebp,[esi+ebx]
                ASM adc edx,0
                ASM sub ebp,eax
                ASM adc edx,0
                ASM mov [esi+ebx],ebp
                ASM dec ecx
                ASM mov ebp,edx
                ASM jnz tcl3

                ASM mov eax,ebp
                ASM pop ebp
                ASM mov borrow,eax
                ASM pop edi
                ASM pop esi
#endif
#if INLINE_ASM == 4
   ASM ("
           movl %1,%%ecx\n
           movl %2,%%esi\n
           shll $2,%%esi\n
           movl %3,%%edi\n
           movl %4,%%ebx\n
           addl %%esi,%%ebx\n
           movl %5,%%esi\n
           addl $4,%%esi\n
           subl %%esi,%%ebx\n
           pushl %%ebp\n
           xorl %%ebp,%%ebp\n
         tcl3:\n
           movl (%%esi),%%eax\n
           addl $4,%%esi\n
           mull %%edi\n
           addl %%ebp,%%eax\n
           movl (%%esi,%%ebx),%%ebp\n
           adcl $0,%%edx\n
           subl %%eax,%%ebp\n
           adcl $0,%%edx\n
           movl %%ebp,(%%esi,%%ebx)\n
           decl %%ecx\n
           movl %%edx,%%ebp\n
           jnz tcl3\n
    
           movl %%ebp,%%eax\n
           popl %%ebp\n
           movl %%eax,%0\n
        "
        :"=g"(borrow)
        :"g"(y0),"g"(m),"g"(attemp),"g"(w0),"g"(y)
        :"eax","edi","esi","ebx","ecx","edx","memory"
       );
#endif
#ifndef INLINE_ASM
                for (i=1;i<=y0;i++)
                {
#ifdef MR_NOASM
                    dble=(mr_large)attemp*y[i]+borrow;
                    dig=(mr_small)dble;
                    borrow=MR_TOP(dble);
#else
                  borrow=muldvd(attemp,y[i],borrow,&dig);
#endif
                  if (w0[m+i]<dig) borrow++;
                  w0[m+i]-=dig;
                }
#endif
                if (w0[k+1]<borrow)
                {  /* whoops! - over did it */
                    w0[k+1]=0;
                    carry=0;
                    for (i=1;i<=y0;i++)
                    {  /* compensate for error ... */
                        psum=w0[m+i]+y[i]+carry;
                        if (psum>y[i]) carry=0;
                        if (psum<y[i]) carry=1;
                        w0[m+i]=psum;
                    }
                    attemp--;  /* ... and adjust guess */
                }
                else w0[k+1]-=borrow;
            }
            if (k==w00 && attemp==0) w00--;
            else if (y!=z) z[m+1]=attemp;
        }
    }
    else
    {   /* have to do it the hard way */
        if (d!=1) mr_pmul(_MIPP_ w0,d,w0);
        ldy=y[y0];
        sdy=y[y0-1];
        for (k=w00;k>=y0;k--)
        {  /* long division */
            if (w0[k+1]==ldy) /* guess next quotient digit */
            {
                attemp=mr_mip->base-1;
                ra=ldy+w0[k];
            }
#ifdef MR_NOASM
            else 
            {
                dble=(mr_large)w0[k+1]*mr_mip->base+w0[k];
                attemp=(mr_small)(dble/ldy);
                ra=(mr_small)(dble-(mr_large)attemp*ldy);
            }
#else
            else attemp=muldiv(w0[k+1],mr_mip->base,w0[k],ldy,&ra);
#endif
            while (ra<mr_mip->base)
            {
#ifdef MR_NOASM
                dble=(mr_large)sdy*attemp;
                tst=(mr_small)(dble/mr_mip->base);
                r=(mr_small)(dble-(mr_large)tst*mr_mip->base);
#else
                tst=muldiv(sdy,attemp,(mr_small)0,mr_mip->base,&r); 
#endif
                if (tst< ra || (tst==ra && r<=w0[k-1])) break;
                attemp--;  /* refine guess */
                ra+=ldy;
            }    
            m=k-y0;
            if (attemp>0)
            { /* do partial subtraction */
                borrow=0;
                for (i=1;i<=y0;i++)
                {
#ifdef MR_NOASM
                  dble=(mr_large)attemp*y[i]+borrow;
                  borrow=(mr_small)(dble/mr_mip->base);
                  dig=(mr_small)(dble-(mr_large)borrow*mr_mip->base);
#else
                  borrow=muldiv(attemp,y[i],borrow,mr_mip->base,&dig);
#endif
                  if (w0[m+i]<dig)
                  { /* set borrow */
                      borrow++;
                      w0[m+i]+=(mr_mip->base-dig);
                  }
                  else w0[m+i]-=dig;
                }
                if (w0[k+1]<borrow)
                {  /* whoops! - over did it */
                    w0[k+1]=0;
                    carry=0;
                    for (i=1;i<=y0;i++)
                    {  /* compensate for error ... */
                        psum=w0[m+i]+y[i]+carry;
                        carry=0;
                        if (psum>=mr_mip->base)
                        {
                            carry=1;
                            psum-=mr_mip->base;
                        }
                        w0[m+i]=psum;
                    }
                    attemp--;  /* ... and adjust guess */
                }
                else w0[k+1]-=borrow;
            }
            if (k==w00 && attemp==0) w00--;
            else if (y!=z) z[m+1]=attemp;
        }
    }
    if (y!=z) z[0]=((w00-y0+1)|sz); /* set sign and length of result */
    w0[0]=y0;
    mr_lzero(y);
    mr_lzero(z);
    if (x!=z)
    {
        mr_lzero(w0);
        if (d!=1) mr_sdiv(_MIPP_ w0,d,x);
        else copy(w0,x);
        if (x[0]!=0) x[0]|=sx;
    }
    if (d!=1) mr_sdiv(_MIPP_ y,d,y);
    y[0]|=sy;
    mr_mip->check=check;
    MR_OUT
}

BOOL divisible(_MIPD_ big x,big y)
{ /* returns y|x, that is TRUE if y divides x exactly */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return FALSE;

    MR_IN(87)

    copy (x,mr_mip->w0);
    divide(_MIPP_ mr_mip->w0,y,y);

    MR_OUT
    if (size(mr_mip->w0)==0) return TRUE;
    else                    return FALSE;
}     

void mad(_MIPD_ big x,big y,big z,big w,big q,big r)
{ /* Multiply, Add and Divide; q=(x*y+z)/w remainder r   *
   * returns remainder only if w=q, quotient only if q=r *
   * add done only if x, y and z are distinct.           */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(24)

    mr_mip->check=OFF;           /* turn off some error checks */
    if (w==r)
    {
        mr_berror(_MIPP_ MR_ERR_BAD_PARAMETERS);
        MR_OUT
        return;
    }
    multiply(_MIPP_ x,y,mr_mip->w0);
    if (x!=z && y!=z) add_r(_MIPP_ mr_mip->w0,z,mr_mip->w0);

    divide(_MIPP_ mr_mip->w0,w,q);
    if (q!=r) copy(mr_mip->w0,r);
    mr_mip->check=ON;
    MR_OUT
}

