/*
 *   MIRACL routines for arithmetic over GF(2^m), and 
 *   implementation of Elliptic Curve Cryptography over GF(2^m) 
 *   mrgf2.c
 *
 *   Curve equation is Y^2 + XY = X^3 + A.X^2 + B
 *   where A is 0 or 1
 *
 *   For algorithms used, see IEEE P1363 Standard, Appendix A
 *   unless otherwise stated.
 * 
 *   The time-critical routines are the multiplication routine multiply2()
 *   and (for AFFINE co-ordinates), the modular inverse routine inverse2() 
 *   and the routines it calls.
 *
 *   No assembly language used.
 *
 *   Copyright (c) 2000 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>
#include <time.h>

#define TOPBIT (mr_small)1<<(MIRACL-1)
#define SECBIT (mr_small)1<<(MIRACL-2)

#define M1 (MIRACL-1)
#define M2 (MIRACL-2)
#define M8 (MIRACL-8)

static mr_small look[16]=
{0,1<<M8,4<<M8,5<<M8,16<<M8,17<<M8,20<<M8,21<<M8,64<<M8,
       65<<M8,68<<M8,69<<M8,80<<M8,81<<M8,84<<M8,85<<M8};

/* This is extremely time-critical, and expensive */

/* wouldn't it be nice if instruction sets supported a 
   one cycle "carry-free" multiplication instruction ... */

static mr_small mr_mul2(mr_small a,mr_small b,mr_small *r)
{
	/* Roger 26.02.2001 Unreferenzierte Variable
    int k;
	*/
    mr_small kb,x,q,p,t[4];
    mr_utype tb;
    q=p=(mr_small)0;

    if (b<a) {x=a; a=b; b=x;}   /* make sure a is smaller */

    if (a==0) 
    {
        *r=p;
        return q;
    }

    t[0]=0;              /* small look up table */
    t[2]=a<<1;           /* it can overflow.... */
    t[1]=t[2]>>1;
    t[3]=t[1]^t[2];

    kb=b;
    tb=(a&TOPBIT);       /* remember top bit    */

#if MIRACL == 32
    p=q=t[b&3];                       q>>=2;
    x=t[(b>>2)&3];  q^=x; p^=(x<<2);  q>>=2;   /* 8 ASM instructions */
    x=t[(b>>4)&3];  q^=x; p^=(x<<4);  q>>=2;
    x=t[(b>>6)&3];  q^=x; p^=(x<<6);  q>>=2;
    x=t[(b>>8)&3];  q^=x; p^=(x<<8);  q>>=2;
    x=t[(b>>10)&3]; q^=x; p^=(x<<10); q>>=2;
    x=t[(b>>12)&3]; q^=x; p^=(x<<12); q>>=2;
    x=t[(b>>14)&3]; q^=x; p^=(x<<14); q>>=2;
    x=t[(b>>16)&3]; q^=x; p^=(x<<16); q>>=2;
    x=t[(b>>18)&3]; q^=x; p^=(x<<18); q>>=2;
    x=t[(b>>20)&3]; q^=x; p^=(x<<20); q>>=2;
    x=t[(b>>22)&3]; q^=x; p^=(x<<22); q>>=2;
    x=t[(b>>24)&3]; q^=x; p^=(x<<24); q>>=2;
    x=t[(b>>26)&3]; q^=x; p^=(x<<26); q>>=2;
    x=t[(b>>28)&3]; q^=x; p^=(x<<28); q>>=2;
    x=t[(b>>30)];   q^=x; p^=(x<<30); q>>=2;
#else
    for (k=0;k<MIRACL;k+=8)
    {                 
        q^=(t[b&3]);   
        b>>=2; 
        p>>=2; 
        p|=q<<M2;
        q>>=2;

        q^=(t[b&3]);
        b>>=2;
        p>>=2;
        p|=q<<M2;
        q>>=2;

        q^=(t[b&3]);
        b>>=2;
        p>>=2;
        p|=q<<M2;
        q>>=2;

        q^=(t[b&3]);
        b>>=2;
        p>>=2;
        p|=q<<M2;
        q>>=2;
    }

#endif

    p^=(tb&(kb<<M1));       /* compensate for top bit */
    q^=((tb>>M1)&(kb>>1));  /* don't break pipleine.. */

    *r=p;
    return q;
}

static mr_small mr_sqr2(mr_small a,mr_small *r)
{ /* squaring is linear O(n), and not time-critical */
    int i;
    mr_small t,q;
    q=0; *r=0;
    
  /* simply insert a 0 between bits - look-up table is a bit faster */

    for (i=0;i<MIRACL/2;i+=4)
    {
        t=look[a&0xF];
        a>>=4;
        *r>>=8;
        *r|=t;
    }

    for (i=0;i<MIRACL/2;i+=4)
    {
        t=look[a&0xF];
        a>>=4;
        q>>=8;
        q|=t;
    }

    return q;
}

static int numbits(big x)
{ /* return degree of x */
    mr_small bit=TOPBIT;
    int m,k=x[0];
    if (k==0) return 0;
    m=k*MIRACL;
    while (!(x[k]&bit))
    {
        m--;
        bit>>=1;
    }
    return m;
}

static int zerobits(big x)
{ /* return number of zero bits at the end of x */
    int m,n,k;
    mr_small bit=1;
    k=x[0]; 
    if (k==0) return (-1);
    for (m=1;m<=k;m++)
    {
        if (x[m]==0) continue;
        n=0;
        while (!(bit&x[m]))
        {
            n++; 
            bit<<=1;
        }
        break;
    }
    return (MIRACL*(m-1)+n);
}

static void shiftrightbits(big x,int m)
{
    int i,k=x[0];
    int w=m/MIRACL;  /* words */
    int b=m%MIRACL;  /* bits  */
    if (k==0 || m==0) return;
    if (w>0)
    {
        for (i=1;i<=k-w;i++)
            x[i]=x[i+w];
        for (i=k-w+1;i<=k;i++) x[i]=0;
        x[0]-=w;
    }
/* time critical */
    if (b!=0) 
    {
        for (i=1;i<=k-w-1;i++)
            x[i]=(x[i]>>b)|x[i+1]<<(MIRACL-b);   
        x[k-w]>>=b;
        if (x[k-w]==0) x[0]--;
    }
}

static void shiftleftbits(big x,int m)
{
    int i,j,k=x[0];
    int w=m/MIRACL;  /* words */
    int b=m%MIRACL;  /* bits  */
    if (k==0 || m==0) return;
    if (w>0)
    {
        for (i=k+w;i>w;i--)
            x[i]=x[i-w];
        for (i=w;i>0;i--) x[i]=0;
        x[0]+=w;
    }
/* time critical */
    if (b!=0) 
    {
        j=x[k+w]>>(MIRACL-b);
        if (j!=0)
        {
            x[0]++;
            x[k+w+1]=j;
        }
        for (i=k+w;i>w+1;i--)
        {
            x[i]=(x[i]<<b)|x[i-1]>>(MIRACL-b);
        }
        x[w+1]<<=b;
    }
}

static void square2(big x,big w)
{ /* w=x*x */
    int i,n;
    mr_small a,b;
    if (x!=w) copy(x,w);
    n=w[0];
    w[0]=2*n;
    for (i=n;i>=1;i--)
    {
        a=mr_sqr2(x[i],&b);
        w[i+i-1]=b;
        w[i+i]=a;
    }
    mr_lzero(w);
}


/* Use katatsuba to multiply two polynomial with coefficients in GF(2^m) */

void karmul2_poly(_MIPD_ int n,big *t,big *x,big *y,big *z)
{
    int m,nd2,nd,md,md2;                          

    if (n==1) 
    { /* finished */
        modmult2(_MIPP_ *x,*y,*z);
        zero(z[1]);
        return;
    }       
    if (n==2)
    {  /* in-line 2x2 */
        modmult2(_MIPP_ x[0],y[0],z[0]);
        modmult2(_MIPP_ x[1],y[1],z[2]);
        add2(x[0],x[1],t[0]);
        add2(y[0],y[1],t[1]);
        modmult2(_MIPP_ t[0],t[1],z[1]);
        add2(z[1],z[0],z[1]);
        add2(z[1],z[2],z[1]);
        zero(z[3]);
        return;
    }
    if (n%2==0)
    {
        md=nd=n;
        md2=nd2=n/2;
    }
    else
    {
        nd=n+1;
        md=n-1;
        nd2=nd/2; md2=md/2;
    }

    for (m=0;m<nd2;m++)
    {
        copy(x[m],z[m]);
        copy(y[m],z[nd2+m]);
    }
    for (m=0;m<md2;m++)
    { 
        add2(z[m],x[nd2+m],z[m]);
        add2(z[nd2+m],y[nd2+m],z[nd2+m]);
    }

    karmul2_poly(_MIPP_ nd2,&t[nd],z,&z[nd2],t); 

    karmul2_poly(_MIPP_ nd2,&t[nd],x,y,z);  

    for (m=0;m<nd;m++) add2(t[m],z[m],t[m]);

    karmul2_poly(_MIPP_ md2,&t[nd],&x[nd2],&y[nd2],&z[nd]);

    for (m=0;m<md;m++) add2(t[m],z[nd+m],t[m]);
    for (m=0;m<nd;m++) add2(z[nd2+m],t[m],z[nd2+m]);
}

void karmul2_poly_upper(_MIPD_ int n,big *t,big *x,big *y,big *z)
{ /* n is large and even, and upper half of z is known already */
    int m,nd2,nd;
    nd2=n/2; nd=n;

    for (m=0;m<nd2;m++)
    { 
        add2(x[m],x[nd2+m],z[m]);
        add2(y[m],y[nd2+m],z[nd2+m]);
    }

    karmul2_poly(_MIPP_ nd2,&t[nd],z,&z[nd2],t); 

    karmul2_poly(_MIPP_ nd2,&t[nd],x,y,z);   /* only 2 karmuls needed! */

    for (m=0;m<nd;m++) add2(t[m],z[m],t[m]);

    for (m=0;m<nd2;m++) 
    {
        add2(z[nd+m],z[nd+nd2+m],z[nd+m]);
        add2(z[nd+m],t[nd2+m],z[nd+m]);
    }

    for (m=0;m<nd;m++) 
    {
        add2(t[m],z[nd+m],t[m]);
        add2(z[nd2+m],t[m],z[nd2+m]);
    }
}

/* Some in-line karatsuba down at the bottom... */

static void mr_bottom1(big x,big y,big z)
{
    z[1]=mr_mul2(x[0],y[0],&z[0]);
}

static void mr_bottom2(big x,big y,big z)
{
    mr_small q0,r0,q1,r1,q2,r2;

    q0=mr_mul2(x[0],y[0],&r0);
    q1=mr_mul2(x[1],y[1],&r1);
    q2=mr_mul2(x[0]^x[1],y[0]^y[1],&r2);

    z[0]=r0;
    z[1]=q0^r1^r0^r2;
    z[2]=q0^r1^q1^q2;
    z[3]=q1;
}

static void mr_bottom3(big x,big y,big z)
{ /* this can be done in 6 mr_muls! */
    mr_small q0,r0,q1,r1,q2,r2,tx,ty;
    mr_small xx0,yy0,xx1,yy1,t0,t1,t2,t3;

    q0=mr_mul2(x[0],y[0],&r0);

    q1=mr_mul2(x[1],y[1],&r1);

    tx=x[0]^x[1];
    ty=y[0]^y[1];
    q2=mr_mul2(tx,ty,&r2);

    z[0]=r0;
    z[1]=q0^r1^r0^r2;
    z[2]=q0^r1^q1^q2;
    z[3]=q1;

    q0=mr_mul2(x[2],y[2],&r0);
    z[4]=r0;
    z[5]=q0;

    xx0=x[2]^x[0];
    yy0=y[2]^y[0];
    q0=mr_mul2(xx0,yy0,&r0);
   
    xx1=x[1];
    yy1=y[1];
    q1=mr_mul2(xx1,yy1,&r1);

    tx=xx0^xx1;
    ty=yy0^yy1;
    q2=mr_mul2(tx,ty,&r2);

    t0=z[0]^z[4]^r0;
    t1=z[1]^z[5]^q0^r1^r0^r2;
    t2=z[2]^q0^r1^q1^q2;
    t3=z[3]^q1; 

    z[2]^=t0;
    z[3]^=t1;
    z[4]^=t2;
    z[5]^=t3;
}

static void mr_bottom4(big x,big y,big z)
{ /* unwound 4x4 karatsuba multiplication - only 9 muls */
    mr_small q0,r0,q1,r1,q2,r2,tx,ty;
    mr_small xx0,yy0,xx1,yy1,t0,t1,t2,t3;
    q0=mr_mul2(x[0],y[0],&r0);

    q1=mr_mul2(x[1],y[1],&r1);

    tx=x[0]^x[1];
    ty=y[0]^y[1];
    q2=mr_mul2(tx,ty,&r2);

    z[0]=r0;
    z[1]=q0^r1^r0^r2;
    z[2]=q0^r1^q1^q2;
    z[3]=q1;

    q0=mr_mul2(x[2],y[2],&r0);

    q1=mr_mul2(x[3],y[3],&r1);

    tx=x[2]^x[3];
    ty=y[2]^y[3];
    q2=mr_mul2(tx,ty,&r2);

    z[4]=r0;
    z[5]=q0^r1^r0^r2;
    z[6]=q0^r1^q1^q2;
    z[7]=q1;

    xx0=x[2]^x[0];
    yy0=y[2]^y[0];
    q0=mr_mul2(xx0,yy0,&r0);
   
    xx1=x[3]^x[1];
    yy1=y[3]^y[1];
    q1=mr_mul2(xx1,yy1,&r1);

    tx=xx0^xx1;
    ty=yy0^yy1;
    q2=mr_mul2(tx,ty,&r2);

    t0=z[0]^z[4]^r0;
    t1=z[1]^z[5]^q0^r1^r0^r2;
    t2=z[2]^z[6]^q0^r1^q1^q2;
    t3=z[3]^z[7]^q1; 

    z[2]^=t0;
    z[3]^=t1;
    z[4]^=t2;
    z[5]^=t3;
}

void karmul2(int n,big t,big x,big y,big z)
{ /* Karatsuba multiplication - note that n can be odd or even */
    int m,nd2,nd,md,md2;

    if (n<=4)
    {
        if (n==1)
        {
            mr_bottom1(x,y,z);
            return;
        }
        if (n==2)
        {   
            mr_bottom2(x,y,z);
            return;
        }
        if (n==3)
        {   
            mr_bottom3(x,y,z);
            return;
        }
        if (n==4)
        {   
            mr_bottom4(x,y,z);
            return;
        }
    }
    if (n%2==0)
    {
        md=nd=n;
        md2=nd2=n/2;
    }
    else
    {
        nd=n+1;
        md=n-1;
        nd2=nd/2; md2=md/2;
    }

    for (m=0;m<nd2;m++)
    {
        z[m]=x[m];
        z[nd2+m]=y[m];
    }
    for (m=0;m<md2;m++)
    {
        z[m]^=x[nd2+m];
        z[nd2+m]^=y[nd2+m];
    }

    karmul2(nd2,&t[nd],z,&z[nd2],t); 
    karmul2(nd2,&t[nd],x,y,z);  

    for (m=0;m<nd;m++) t[m]^=z[m];

    karmul2(md2,&t[nd],&x[nd2],&y[nd2],&z[nd]);

    for (m=0;m<md;m++) t[m]^=z[nd+m];
    for (m=0;m<nd;m++) z[nd2+m]^=t[m];
}

/* this is time-critical, so use karatsuba here, since addition is cheap *
 * and easy (no carries to worry about...)                               */

void multiply2(_MIPD_ big x,big y,big w)
{
    int i,j,xl,yl,ml;
    mr_small p,q;

#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

    big w0=mr_mip->w0;

    if (x==NULL || y==NULL)
    {
        zero(w);
        return;
    }
    if (x[0]==0 || y[0]==0)
    {
        zero(w);
        return;
    }

    xl=x[0];
    yl=y[0];
    zero(w0);

    if (xl>=4 && yl>=4)
    { /* Use Karatsuba */
        if (xl>yl) ml=xl;
        else       ml=yl;
     
        karmul2(ml,&mr_mip->w7[1],&x[1],&y[1],&w0[1]);  /* w7 is work-space */

        mr_mip->w7[0]=w0[0]=2*ml+1;
        mr_lzero(w0);
        mr_lzero(mr_mip->w7);
        copy(w0,w);
        return;
    }

    w0[0]=xl+yl;
    for (i=1;i<=xl;i++)
    { /* slow old-fashioned O(n^2) way */
        for (j=1;j<=yl;j++)
        {
            q=mr_mul2(x[i],y[j],&p); 
            w0[i+j-1]^=p;
            w0[i+j]^=q;
        } 
    }
    mr_lzero(w0);
    copy(w0,w);
}

void add2(big x,big y,big z)
{ /* XOR x and y */
    int i,lx,ly,lz,lm;

    if (x==y)
    {
        zero(z);
        return;
    }
    if (y==NULL)
    {
        copy(x,z);
        return;
    }
    else if (x==NULL) 
    {
        copy(y,z);
        return;
    }

    lx=x[0]; ly=y[0]; lz=z[0];
    lm=lx; if (ly>lx) lm=ly;

    for (i=1;i<=lm;i++)
        z[i]=x[i]^y[i];
    z[0]=lm;
    for (i=lm+1;i<=lz;i++)
        z[i]=0;
    if (lx==ly) mr_lzero(z);
}

static void remain2(_MIPD_ big y,big x)
{ /* generic "remainder" program. x%=y */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    int my=numbits(y);
    while (numbits(x)>=my)
    {
        copy(y,mr_mip->w7);
        shiftleftbits(mr_mip->w7,numbits(x)-my);
        add2(x,mr_mip->w7,x);    
    }
    return;
}

static void gcd2(_MIPD_ big x,big y,big g)
{
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (size(y)==0) 
    {
        copy(x,g);
        return;
    }
    copy(x,mr_mip->w1);
    copy(y,mr_mip->w2);
    forever
    {
        remain2(_MIPP_ mr_mip->w2,mr_mip->w1);
        if (size(mr_mip->w1)==0) break;
        copy(mr_mip->w1,mr_mip->w3);
        copy(mr_mip->w2,mr_mip->w1);
        copy(mr_mip->w3,mr_mip->w2);
    }
    copy(mr_mip->w2,g);
}


/* See "Elliptic Curves in Cryptography", Blake, Seroussi & Smart, 
   Cambridge University Press, 1999, page 20, for this fast reduction
   routine - algorithm II.9 */

void reduce2(_MIPD_ big y,big x)
{ /* reduction wrt the trinomial or pentanomial modulus        *
   * Note that this is linear O(n), and thus not time critical */
    int k1,k2,k3,k4,ls1,ls2,ls3,ls4,rs1,rs2,rs3,rs4,i;
    int M,A,B,C;
    int xl=x[0];
    mr_small top;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

    copy(y,x);

    M=mr_mip->M;
    if (numbits(x)<=M) return;

    A=mr_mip->AA;
    B=mr_mip->BB;
    C=mr_mip->CC;

    k1=1+M/MIRACL;       /* words from MSB to LSB */
    rs1=M%MIRACL;
    ls1=MIRACL-rs1;

    if (M-A < MIRACL)
    { /* slow way */
        while (numbits(x)>=M+1)
        {
            copy(mr_mip->modulus,mr_mip->w7);
            shiftleftbits(mr_mip->w7,numbits(x)-M-1);
            add2(x,mr_mip->w7,x);    
        }
        return;
    }

    k2=1+(M-A)/MIRACL;   /* words from MSB to bit */
    rs2=(M-A)%MIRACL;
    ls2=MIRACL-rs2;

    if (B)
    { /* Pentanomial */
        k3=1+(M-B)/MIRACL;
        rs3=(M-B)%MIRACL;
        ls3=MIRACL-rs3;

        k4=1+(M-C)/MIRACL;
        rs4=(M-C)%MIRACL;
        ls4=MIRACL-rs4;
    }

    for (i=xl;i>k1;i--)
    {
        if (rs1==0) x[i-k1+1]^=x[i];
        else
        {
            x[i-k1+1]^=(x[i]>>rs1);
            x[i-k1]^=(x[i]<<ls1);
        }
        if (rs2==0) x[i-k2+1]^=x[i];
        else
        {
            x[i-k2+1]^=(x[i]>>rs2);
            x[i-k2]^=(x[i]<<ls2);
        }
        if (B)
        {
            if (rs3==0) x[i-k3+1]^=x[i];
            else
            {
                x[i-k3+1]^=(x[i]>>rs3);
                x[i-k3]^=(x[i]<<ls3);
            }
            if (rs4==0) x[i-k4+1]^=x[i];
            else
            {
                x[i-k4+1]^=(x[i]>>rs4);
                x[i-k4]^=(x[i]<<ls4);
            }
        }
        x[i]=0;
    }

    top=x[k1]>>rs1;
    if (top!=0)
    {  
        x[1]^=top;
        top<<=rs1;

        if (rs2==0) x[k1-k2+1]^=top;
        else
        {
            x[k1-k2+1]^=(top>>rs2);
            if (k1>k2) x[k1-k2]^=(top<<ls2);
        }
        if (B)
        {
            if (rs3==0) x[k1-k3+1]^=top;
            else
            {
                x[k1-k3+1]^=(top>>rs3);
                if (k1>k3) x[k1-k3]^=(top<<ls3);
            }
            if (rs4==0) x[k1-k4+1]^=top;
            else
            {
                x[k1-k4+1]^=(top>>rs4);
                if (k1>k4) x[k1-k4]^=(top<<ls4);
            }
        }
       x[k1]^=top;
    }

    mr_lzero(x);
}

void incr2(big x,int n,big w)
{ /* increment x by small amount */
    copy(x,w);
    if (n==0) return;
    if (w[0]==0)
    {
        w[0]=1;
        w[1]=n;
    }
    else
    {
        w[1]^=(mr_small)n;
        mr_lzero(w);
    }
}

void modsquare2(_MIPD_ big x,big w)
{ /* w=x*x mod f */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    square2(x,mr_mip->w0);
    reduce2(_MIPP_ mr_mip->w0,mr_mip->w0);
    copy(mr_mip->w0,w);
}

void modmult2(_MIPD_ big x,big y,big w)
{ /* w=x*y mod f */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (x==y)
    {
        modsquare2(_MIPP_ x,w);
        return;
    }
    
    multiply2(_MIPP_ x,y,mr_mip->w0);
    reduce2(_MIPP_ mr_mip->w0,mr_mip->w0);
    copy(mr_mip->w0,w);
}

void sqroot2(_MIPD_ big x,big y)
{ /* there are quicker ways, but its not time critical here... */
    int i;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    copy(x,y);
    for (i=1;i<mr_mip->M;i++)
        modsquare2(_MIPP_ y,y);

}

void power2(_MIPD_ big x,int m,big w)
{ /* w=x^m mod f. Could be optimised a lot, but not time critical for me */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    copy(x,mr_mip->w1);
    
    convert(_MIPP_ 1,w);
    forever
    {
        if (m%2!=0)
            modmult2(_MIPP_ w,mr_mip->w1,w);
        m/=2;
        if (m==0) break;
        modsquare2(_MIPP_ mr_mip->w1,mr_mip->w1);
    }
}

/* Schroeppel, Orman, O'Malley, Spatscheck    *
 * "Almost Inverse" algorithm, Crypto '95     *
 * More optimization here and in-lining would *
 * speed up AFFINE mode. I observe that       *
 * pentanomials would be more efficient if C  *
 * were greater                               */

BOOL inverse2(_MIPD_ big x,big w)
{
    mr_small lsw;
    int n,bits,step,k=0;
    int k1,k2,k3,k4,ls1,ls2,ls3,ls4,rs1,rs2,rs3,rs4;
    int M,A,B,C;
    big t;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (size(x)==0) return FALSE;

    M=mr_mip->M;
    A=mr_mip->AA;
    B=mr_mip->BB;
    C=mr_mip->CC;
    convert(_MIPP_ 1,mr_mip->w1);            /* B */
    zero(mr_mip->w2);                 /* C */
    copy(x,mr_mip->w3);               /* F */
    copy(mr_mip->modulus,mr_mip->w4); /* G */
    forever
    {
        bits=zerobits(mr_mip->w3);
        shiftrightbits(mr_mip->w3,bits);
        shiftleftbits(mr_mip->w2,bits);
        k+=bits;    
        if (size(mr_mip->w3)==1) break;

        if (numbits(mr_mip->w3)<numbits(mr_mip->w4))
        { /* swap F & G, B & C */
            t=mr_mip->w3; mr_mip->w3=mr_mip->w4; mr_mip->w4=t;
            t=mr_mip->w1; mr_mip->w1=mr_mip->w2; mr_mip->w2=t;
        }
        add2(mr_mip->w3,mr_mip->w4,mr_mip->w3);
        add2(mr_mip->w1,mr_mip->w2,mr_mip->w1);
    }

    copy(mr_mip->w1,w);

    if (k==0) return TRUE;
    step=MIRACL;

    if (A<MIRACL) step=A;
    
    k1=1+M/MIRACL;       /* words from MSB to LSB */
    rs1=M%MIRACL;
    ls1=MIRACL-rs1;

    k2=1+A/MIRACL;   /* words from MSB to bit */
    rs2=A%MIRACL;
    ls2=MIRACL-rs2;

    if (B)
    { /* Pentanomial */
        if (C<MIRACL) step=C;

        k3=1+B/MIRACL;
        rs3=B%MIRACL;
        ls3=MIRACL-rs3;

        k4=1+C/MIRACL;
        rs4=C%MIRACL;
        ls4=MIRACL-rs4;
    }

    while (k>0)
    {
        if (k>step) n=step;
        else        n=k;
 
        if (n==MIRACL) lsw=w[1];
        else           lsw=w[1]&((1<<n)-1);

        w[0]=k1;
        if (rs1==0) w[k1]^=lsw;
        else
        {
            w[0]++;
            w[k1+1]^=(lsw>>ls1);
            w[k1]^=(lsw<<rs1);
        }
        if (rs2==0) w[k2]^=lsw;
        else
        {
            w[k2+1]^=(lsw>>ls2);
            w[k2]^=(lsw<<rs2);
        }
        if (B)
        {
            if (rs3==0) w[k3]^=lsw;
            else
            {
                w[k3+1]^=(lsw>>ls3);
                w[k3]^=(lsw<<rs3);
            }
            if (rs4==0) w[k4]^=lsw;
            else
            {
                w[k4+1]^=(lsw>>ls4);
                w[k4]^=(lsw<<rs4);
            }
        }
        shiftrightbits(w,n);
        k-=n;
    }
    mr_lzero(w);
    return TRUE;
}

BOOL multi_inverse2(_MIPD_ int m,big *x,big *w)
{ /* find w[i]=1/x[i] mod f, for i=0 to m-1 */
    int i;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (m==0) return TRUE;
    if (m<0) return FALSE;

    if (x==w)
    {
        mr_berror(_MIPP_ MR_ERR_BAD_PARAMETERS);
        return FALSE;
    }
    if (m==1)
    {
        inverse2(_MIPP_ x[0],w[0]);
        return TRUE;
    }
    convert(_MIPP_ 1,w[0]);
    copy(x[0],w[1]);
    for (i=2;i<m;i++)
        modmult2(_MIPP_ w[i-1],x[i-1],w[i]);

    modmult2(_MIPP_ w[m-1],x[m-1],mr_mip->w6);
    if (size(mr_mip->w6)==0)
    {
        mr_berror(_MIPP_ MR_ERR_DIV_BY_ZERO);
        return FALSE;
    }

    inverse2(_MIPP_ mr_mip->w6,mr_mip->w6);  /* y=1/y */

    copy(x[m-1],mr_mip->w5);
    modmult2(_MIPP_ w[m-1],mr_mip->w6,w[m-1]);

    for (i=m-2;;i--)
    {
        if (i==0)
        {
            modmult2(_MIPP_ mr_mip->w5,mr_mip->w6,w[0]);
            break;
        }
        modmult2(_MIPP_ w[i],mr_mip->w5,w[i]);
        modmult2(_MIPP_ w[i],mr_mip->w6,w[i]);
        modmult2(_MIPP_ mr_mip->w5,x[i],mr_mip->w5);
    }
    return TRUE;
}

int trace2(_MIPD_ big x)
{
    int i;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    copy(x,mr_mip->w1);
    for (i=1;i<mr_mip->M;i++)
    {
        modsquare2(_MIPP_ mr_mip->w1,mr_mip->w1);
        add2(mr_mip->w1,x,mr_mip->w1);
    }    
    return (mr_mip->w1[1]&1);
}

void rand2(_MIPD_ big x)
{ /* random number */
    int i,k;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    zero(x);
    k=1+mr_mip->M/MIRACL;        
    x[0]=k;
    for (i=1;i<=k;i++) x[i]=brand(_MIPPO_ );
    reduce2(_MIPP_ x,x);    
}

int parity2(big x)
{ /* return LSB */
   if (x[0]==0) return 0;
   return (int)(x[1]%2);
}

BOOL quad2(_MIPD_ big b,big w)
{ /* Solves x^2 + x = b  for a root w  *
   * returns TRUE if a solution exists *
   * the "other" solution is w+1       */
    int i,M;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

    M=mr_mip->M;
    copy(b,mr_mip->w1);
    if (M%2==1)
    { /* M is odd, so its the Half-Trace */
        copy(b,w);
        for (i=1;i<=(M-1)/2;i++)
        { 
            modsquare2(_MIPP_ w,w);
            modsquare2(_MIPP_ w,w);
            add2(w,mr_mip->w1,w);   
        } 
    }
    else
    {
        forever
        {
            rand2(_MIPP_ mr_mip->w2);
            zero(w);
            copy(mr_mip->w2,mr_mip->w3);
            for (i=1;i<M;i++)
            {
                modsquare2(_MIPP_ mr_mip->w3,mr_mip->w3);
                modmult2(_MIPP_ mr_mip->w3,mr_mip->w1,mr_mip->w4);
                modsquare2(_MIPP_ w,w);
                add2(w,mr_mip->w4,w);
                add2(mr_mip->w3,mr_mip->w2,mr_mip->w3);
            }    
            if (size(mr_mip->w3)!=0) break; 
        }
    }
    copy(w,mr_mip->w2);
    modsquare2(_MIPP_ mr_mip->w2,mr_mip->w2);
    add2(mr_mip->w2,w,mr_mip->w2);
    if (compare(mr_mip->w1,mr_mip->w2)==0) return TRUE;
    return FALSE;
}

void gf2m_dotprod(_MIPD_ int n,big *x,big *y,big w)
{ /* dot product - only one reduction! */
    int i;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    mr_mip->check=OFF;
    zero(mr_mip->w5);

    for (i=0;i<n;i++)
    {
        multiply2(_MIPP_ x[i],y[i],mr_mip->w0);
        add2(mr_mip->w5,mr_mip->w0,mr_mip->w5);
    }

    reduce2(_MIPP_ mr_mip->w5,mr_mip->w5);
    copy(mr_mip->w5,w);

    mr_mip->check=ON;
}

BOOL prepare_basis(_MIPD_ int m,int a,int b,int c,BOOL check)
{
    int i,k,sh;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return FALSE;

    if (b==0) c=0;
    if (m==mr_mip->M && a==mr_mip->AA && b==mr_mip->BB && c==mr_mip->CC)
        return TRUE;   /* its already prepared... */

    MR_IN(138)
    if (m <=0 || a<=0 || a>=m || b>=a) 
    {
        mr_berror(_MIPP_ MR_ERR_BAD_MODULUS);
        MR_OUT
        return FALSE;
    }
    
    mr_mip->M=m;
    mr_mip->AA=a;
    mr_mip->BB=0;
    mr_mip->CC=0;
    if (mr_mip->modulus==NULL) mr_mip->modulus=mirvar(_MIPP_ 0);
    else zero(mr_mip->modulus);

    k=1+m/MIRACL;
    mr_mip->modulus[0]=k;
    sh=m%MIRACL;
    mr_mip->modulus[k]=(1<<sh);
    mr_mip->modulus[1]^=1;
    mr_mip->modulus[1+a/MIRACL]^=(1<<(a%MIRACL));
    if (b!=0)
    {
         mr_mip->BB=b;
         mr_mip->CC=c;
         mr_mip->modulus[1+b/MIRACL]^=(1<<(b%MIRACL));
         mr_mip->modulus[1+c/MIRACL]^=(1<<(c%MIRACL));
    }

    if (!check)
    {
        MR_OUT
        return TRUE;
    }

/* check for irreducibility of basis */

    zero(mr_mip->w4);
    mr_mip->w4[0]=1;
    mr_mip->w4[1]=2;       /* f(t) = t */
    for (i=0;i<=m/2;i++)
    {
        modsquare2(_MIPP_ mr_mip->w4,mr_mip->w4);
        incr2(mr_mip->w4,2,mr_mip->w5);
        gcd2(_MIPP_ mr_mip->w5,mr_mip->modulus,mr_mip->w5);
        if (size(mr_mip->w5)!=1)
        {
            mr_berror(_MIPP_ MR_ERR_NOT_IRREDUC);
            MR_OUT
            return FALSE;
        }
    }
                   
    MR_OUT
    return TRUE;
}

/* Initialise with Trinomial or Pentanomial   *
 * t^m  + t^a + 1 OR t^m + t^a +t^b + t^c + 1 *
 * Set b=0 for pentanomial. a2 is 0 or 1.     */

BOOL ecurve2_init(_MIPD_ int m,int a,int b,int c,big a2,big a6,BOOL check,int type)
{
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    int i;

/* catch some nonsense conditions */

    if (mr_mip->ERNUM) return FALSE;

    if (size(a2)<0) return FALSE;
    if (size(a6)<0) return FALSE;

    MR_IN(123)

    if (!prepare_basis(_MIPP_ m,a,b,c,check))
    { /* unable to set the basis */
        MR_OUT
        return FALSE;
    }    

    mr_mip->Asize=size(a2);    
    mr_mip->Bsize=size(a6);

    if (mr_mip->Asize==MR_TOOBIG)
    { 
        if (mr_mip->A==NULL) mr_mip->A=mirvar(_MIPP_ 0);
        copy(a2,mr_mip->A);
    }

    if (mr_mip->Bsize==MR_TOOBIG)
    { 
        if (mr_mip->B==NULL) mr_mip->B=mirvar(_MIPP_ 0);
        copy(a6,mr_mip->B);
    }

 /* Use C to store B^(2^M-2) - required for projective doubling */

    if (mr_mip->C==NULL) mr_mip->C=mirvar(_MIPP_ 0);
    copy(a6,mr_mip->C);
    for (i=1;i<m-1;i++) modsquare2(_MIPP_ mr_mip->C,mr_mip->C);

    mr_mip->coord=type;
    MR_OUT
    return TRUE;
}    

epoint* epoint2_init(_MIPDO_ )
{
    epoint *p;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return NULL;
    
    MR_IN(124)
 
    p=mr_alloc(_MIPP_ 1,sizeof(epoint));
    p->X=mirvar(_MIPP_ 0);
    p->Y=mirvar(_MIPP_ 0);
    p->Z=NULL;
    p->marker=MR_EPOINT_INFINITY;
    
    MR_OUT

    return p;
}

void epoint2_free(_MIPD_ epoint *p)
{ /* clean up point */
    mirkill(_MIPP_ p->X);
    mirkill(_MIPP_ p->Y);
    if (p->Z!=NULL) mirkill(_MIPP_ p->Z);
    mr_free(_MIPP_ p);
}

BOOL epoint2_set(_MIPD_ big x,big y,int cb,epoint *p)
{ /* initialise a point on active ecurve            *
   * if x or y == NULL, set to point at infinity    *
   * if x==y, a y co-ordinate is calculated - if    *
   * possible - and cb suggests LSB 0/1  of y/x     *
   * (which "decompresses" y). Otherwise, check     *
   * validity of given (x,y) point, ignoring cb.    *
   * Returns TRUE for valid point, otherwise FALSE. */
  
    BOOL valid;
   
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return FALSE;

    MR_IN(125)

    if (x==NULL || y==NULL)
    {
        convert(_MIPP_ 1,p->X);
        convert(_MIPP_ 1,p->Y);
        p->marker=MR_EPOINT_INFINITY;
        MR_OUT
        return TRUE;
    }
/* calculate x^3+Ax^2+B */
    copy(x,p->X);
    modsquare2(_MIPP_ p->X,mr_mip->w6);           /* w6=x^2 */
    modmult2(_MIPP_ mr_mip->w6,p->X,mr_mip->w5);  /* w5=x^3 */

    if (mr_mip->Asize==MR_TOOBIG)
        copy(mr_mip->A,mr_mip->w1);
    else
        convert(_MIPP_ mr_mip->Asize,mr_mip->w1);
    modmult2(_MIPP_ mr_mip->w6,mr_mip->w1,mr_mip->w0);
    add2(mr_mip->w5,mr_mip->w0,mr_mip->w5);

    if (mr_mip->Bsize==MR_TOOBIG)
        add2(mr_mip->w5,mr_mip->B,mr_mip->w5);    /* w5=x^3+Ax^2+B */
    else
        incr2(mr_mip->w5,mr_mip->Bsize,mr_mip->w5);
    valid=FALSE;       
    if (x!=y)
    { /* compare with y^2+xy */
        copy(y,p->Y);
        modsquare2(_MIPP_ p->Y,mr_mip->w2);
        modmult2(_MIPP_ p->Y,p->X,mr_mip->w1);
        add2(mr_mip->w1,mr_mip->w2,mr_mip->w1);
        if (compare(mr_mip->w1,mr_mip->w5)==0) valid=TRUE;
    }
    else
    { /* no y supplied - calculate one. Solve quadratic */
        if (size(p->X)==0) 
        {
            if (mr_mip->Bsize==MR_TOOBIG) 
                copy(mr_mip->B,mr_mip->w1);
            else convert(_MIPP_ mr_mip->Bsize,mr_mip->w1); 

            sqroot2(_MIPP_ mr_mip->w1,p->Y);
            valid=TRUE;
        }
        else
        {
            inverse2(_MIPP_ mr_mip->w6,mr_mip->w6);  /* 1/x^2 */
            modmult2(_MIPP_ mr_mip->w5,mr_mip->w6,mr_mip->w5);
            valid=quad2(_MIPP_ mr_mip->w5,mr_mip->w5);     
            incr2(mr_mip->w5,cb^parity2(mr_mip->w5),mr_mip->w5);
            modmult2(_MIPP_ mr_mip->w5,p->X,p->Y);
        }
    }
    if (valid)
    {
        if (p->Z!=NULL)
            convert(_MIPP_ 1,p->Z);
        p->marker=MR_EPOINT_NORMALIZED;
        MR_OUT
        return TRUE;
    }
    MR_OUT
    return FALSE;
}

BOOL epoint2_norm(_MIPD_ epoint *p)
{ /* normalise a point */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

    if (mr_mip->coord==MR_AFFINE) return TRUE;
    if (p->marker!=MR_EPOINT_GENERAL) return TRUE;

    if (mr_mip->ERNUM) return FALSE;

    MR_IN(126)

    if (!inverse2(_MIPP_ p->Z,mr_mip->w8))
    {
        MR_OUT
        return FALSE;
    }

    modsquare2(_MIPP_ mr_mip->w8,mr_mip->w1);          /* 1/ZZ */
    modmult2(_MIPP_ p->X,mr_mip->w1,p->X);             /* X/ZZ */
    modmult2(_MIPP_ mr_mip->w1,mr_mip->w8,mr_mip->w1); /* 1/ZZZ */ 
    modmult2(_MIPP_ p->Y,mr_mip->w1,p->Y);             /* Y/ZZZ */
    convert(_MIPP_ 1,p->Z);

    p->marker=MR_EPOINT_NORMALIZED;
    MR_OUT
    return TRUE;
}

int epoint2_get(_MIPD_ epoint* p,big x,big y)
{ /* Get point co-ordinates in affine, normal form       *
   * (converted from projective form). If x==y, supplies *
   * x only. Return value is LSB of y/x (useful for      *
   * point compression                                   */
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

    MR_IN(127)

    epoint2_norm(_MIPP_ p);

    copy(p->X,x);
    copy(p->Y,mr_mip->w5);

    if (x!=y) copy(mr_mip->w5,y);
    if (size(x)==0)
    {
        MR_OUT
        return 0;
    }
    inverse2(_MIPP_ x,mr_mip->w5);
    modmult2(_MIPP_ mr_mip->w5,p->Y,mr_mip->w5);

    lsb=parity2(mr_mip->w5);

    MR_OUT
    return lsb;
}

static void ecurve2_double(_MIPD_ epoint *p)
{ /* double epoint on active curve */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

    if (p->marker==MR_EPOINT_INFINITY)
    { /* 2 times infinity == infinity! */
        return;
    }

    if (mr_mip->coord==MR_AFFINE)
    {
        if (size(p->X)==0)
        { /* set to point at infinity */
            epoint2_set(_MIPP_ NULL,NULL,0,p);
            return;
        }
        inverse2(_MIPP_ p->X,mr_mip->w8);
        modmult2(_MIPP_ mr_mip->w8,p->Y,mr_mip->w8);
        add2(mr_mip->w8,p->X,mr_mip->w8);   /* w8 is slope m */

        modsquare2(_MIPP_ mr_mip->w8,mr_mip->w6);  /* w6 =m^2 */
        add2(mr_mip->w6,mr_mip->w8,mr_mip->w1);
        if (mr_mip->Asize==MR_TOOBIG)
            add2(mr_mip->w1,mr_mip->A,mr_mip->w1); 
        else
            incr2(mr_mip->w1,mr_mip->Asize,mr_mip->w1); /* w1 = x3 */

        add2(p->X,mr_mip->w1,mr_mip->w6);
        modmult2(_MIPP_ mr_mip->w6,mr_mip->w8,mr_mip->w6);
        copy(mr_mip->w1,p->X);
        add2(mr_mip->w6,mr_mip->w1,mr_mip->w6);
        add2(p->Y,mr_mip->w6,p->Y);
        return;
    }

    if (p->Z==NULL)
        p->Z=mirvar(_MIPP_ 1);

    if (size(p->X)==0)
    { /* set to infinity */
        epoint2_set(_MIPP_ NULL,NULL,0,p);
        return;
    }

    modmult2(_MIPP_ p->Y,p->Z,p->Y);             /* t2 = t2 * t3 */
    modsquare2(_MIPP_ p->Z,p->Z);                /* t3 = t3^2 */
    modmult2(_MIPP_ mr_mip->C,p->Z,mr_mip->w4);  /* t4 = c * t3 */ 
    modmult2(_MIPP_ p->Z,p->X,p->Z);             /* t3 = t3 * t1 */

    add2(p->Y,p->Z,p->Y);                 /* t2 = t2 + t3 */
    add2(mr_mip->w4,p->X,mr_mip->w4);     /* t4 = t4 + t1 */
    modsquare2(_MIPP_ mr_mip->w4,mr_mip->w4);    /* t4 = t4^2 */ 
    modsquare2(_MIPP_ mr_mip->w4,mr_mip->w4);    /* t4 = t4^2 */
    modsquare2(_MIPP_ p->X,mr_mip->w1);          /* t1 = t1^2 */
    add2(p->Y,mr_mip->w1,p->Y);           /* t2 = t2 + t1 */
    modmult2(_MIPP_ p->Y,mr_mip->w4,p->Y);       /* t2 = t2 * t4 */
    modsquare2(_MIPP_ mr_mip->w1,mr_mip->w1);    /* t1 = t1^2 */
    modmult2(_MIPP_ mr_mip->w1,p->Z,mr_mip->w1); /* t1 = t1 * t3 */
    add2(p->Y,mr_mip->w1,p->Y);           /* t2 = t2 + t1 */
    copy(mr_mip->w4,p->X);

    p->marker=MR_EPOINT_GENERAL;
}

static BOOL ecurve2_padd(_MIPD_ epoint *p,epoint *pa)
{ /* primitive add two epoints on the active ecurve pa+=p      *
   * note that if p is normalized, its Z coordinate isn't used */
 
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->coord==MR_AFFINE)
    {
        add2(p->Y,pa->Y,mr_mip->w8);
        add2(p->X,pa->X,mr_mip->w6);
        if (size(mr_mip->w6)==0)
        {  /* divide by zero */
            if (size(mr_mip->w8)==0)
            { /* should have doubled! */
                return FALSE;
            }
            else
            { /* point at infinity */
                epoint2_set(_MIPP_ NULL,NULL,0,pa);
                return TRUE;
            }
        }
        inverse2(_MIPP_ mr_mip->w6,mr_mip->w5);

        modmult2(_MIPP_ mr_mip->w8,mr_mip->w5,mr_mip->w8); /* w8=m */
        modsquare2(_MIPP_ mr_mip->w8,mr_mip->w5);
        add2(mr_mip->w5,mr_mip->w8,mr_mip->w5);
        add2(mr_mip->w5,mr_mip->w6,mr_mip->w5);
        if (mr_mip->Asize==MR_TOOBIG)
            add2(mr_mip->w5,mr_mip->A,mr_mip->w5);
        else
            incr2(mr_mip->w5,mr_mip->Asize,mr_mip->w5); /* w5=x3 */
        
        add2(pa->X,mr_mip->w5,mr_mip->w6);
        modmult2(_MIPP_ mr_mip->w6,mr_mip->w8,mr_mip->w6);
        copy(mr_mip->w5,pa->X);
        add2(mr_mip->w6,mr_mip->w5,mr_mip->w6);
        add2(pa->Y,mr_mip->w6,pa->Y);

        pa->marker=MR_EPOINT_NORMALIZED;
        return TRUE;
    }

    if (pa->Z==NULL)
        pa->Z=mirvar(_MIPP_ 1);


    if (p->marker!=MR_EPOINT_NORMALIZED)
    {
        modsquare2(_MIPP_ p->Z,mr_mip->w6);           /* t7 = t6^2    */
        modmult2(_MIPP_ pa->X,mr_mip->w6,mr_mip->w1); /* t1 = t1 * t7 */
        modmult2(_MIPP_ mr_mip->w6,p->Z,mr_mip->w6);  /* t7 = t7 * t6 */
        modmult2(_MIPP_ pa->Y,mr_mip->w6,mr_mip->w2); /* t2 = t2 * t7 */ 
    }
    else
    {
        copy(pa->X,mr_mip->w1);
        copy(pa->Y,mr_mip->w2);
    }
    modsquare2(_MIPP_ pa->Z,mr_mip->w6);               /* t7 = t3^2    */
    modmult2(_MIPP_ mr_mip->w6,p->X,mr_mip->w8);       /* t8 = t4 * t7 */
    add2(mr_mip->w1,mr_mip->w8,mr_mip->w1);     /* t1 = t1 + t8 */
    modmult2(_MIPP_ mr_mip->w6,pa->Z,mr_mip->w6);      /* t7 = t7 * t3 */
    modmult2(_MIPP_ mr_mip->w6,p->Y,mr_mip->w8);       /* t8 = t7 * t5 */
    add2(mr_mip->w2,mr_mip->w8,mr_mip->w2);     /* t2 = t2 + t8 */
    if (size(mr_mip->w1)==0)
    {
        if (size(mr_mip->w2)==0)
        { /* should have doubled! */
            return FALSE;
        }
        else
        { /* point at infinity */
            epoint2_set(_MIPP_ NULL,NULL,0,pa);
            return TRUE;
        }
    }
    modmult2(_MIPP_ p->X,mr_mip->w2,mr_mip->w4);      /* t4 = t2 * t4 */
    modmult2(_MIPP_ pa->Z,mr_mip->w1,mr_mip->w3);     /* t3 = t3 * t1 */
    modmult2(_MIPP_ p->Y,mr_mip->w3,mr_mip->w5);      /* t5 = t5 * t3 */
    add2(mr_mip->w4,mr_mip->w5,mr_mip->w4);    /* t4 = t4 + t5 */
    modsquare2(_MIPP_ mr_mip->w3,mr_mip->w5);         /* t5 = t3^2    */
    modmult2(_MIPP_ mr_mip->w4,mr_mip->w5,mr_mip->w6); /* t7 = t4 * t5 */

    if (p->marker!=MR_EPOINT_NORMALIZED) 
        modmult2(_MIPP_ mr_mip->w3,p->Z,mr_mip->w3);  /* t3 = t3 * t6 */
    add2(mr_mip->w2,mr_mip->w3,mr_mip->w4);    /* t4 = t2 + t3 */
    modmult2(_MIPP_ mr_mip->w2,mr_mip->w4,mr_mip->w2);/* t2 = t2 * t4 */
    modsquare2(_MIPP_ mr_mip->w1,mr_mip->w5);         /* t5 = t1^2    */
    modmult2(_MIPP_ mr_mip->w1,mr_mip->w5,mr_mip->w1);/* t1 = t1 * t5 */
    if (mr_mip->Asize>0)
    {
        modsquare2(_MIPP_ mr_mip->w3,mr_mip->w8);     /* t8 = t3^2    */
        if (mr_mip->Asize>1)
        {
            if (mr_mip->Asize==MR_TOOBIG)
                copy(mr_mip->A,mr_mip->w5);
            else 
                convert(_MIPP_ mr_mip->Asize,mr_mip->w5);
            modmult2(_MIPP_ mr_mip->w8,mr_mip->w5,mr_mip->w8);
        }
        add2(mr_mip->w1,mr_mip->w8,mr_mip->w1);/* t1 = t1 + t8 */
    }
    add2(mr_mip->w1,mr_mip->w2,pa->X);         /* t1 = t1 + t2 */
    modmult2(_MIPP_ mr_mip->w4,pa->X,mr_mip->w4);/* t4 = t4 * t1 */
    add2(mr_mip->w4,mr_mip->w6,pa->Y);         /* t2 = t4 + t7 */
    copy(mr_mip->w3,pa->Z);

    pa->marker=MR_EPOINT_GENERAL;
    return TRUE;
}

void epoint2_copy(_MIPD_ epoint *a,epoint *b)
{   
    if (a==b) return;
    copy(a->X,b->X);
    copy(a->Y,b->Y);
    if (a->Z==NULL)
    {
         if (b->Z!=NULL)
            convert(_MIPP_ 1,b->Z);
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

BOOL epoint2_comp(_MIPD_ epoint *a,epoint *b)
{
    int ia,ib;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return FALSE;
    if (a==b) return TRUE;

    MR_IN(128)

    ia=epoint2_get(_MIPP_ a,mr_mip->w9,mr_mip->w9);
    ib=epoint2_get(_MIPP_ b,mr_mip->w10,mr_mip->w10);

    MR_OUT
    if (ia==ib && compare(mr_mip->w9,mr_mip->w10)==0) return TRUE;
    return FALSE;
}

void ecurve2_add(_MIPD_ epoint *p,epoint *pa)
{  /* pa=pa+p; */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(129)

    if (p==pa) 
    {
        ecurve2_double(_MIPP_ pa);
        MR_OUT
        return;
    }
    if (pa->marker==MR_EPOINT_INFINITY)
    {
        epoint2_copy(_MIPP_ p,pa);
        MR_OUT 
        return;
    }
    if (p->marker==MR_EPOINT_INFINITY) 
    {
        MR_OUT
        return;
    }
    if (!ecurve2_padd(_MIPP_ p,pa)) ecurve2_double(_MIPP_ pa);
    MR_OUT
}

void epoint2_negate(_MIPD_ epoint *p)
{ /* negate a point */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    if (p->marker==MR_EPOINT_INFINITY) return;
    MR_IN(130)
    if (p->marker==MR_EPOINT_GENERAL)
    {
        modmult2(_MIPP_ p->X,p->Z,mr_mip->w1);
        add2(p->Y,mr_mip->w1,p->Y);
    }
    else add2(p->Y,p->X,p->Y);
    MR_OUT
}

void ecurve2_sub(_MIPD_ epoint *p,epoint *pa)
{
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(131)

    if (p==pa)
    {
        epoint2_set(_MIPP_ NULL,NULL,0,pa);
        MR_OUT
        return;
    } 
    if (p->marker==MR_EPOINT_INFINITY) 
    {
        MR_OUT
        return;
    }

    epoint2_negate(_MIPP_ p);
    ecurve2_add(_MIPP_ p,pa);
    epoint2_negate(_MIPP_ p);

    MR_OUT
}

void ecurve2_multi_add(_MIPD_ int m,epoint **x,epoint **w)
{ /* adds m points together simultaneously, w[i]+=x[i] */
    int i,*flag;
    big *A,*B,*C;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(132)
    if (mr_mip->coord==MR_AFFINE)
    {
        A=(big *)mr_alloc(_MIPP_ m,sizeof(big));
        B=(big *)mr_alloc(_MIPP_ m,sizeof(big));
        C=(big *)mr_alloc(_MIPP_ m,sizeof(big));
        flag=(int *)mr_alloc(_MIPP_ m,sizeof(int));

        convert(_MIPP_ 1,mr_mip->w3);  /* unity */
 
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
                    flag[i]=1;     /* result is infinity */
                    copy(mr_mip->w3,B[i]);
                    continue;
                }
                modsquare2(_MIPP_ x[i]->X,A[i]);
                add2(A[i],x[i]->Y,A[i]);
                copy(x[i]->X,B[i]);
            }
            else
            {
                if (x[i]->marker==MR_EPOINT_INFINITY)
                {
                    flag[i]=2;                    /* w[i] unchanged */
                    copy(mr_mip->w3,B[i]);
                    continue;
                }
                if (w[i]->marker==MR_EPOINT_INFINITY)
                {
                    flag[i]=3;                    /* w[i]=x[i] */
                    copy(mr_mip->w3,B[i]);
                    continue;
                }
                add2(x[i]->X,w[i]->X,B[i]);
                if (size(B[i])==0)
                { /* point at infinity */
                    flag[i]=1;                /* result is infinity */
                    copy(mr_mip->w3,B[i]);
                    continue;
                }
                add2(x[i]->Y,w[i]->Y,A[i]);
            }
        }

        multi_inverse2(_MIPP_ m,B,C); /* one inversion only */
        for (i=0;i<m;i++)
        {
            if (flag[i]==1)
            { /* point at infinity */
                epoint2_set(_MIPP_ NULL,NULL,0,w[i]);
                continue;
            }
            if (flag[i]==2)
            {
                continue;
            }
            if (flag[i]==3)
            {
                epoint2_copy(_MIPP_ x[i],w[i]);
                continue;
            }
            modmult2(_MIPP_ A[i],C[i],mr_mip->w8);
            modsquare2(_MIPP_ mr_mip->w8,mr_mip->w6); /* m^2 */
            add2(mr_mip->w6,mr_mip->w8,mr_mip->w6);
            add2(mr_mip->w6,x[i]->X,mr_mip->w6);
            add2(mr_mip->w6,w[i]->X,mr_mip->w6);
            if (mr_mip->Asize==MR_TOOBIG)
                add2(mr_mip->w6,mr_mip->A,mr_mip->w6);
            else
                incr2(mr_mip->w6,mr_mip->Asize,mr_mip->w6);

            add2(w[i]->X,mr_mip->w6,mr_mip->w2);
            modmult2(_MIPP_ mr_mip->w2,mr_mip->w8,mr_mip->w2);
            add2(mr_mip->w2,mr_mip->w6,mr_mip->w2);
            add2(mr_mip->w2,w[i]->Y,w[i]->Y);
            copy(mr_mip->w6,w[i]->X);

            w[i]->marker=MR_EPOINT_GENERAL;

            mr_free(_MIPP_ C[i]);
            mr_free(_MIPP_ B[i]);
            mr_free(_MIPP_ A[i]);
        }
        mr_free(_MIPP_ flag);
        mr_free(_MIPP_ C); mr_free(_MIPP_ B); mr_free(_MIPP_ A);
    }
    else
    { /* no speed-up for projective coordinates */
        for (i=0;i<m;i++) ecurve2_add(_MIPP_ x[i],w[i]);
    }
    MR_OUT
}

void ecurve2_mult(_MIPD_ big e,epoint *pa,epoint *pt)
{ /* pt=e*pa; */
    int i,j,n,ch,ce,nb,nbs,nzs;
    epoint *p;
    epoint *table[11];
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(133)

    if (size(e)==0) 
    { /* multiplied by 0 */
        epoint2_set(_MIPP_ NULL,NULL,0,pt);
        MR_OUT
        return;
    }
    copy(e,mr_mip->w9);
    epoint2_norm(_MIPP_ pa);
    epoint2_copy(_MIPP_ pa,pt);

    if (size(mr_mip->w9)<0)
    { /* pt = -pt */
        negate(mr_mip->w9,mr_mip->w9);
        epoint2_negate(_MIPP_ pt);
    }

    if (size(mr_mip->w9)==1)
    { 
        MR_OUT
        return;
    }

    premult(_MIPP_ mr_mip->w9,3,mr_mip->w10);      /* h=3*e */
    p=epoint2_init(_MIPPO_ );
    epoint2_copy(_MIPP_ pt,p);

    if (mr_mip->base==mr_mip->base2)
    {
        table[0]=epoint2_init(_MIPPO_ );
        epoint2_copy(_MIPP_ p,table[0]);
        ecurve2_double(_MIPP_ p);

        for (i=1;i<=10;i++)
        { /* precomputation */
            table[i]=epoint2_init(_MIPPO_ );
            epoint2_copy(_MIPP_ table[i-1],table[i]);
            ecurve2_add(_MIPP_ p,table[i]);
        }

  /* note that normalising this table doesn't really help */
        nb=logb2(_MIPP_ mr_mip->w10);

        for (i=nb-2;i>=1;)
        { /* add/subtract */
            if (mr_mip->user!=NULL) (*mr_mip->user)();
            n=mr_naf_window(_MIPP_ mr_mip->w9,mr_mip->w10,i,&nbs,&nzs);
            for (j=0;j<nbs;j++)
                ecurve2_double(_MIPP_ pt);
            if (n>0) 
                ecurve2_add(_MIPP_ table[n/2],pt);
            if (n<0) 
                 ecurve2_sub(_MIPP_ table[(-n)/2],pt);
            i-=nbs;
            if (nzs)
            {
                for (j=0;j<nzs;j++) ecurve2_double(_MIPP_ pt);
                i-=nzs;
            }
        }
        for (i=10;i>=0;i--) epoint2_free(_MIPP_ table[i]);
    }
    else
    { 
        expint(_MIPP_ 2,logb2(_MIPP_ mr_mip->w10)-1,mr_mip->w11);
        mr_psub(_MIPP_ mr_mip->w10,mr_mip->w11,mr_mip->w10);
        subdiv(_MIPP_ mr_mip->w11,2,mr_mip->w11);
        while (size(mr_mip->w11) > 1)
        { /* add/subtract method */
            if (mr_mip->user!=NULL) (*mr_mip->user)();

            ecurve2_double(_MIPP_ pt);
            ce=compare(mr_mip->w9,mr_mip->w11); /* e(i)=1? */
            ch=compare(mr_mip->w10,mr_mip->w11); /* h(i)=1? */
            if (ch>=0) 
            {  /* h(i)=1 */
                if (ce<0) ecurve2_add(_MIPP_ p,pt);
                mr_psub(_MIPP_ mr_mip->w10,mr_mip->w11,mr_mip->w10);
            }
            if (ce>=0) 
            {  /* e(i)=1 */
                if (ch<0) ecurve2_sub(_MIPP_ p,pt);
                mr_psub(_MIPP_ mr_mip->w9,mr_mip->w11,mr_mip->w9);  
            }
            subdiv(_MIPP_ mr_mip->w11,2,mr_mip->w11);
        }
    }
    epoint2_free(_MIPP_ p);
    MR_OUT
}

void ecurve2_multn(_MIPD_ int n,big *y,epoint **x,epoint *w)
{ /* pt=e[o]*p[0]+e[1]*p[1]+ .... e[n-1]*p[n-1]   */
    int i,j,k,m,nb,ea;
    epoint **G;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(134)

    m=1<<n;
    G=(epoint **)mr_alloc(_MIPP_ m,sizeof(epoint*));

    for (i=0,k=1;i<n;i++)
    {
        for (j=0; j < (1<<i) ;j++)
        {
            G[k]=epoint2_init(_MIPPO_ );
            epoint2_copy(_MIPP_ x[i],G[k]);
            if (j!=0) ecurve2_add(_MIPP_ G[j],G[k]);
            k++;
        }
    }

    nb=0;
    for (j=0;j<n;j++) if ((k=logb2(_MIPP_ y[j])) > nb) nb=k;

    epoint2_set(_MIPP_ NULL,NULL,0,w);            /* w=0 */
    
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
            ecurve2_double(_MIPP_ w);
            if (ea!=0) ecurve2_add(_MIPP_ G[ea],w);
        }    
    }
    else mr_berror(_MIPP_ MR_ERR_NOT_SUPPORTED);

    for (i=1;i<m;i++) epoint2_free(_MIPP_ G[i]);
    mr_free(_MIPP_ G);
    MR_OUT
}

void ecurve2_mult2(_MIPD_ big e,epoint *p,big ea,epoint *pa,epoint *pt)
{ /* pt=e*p+ea*pa; */
    int e1,h1,e2,h2;
    epoint *p1,*p2,*ps,*pd;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(135)

    if (size(e)==0) 
    {
        ecurve2_mult(_MIPP_ ea,pa,pt);
        MR_OUT
        return;
    }

    p2=epoint2_init(_MIPPO_ );
    epoint2_norm(_MIPP_ pa);
    epoint2_copy(_MIPP_ pa,p2);
    copy(ea,mr_mip->w9);
    if (size(mr_mip->w9)<0)
    { /* p2 = -p2 */
        negate(mr_mip->w9,mr_mip->w9);
        epoint2_negate(_MIPP_ p2);
    }
    premult(_MIPP_ mr_mip->w9,3,mr_mip->w10);      /* 3*ea */

    p1=epoint2_init(_MIPPO_ );
    epoint2_norm(_MIPP_ p);
    epoint2_copy(_MIPP_ p,p1);
    copy(e,mr_mip->w12);
    if (size(mr_mip->w12)<0)
    { /* p1= -p1 */
        negate(mr_mip->w12,mr_mip->w12);
        epoint2_negate(_MIPP_ p1);
    }
    premult(_MIPP_ mr_mip->w12,3,mr_mip->w13);    /* 3*e */

    epoint2_set(_MIPP_ NULL,NULL,0,pt);            /* pt=0 */

    if (compare(mr_mip->w10,mr_mip->w13)>=0)
         expint(_MIPP_ 2,logb2(_MIPP_ mr_mip->w10)-1,mr_mip->w11);
    else expint(_MIPP_ 2,logb2(_MIPP_ mr_mip->w13)-1,mr_mip->w11);

    ps=epoint2_init(_MIPPO_ );
    pd=epoint2_init(_MIPPO_ );

    epoint2_copy(_MIPP_ p1,ps);
    ecurve2_add(_MIPP_ p2,ps);                    /* ps=p1+p2 */
    epoint2_copy(_MIPP_ p1,pd);
    ecurve2_sub(_MIPP_ p2,pd);                    /* pd=p1-p2 */
    epoint2_norm(_MIPP_ ps);
    epoint2_norm(_MIPP_ pd);
    while (size(mr_mip->w11) > 1)
    { /* add/subtract method */
        if (mr_mip->user!=NULL) (*mr_mip->user)();

        ecurve2_double(_MIPP_ pt);

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
                if (h1==1) ecurve2_add(_MIPP_ p1,pt);
                else       ecurve2_sub(_MIPP_ p1,pt);
            }
            else
            {
                if (h1==1)
                {
                    if (h2==1) ecurve2_add(_MIPP_ ps,pt);
                    else       ecurve2_add(_MIPP_ pd,pt);
                }
                else
                {
                    if (h2==1) ecurve2_sub(_MIPP_ pd,pt);
                    else       ecurve2_sub(_MIPP_ ps,pt);
                }
            }
        }
        else if (e2!=h2)
        {
            if (h2==1) ecurve2_add(_MIPP_ p2,pt);
            else       ecurve2_sub(_MIPP_ p2,pt);
        }

        subdiv(_MIPP_ mr_mip->w11,2,mr_mip->w11);
    }
    epoint2_free(_MIPP_ p1);
    epoint2_free(_MIPP_ p2);
    epoint2_free(_MIPP_ ps);
    epoint2_free(_MIPP_ pd);
    MR_OUT
}

/*   Routines to implement Brickell et al's method for fast
 *   computation of x*G mod n, for fixed G and n, using precomputation. 
 *
 *   Elliptic curve over GF(2^m) version of mrebrick.c
 *
 *   This idea can be used to substantially speed up certain phases 
 *   of the Digital Signature Standard (ECS) for example.
 *
 *   See "Fast Exponentiation with Precomputation"
 *   by E. Brickell et al. in Proceedings Eurocrypt 1992
 */

BOOL ebrick2_init(_MIPD_ ebrick2 *B,big x,big y,big a2,big a6,int m,int a,int b,int c,int nb)
{ /* (x,y) is the fixed base                            *
   * a2 and a6 the parameters of the curve              *
   * m, a, b, c are the m in the 2^m modulus, and a,b,c *
   * are the parameters of the irreducible bases,       *
   * trinomial if b!=0, otherwise pentanomial           *
   * nb is the maximum number of bits in the multiplier */

    int i,base,best,store,time;
    epoint *w;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (nb<2 || mr_mip->ERNUM) return FALSE;

    MR_IN(136)

    best=0;
    for (i=1,base=2;;base*=2,i++)
    { /* try to find best base as power of 2 */
        store=nb/i+1;
        time=store+base-3;  /* no floating point! */
        if (best==0 || time<best) best=time;
        else break; 
    }
    B->base=base;
    B->store=store;
    B->table=mr_alloc(_MIPP_ store,sizeof(epoint *));
    if (B->table==NULL)
    {
        mr_berror(_MIPP_ MR_ERR_OUT_OF_MEMORY);   
        MR_OUT
        return FALSE;
    }
    B->a6=mirvar(_MIPP_ 0);
    copy(a6,B->a6);
    B->a2=mirvar(_MIPP_ 0);
    copy(a2,B->a2);
    B->m=m;
    B->a=a;
    B->b=b;
    B->c=c;   

    if (!ecurve2_init(_MIPP_ m,a,b,c,a2,a6,TRUE,MR_PROJECTIVE))
    {
        MR_OUT
        return FALSE;
    }
    w=epoint2_init(_MIPPO_ );
    B->table[0]=epoint2_init(_MIPPO_ );
    epoint2_set(_MIPP_ x,y,0,B->table[0]);

    for (i=1;i<store;i++) 
    { /* calculate look-up table */
        B->table[i]=epoint2_init(_MIPPO_ );
        convert(_MIPP_ base,mr_mip->w1);
        ecurve2_mult(_MIPP_ mr_mip->w1,B->table[i-1],w);
        epoint2_norm(_MIPP_ w);
        epoint2_copy(_MIPP_ w,B->table[i]);
    }
    epoint2_free(_MIPP_ w);
    MR_OUT
    return TRUE;
}

void ebrick2_end(_MIPD_ ebrick2 *B)
{
    int i;
    for (i=0;i<B->store;i++)
        epoint2_free(_MIPP_ B->table[i]);
    mirkill(_MIPP_ B->a2);
    mirkill(_MIPP_ B->a6);
    mr_free(_MIPP_ B->table);  
}

int mul2_brick(_MIPD_ ebrick2 *B,big e,big x,big y)
{
    int i,ndig,d;
    int *digits;
    epoint *w,*w1;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

    if (size(e)<0) mr_berror(_MIPP_ MR_ERR_NEG_POWER);

    MR_IN(137)

    digits=mr_alloc(_MIPP_ B->store,sizeof(int));
    if (digits==NULL)
    {
        mr_berror(_MIPP_ MR_ERR_OUT_OF_MEMORY);
        MR_OUT
        return 0;        
    }

    if (!ecurve2_init(_MIPP_ B->m,B->a,B->b,B->c,B->a2,B->a6,FALSE,MR_PROJECTIVE))
    {
        MR_OUT
        return 0;
    }
    copy(e,mr_mip->w1);
    for (ndig=0;size(mr_mip->w1)>0;ndig++)
    { /* break up exponent into digits, using 'base' */
      /* (note base is a power of 2.) This is fast.  */
        digits[ndig]=subdiv(_MIPP_ mr_mip->w1,B->base,mr_mip->w1);
    }

    if (ndig>B->store)
    {
        mr_free(_MIPP_ digits);
        mr_berror(_MIPP_ MR_ERR_EXP_TOO_BIG);
        MR_OUT
        return 0;
    }

    w=epoint2_init(_MIPPO_ );
    w1=epoint2_init(_MIPPO_ );

    for (d=B->base-1;d>0;d--)
    { /* brickell's method */
        for (i=0;i<ndig;i++)
        {
            if (mr_mip->user!=NULL) (*mr_mip->user)();
            if (digits[i]==d) ecurve2_add(_MIPP_ B->table[i],w1);
        }
        ecurve2_add(_MIPP_ w1,w);
    }
    d=epoint2_get(_MIPP_ w,x,y);
    epoint2_free(_MIPP_ w1);
    epoint2_free(_MIPP_ w);

    for (i=0;i<ndig;i++) digits[i]=0;
    mr_free(_MIPP_ digits);
    MR_OUT
    return d;
}

