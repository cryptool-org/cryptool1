/*
 *   MIRACL Core module - contains initialisation code and general purpose 
 *   utilities.
 *   mrcore.c
 *
 *   Copyright (c) 1988-2000 Shamus Software Ltd.
 */

#include <stdio.h>
#include <stdlib.h>
#include <miracl.h>
#include <string.h>

/*** Multi-Threaded Support ***/

#ifndef MR_GENERIC_MT

#ifdef MR_WINDOWS_MT
#include <windows.h>
DWORD mr_key;   

miracl *get_mip()
{
    return (miracl *)TlsGetValue(mr_key); 
}

void mr_init_threading()
{
    mr_key=TlsAlloc();
}

void mr_end_threading()
{
    TlsFree(mr_key);
}

#endif

#ifdef MR_UNIX_MT
#include <pthread.h>
pthread_key_t mr_key;

miracl *get_mip()
{
    return (miracl *)pthread_getspecific(mr_key); 
}

void mr_init_threading()
{
    mr_key=pthread_key_create(&mr_key,(void(*)(void *))NULL);
}

void mr_end_threading()
{
    pthread_key_delete(mr_key);
}
#endif

#ifndef MR_WINDOWS_MT
#ifndef MR_UNIX_MT
miracl *mr_mip=NULL;     /* MIRACL's one and only global variable */

miracl *get_mip()
{
    return (miracl *)mr_mip; 
}

void set_mip(miracl *n_mip)
{
	mr_mip = n_mip;
}
#endif
#endif

#endif



/* See Advanced Windows by Jeffrey Richter, Chapter 12 for methods for
   creating different instances of this global for each executing thread 
   when using WIndows '95/NT
*/


#ifndef MR_STRIPPED_DOWN
#ifndef MR_NO_STANDARD_IO

static char *names[] =
{"your program","innum","otnum","jack","normalise",
"multiply","divide","incr","decr","premult",
"subdiv","fdsize","egcd","cbase",
"cinnum","cotnum","nroot","power",
"powmod","bigdig","bigrand","nxprime","isprime",
"mirvar","mad","mirsys","putdig",
"add","subtract","select","xgcd",
"fpack","dconv","mr_shift","round","fmul",
"fdiv","fadd","fsub","fcomp","fconv",
"frecip","fpmul","fincr","fsize","ftrunc",
"frand","sftbit","build","logb2","expint",
"fpower","froot","fpi","fexp","flog","fpowf",
"ftan","fatan","fsin","fasin","fcos","facos",
"ftanh","fatanh","fsinh","fasinh","fcosh",
"facosh","flop","gprime","powltr","fft_mult",
"crt_init","crt","otstr","instr","cotstr","cinstr","powmod2",
"prepare_monty","nres","redc","nres_modmult","nres_powmod",
"nres_moddiv","nres_powltr","divisible","remain",
"fmodulo","nres_modadd","nres_modsub","nres_negate",
"ecurve_init","ecurve_add","ecurve_mult",
"epoint_init","epoint_set","epoint_get","nres_powmod2",
"nres_sqroot","sqroot","nres_premult","ecurve_mult2",
"ecurve_sub","trial_division","nxsafeprime","nres_lucas","lucas",
"brick_init","pow_brick","set_user_function",
"nres_powmodn","powmodn","ecurve_multn",
"ebrick_init","mul_brick","epoint_norm","nres_multi_inverse","mr_alloc",
"nres_dotprod","epoint_negate","ecurve_multi_add",
"ecurve2_init","epoint2_init","epoint2_set","epoint2_norm","epoint2_get",
"epoint2_comp","ecurve2_add","epoint2_negate","ecurve2_sub",
"ecurve2_multi_add","ecurve2_mult","ecurve2_multn","ecurve2_mult2",
"ebrick2_init","mul2_brick","prepare_basis","strong_bigrand",
"bytes_to_big","big_to_bytes","set_io_buffer_size"};
/* 0 - 142 (143 in all) */

#endif
#endif


#ifdef MR_NOASM

/* C only versions of muldiv/muldvd/muldvd2/muldvm */
/* Note that mr_large should be twice the size of mr_small */

mr_small muldiv(mr_small a,mr_small b,mr_small c,mr_small m,mr_small *rp)
{
    mr_small q;
    mr_large p=(mr_large)a*b+c;
    q=(mr_small)(p/m);
    *rp=(mr_small)(p-(mr_large)q*m);
    return q;
}

#ifndef MR_NOFULLWIDTH

mr_small muldvm(mr_small a,mr_small c,mr_small m,mr_small *rp)
{
    mr_small q;
    mr_large dble;
    MR_BOT(dble)=c;
    MR_TOP(dble)=a;
    q=(mr_small)(dble/m);
    *rp=(mr_small)(dble-(mr_large)q*m);
    return q;
}

mr_small muldvd(mr_small a,mr_small b,mr_small c,mr_small *rp)
{
    mr_large dble=(mr_large)a*b+c;
    *rp=(mr_small)dble;
    return MR_TOP(dble);
}

void muldvd2(mr_small a,mr_small b,mr_small *c,mr_small *rp)
{
    mr_large dble=(mr_large)a*b+*c+*rp;
    *rp=(mr_small)dble;
    *c=MR_TOP(dble);
}

#endif
#endif

#ifdef MR_NOFULLWIDTH

/* no FULLWIDTH working, so supply dummies */

mr_small muldvd(mr_small a,mr_small b,mr_small c,mr_small *rp)
{
}

mr_small muldvm(mr_small a,mr_small c,mr_small m,mr_small *rp)
{
}

void muldvd2(mr_small a,mr_small b,mr_small *c,mr_small *rp)
{
}

#endif

#ifndef MR_NO_STANDARD_IO

static void mputs(char *s)
{ /* output a string */
    int i=0;
    while (s[i]!=0) fputc((int)s[i++],stdout);
}

#endif

void mr_berror(_MIPD_ int nerr)
{  /*  Big number error routine  */
#ifndef MR_STRIPPED_DOWN

/* Roger 26.02.2001 Unreferenzierte Variable
int i;
*/
#endif

#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

if (mr_mip->ERCON)
{
    mr_mip->ERNUM=nerr;
    return;
}
#ifndef MR_NO_STANDARD_IO

#ifndef MR_STRIPPED_DOWN
mputs("\nMIRACL error from routine ");
if (mr_mip->depth<MR_MAXDEPTH) mputs(names[mr_mip->trace[mr_mip->depth]]);
else                           mputs("???");
fputc('\n',stdout);

for (i=mr_mip->depth-1;i>=0;i--)
{
    mputs("              called from ");
    if (i<MR_MAXDEPTH) mputs(names[mr_mip->trace[i]]);
    else               mputs("???");
    fputc('\n',stdout);
}

switch (nerr)
{
case 1 :
mputs("Number base too big for representation\n");
break;
case 2 :
mputs("Division by zero attempted\n");
break;
case 3 : 
mputs("Overflow - Number too big\n");
break;
case 4 :
mputs("Internal result is negative\n");
break;
case 5 : 
mputs("Input format error\n");
break;
case 6 :
mputs("Illegal number base\n");
break;
case 7 : 
mputs("Illegal parameter usage\n");
break;
case 8 :
mputs("Out of space\n");
break;
case 9 :
mputs("Even root of a negative number\n");
break;
case 10:
mputs("Raising integer to negative power\n");
break;
case 11:
mputs("Attempt to take illegal root\n");
break;
case 12:
mputs("Integer operation attempted on Flash number\n");
break;
case 13:
mputs("Flash overflow\n");
break;
case 14:
mputs("Numbers too big\n");
break;
case 15:
mputs("Log of a non-positive number\n");
break;
case 16:
mputs("Flash to double conversation failure\n");
break;
case 17:
mputs("I/O buffer overflow\n");
break;
case 18:
mputs("MIRACL not initialised - no call to mirsys()\n");
break;
case 19:
mputs("Illegal modulus \n");
break;
case 20:
mputs("No modulus defined\n");
break;
case 21:
mputs("Exponent too big\n");
break;
case 22:
mputs("Number Base must be power of 2\n");
break;
case 23:
mputs("Specified double length type isn't double length\n");
break;
case 24:
mputs("Specified basis is NOT irreducible\n");

}
exit(0);
#else
mputs("MIRACL error\n");
exit(0);
#endif

#endif
}

void mr_track(_MIPDO_ )
{ /* track course of program execution *
   * through the MIRACL routines       */

#ifndef MR_NO_STANDARD_IO
#ifndef MR_STRIPPED_DOWN
    int i;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    for (i=0;i<mr_mip->depth;i++) fputc('-',stdout);
    fputc('>',stdout);
    mputs(names[mr_mip->trace[mr_mip->depth]]);
    fputc('\n',stdout);
#endif
#endif
}

mr_small brand(_MIPDO_ )
{ /* Marsaglia & Zaman random number generator */
    int i,k;
    mr_unsign32 pdiff,t;
    mr_small r;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (sizeof(mr_utype)>sizeof(mr_unsign32))
    { /* underlying type is > 32 bits. Assume twice as long */
        mr_mip->rndptr+=2;
        if (mr_mip->rndptr<NK-1)
        {
            r=(mr_small)mr_mip->ira[mr_mip->rndptr];
            r<<=(MIRACL/2);
            r+=(mr_small)mr_mip->ira[mr_mip->rndptr+1];
            return r;
        }
    }
    else
    {
        mr_mip->rndptr++;
        if (mr_mip->rndptr<NK) return (mr_small)mr_mip->ira[mr_mip->rndptr];
    }
    mr_mip->rndptr=0;
    for (i=0,k=NK-NJ;i<NK;i++,k++)
    { /* calculate next NK values */
        if (k==NK) k=0;
        t=mr_mip->ira[k];
        pdiff=t - mr_mip->ira[i] - mr_mip->borrow;
        if (pdiff<t) mr_mip->borrow=0;
        if (pdiff>t) mr_mip->borrow=1;
        mr_mip->ira[i]=pdiff; 
    }
    if (sizeof(mr_utype)>sizeof(mr_unsign32))
    { /* double up */
        r=(mr_small)mr_mip->ira[0];
        r<<=(MIRACL/2);
        r+=(mr_small)mr_mip->ira[1];
        return r;
    }
    else return (mr_small)(mr_mip->ira[0]);
}

void irand(_MIPD_ mr_unsign32 seed)
{ /* initialise random number system */
  /* modified so that a subsequent call "stirs" in another seed value */
  /* in this way as many seed bits as desired may be used */
    int i,in;
    mr_unsign32 t,m=1L;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    mr_mip->borrow=0L;
    mr_mip->rndptr=0;
    mr_mip->ira[0]^=seed;
    for (i=1;i<NK;i++)
    { /* fill initialisation vector */
        in=(NV*i)%NK;
        mr_mip->ira[in]^=m;      /* note XOR */
        t=m;
        m=seed-m;
        seed=t;
    }
    for (i=0;i<1000;i++) brand(_MIPPO_ ); /* "warm-up" & stir the generator */
}

void mr_setbase(_MIPD_ mr_small nb)
{  /* set base. Pack as many digits as  *
    * possible into each computer word  */
    mr_small temp;
#ifndef MR_NOFULLWIDTH
    BOOL fits;
    int bits;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    fits=FALSE;
    bits=MIRACL;
    while (bits>1) 
    {
        bits/=2;
        temp=((mr_small)1<<bits);
        if (temp==nb)
        {
            fits=TRUE;
            break;
        }
        if (temp<nb || (bits%2)!=0) break;
    }
    if (fits)
    {
        mr_mip->apbase=nb;
        mr_mip->pack=MIRACL/bits;
        mr_mip->base=0;
        return;
    }
#endif
    mr_mip->apbase=nb;
    mr_mip->pack=1;
    mr_mip->base=nb;
    if (mr_mip->base==0) return;
    temp=MAXBASE/nb;
    while (temp>=nb)
    {
        temp=(temp/nb);
        mr_mip->base*=nb;
        mr_mip->pack++;
    }
}

#ifdef MR_FLASH

BOOL fit(big x,big y,int f)
{ /* returns TRUE if x/y would fit flash format of length f */
    int n,d;
    n=(int)(x[0]&(MR_OBITS));
    d=(int)(y[0]&(MR_OBITS));
    if (n==1 && x[1]==1) n=0;
    if (d==1 && y[1]==1) d=0;
    if (n+d<=f) return TRUE;
    return FALSE;
}

#endif

int mr_lent(flash x)
{ /* return length of big or flash in words */
    mr_small lx;
    lx=(x[0]&(MR_OBITS));
#ifdef MR_FLASH
    return (int)((lx&(MR_MSK))+((lx>>(MR_BTS))&(MR_MSK)));
#else
    return (int)lx;
#endif
}

void zero(flash x)
{ /* set big/flash number to zero */
    int n;
    if (x==NULL) return;
#ifdef MR_FLASH
    n=mr_lent(x);
#else
    n=(x[0]&(MR_OBITS));
#endif

    memset(x,0,(n+1)*sizeof(mr_utype));
/*
    for (i=0;i<=n;i++)
        x[i]=0;
*/
}

void convert(_MIPD_ int n ,big x)
{  /*  convert integer n to big number format  */
    int m;
    mr_small s;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    zero(x);
    if (n==0) return;
    s=0;
    if (n<0)
    {
        s=MR_MSBIT;
        n=(-n);
    }
    m=0;
    if (mr_mip->base==0)
    {
#if MR_IBITS > MIRACL
        while (n>0)
        {
            m++;
            x[m]=(mr_small)(n%(1<<(MIRACL)));
            n/=(1<<(MIRACL));
        }
#else
        m=1;
        x[m]=(mr_small)n;
#endif
    }
    else while (n>0)
    {
        m++;
        x[m]=n%(mr_mip->base);
        n/=mr_mip->base;
    }
    x[0]=(m|s);
}

void lgconv(_MIPD_ long n,big x)
{ /* convert long integer to big number format - rarely needed */
    int m;
    mr_small s;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    zero(x);
    if (n==0) return;
    s=0;
    if (n<0)
    {
        s=MR_MSBIT;
        n=(-n);
    }
    m=0;
    if (mr_mip->base==0)
    {
#if MR_LBITS > MIRACL
        while (n>0)
        {
            m++;
            x[m]=(mr_small)(n%(1L<<(MIRACL)));
            n/=(1L<<(MIRACL));
        }
#else
        m=1;
        x[m]=(mr_small)n;
#endif
    }    
    else while (n>0)
    {
        m++;
        x[m]=(mr_small)(n%(mr_mip->base));
        n/=mr_mip->base;
    }
    x[0]=(m|s);
}

flash mirvar(_MIPD_ int iv)
{ /* initialize big/flash number */
    flash x;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return NULL;

    MR_IN(23);  

    if (!(mr_mip->active))
    {
        mr_berror(_MIPP_ MR_ERR_NO_MIRSYS);
        MR_OUT  
        return NULL;
    }
    x=(mr_small *)mr_alloc(_MIPP_ mr_mip->nib+1,sizeof(mr_small));
    if (x==NULL)
    {
        MR_OUT 
        return x;
    }
    if (iv!=0) convert(_MIPP_ iv,x);
    MR_OUT 
    return x;
}

void set_user_function(_MIPD_ BOOL (*user)(void))
{
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(111)

    if (!(mr_mip->active))
    {
        mr_berror(_MIPP_ MR_ERR_NO_MIRSYS);
        MR_OUT
        return;
    }

    mr_mip->user=user;

    MR_OUT
}

void set_io_buffer_size(_MIPD_ int len)
{
    int i;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (len<0) return;
    MR_IN(142)
    for (i=0;i<mr_mip->IOBSIZ;i++) mr_mip->IOBUFF[i]=0;
    mr_free(_MIPP_ mr_mip->IOBUFF);
    if (len==0) 
    {
        MR_OUT
        return;
    }
    mr_mip->IOBSIZ=len;
    mr_mip->IOBUFF=mr_alloc(_MIPP_ len+1,1);
    mr_mip->IOBUFF[0]='\0';
    MR_OUT
}

miracl *mirsys(int nd,mr_small nb)
{  /*  Initialize MIRACL system to   *
    *  use numbers to base nb, and   *
    *  nd digits or (-nd) bytes long */
    int i;
    mr_small b;

/*** Multi-Threaded support ***/

#ifndef MR_GENERIC_MT

#ifdef MR_WINDOWS_MT
    miracl *mr_mip=(miracl *)mr_alloc(1,sizeof(miracl));
    TlsSetValue(mr_key,mr_mip);
#endif

#ifdef MR_UNIX_MT
    miracl *mr_mip=(miracl *)mr_alloc(1,sizeof(miracl));
    pthread_setspecific(mr_key,mr_mip);
#endif

#ifndef MR_WINDOWS_MT
#ifndef MR_UNIX_MT
    mr_mip=NULL;
    mr_mip=(miracl *)mr_alloc(1,sizeof(miracl));
#endif
#endif
    mr_mip=get_mip();
#else
    miracl *mr_mip=(miracl *)mr_alloc(NULL,1,sizeof(miracl));
#endif

    if (mr_mip==NULL) return NULL;
    mr_mip->depth=0;
    mr_mip->trace[0]=0;
    mr_mip->depth++;
    mr_mip->trace[mr_mip->depth]=25;
                    /* digest hardware configuration */

#ifdef MR_NO_STANDARD_IO
    mr_mip->ERCON=TRUE;
#else
    mr_mip->ERCON=FALSE;
#endif
    mr_mip->logN=0;
    mr_mip->degree=0;
    mr_mip->chin.NP=0;
    mr_mip->user=NULL;
    mr_set_align(_MIPP_ 0);
    
#ifdef MR_NOFULLWIDTH
    if (nb==0)
    {
        mr_berror(_MIPP_ MR_ERR_BAD_BASE);
        mr_mip->depth--;
        return mr_mip;
    }
#endif
#ifdef mr_dltype
    if (sizeof(mr_dltype)<2*sizeof(mr_utype))
    { /* double length type, isn't */
        mr_berror(_MIPP_ MR_ERR_NOT_DOUBLE_LEN);
        mr_mip->depth--;
        return mr_mip;
    }
#endif

    if (nb==1 || nb>MAXBASE)
    {
        mr_berror(_MIPP_ MR_ERR_BAD_BASE);
        mr_mip->depth--;
        return mr_mip;
    }
    mr_setbase(_MIPP_ nb);

    b=mr_mip->base;
    mr_mip->lg2b=0;
    mr_mip->base2=1;
    if (b==0)
    {
        mr_mip->lg2b=MIRACL;
        mr_mip->base2=0;
    }
    else while (b>1)
    {
        b/=2;
        mr_mip->lg2b++;
        mr_mip->base2*=2;
    }
    if (nd>0)
        mr_mip->nib=(nd-1)/mr_mip->pack+1;
    else
        mr_mip->nib=(mr_mip->lg2b-8*nd-1)/mr_mip->lg2b;
    if (mr_mip->nib<2) mr_mip->nib=2;
#ifdef MR_FLASH
    mr_mip->workprec=mr_mip->nib;
    mr_mip->stprec=mr_mip->nib;
    while (mr_mip->stprec>2 && mr_mip->stprec>MR_FLASH/mr_mip->lg2b) 
        mr_mip->stprec=(mr_mip->stprec+1)/2;
    if (mr_mip->stprec<2) mr_mip->stprec=2;
    mr_mip->pi=NULL;
#endif
    mr_mip->check=ON;
    mr_mip->IOBASE=10;   /* defaults */
    mr_mip->ERNUM=0;
    mr_mip->RPOINT=OFF;
    mr_mip->NTRY=6;
    mr_mip->EXACT=TRUE;
    mr_mip->TRACER=OFF;
    mr_mip->INPLEN=0;
    mr_mip->PRIMES=NULL;
    mr_mip->IOBSIZ=1024;
    mr_mip->IOBUFF=mr_alloc(_MIPP_ 1025,1);
    mr_mip->IOBUFF[0]='\0';
    for (i=0;i<NK;i++) mr_mip->ira[i]=0L;
    irand(_MIPP_ 0L);     /* start rand number generator */
    mr_mip->nib=2*mr_mip->nib+1;
#ifdef MR_FLASH
    if (mr_mip->nib!=(mr_mip->nib&(MR_MSK)) || mr_mip->nib > MR_TOOBIG)
#else
    if (mr_mip->nib!=(mr_mip->nib&(MR_OBITS)) || mr_mip->nib>MR_TOOBIG)
#endif
    {
        mr_berror(_MIPP_ MR_ERR_TOO_BIG);
        mr_mip->nib=(mr_mip->nib-1)/2;
        mr_mip->depth--;
        return mr_mip;
    }
    mr_mip->modulus=NULL;
    mr_mip->A=NULL;
    mr_mip->B=NULL;
    mr_mip->C=NULL;

    mr_mip->M=0;
    mr_mip->fin=FALSE;
    mr_mip->fout=FALSE;
    mr_mip->active=ON;
    mr_mip->w0=mirvar(_MIPP_ 0); /* w0 is double length  */
    mr_mip->nib=(mr_mip->nib-1)/2;
#ifdef MR_KCM
    mr_mip->big_ndash=NULL;
    mr_mip->ws=mirvar(_MIPP_ 0);
#endif

    mr_mip->w1=mirvar(_MIPP_ 0); /* initialize workspace */
    mr_mip->w2=mirvar(_MIPP_ 0);
    mr_mip->w3=mirvar(_MIPP_ 0);
    mr_mip->w4=mirvar(_MIPP_ 0);

    mr_mip->nib=2*mr_mip->nib+1;             /* double length */
    mr_mip->w5=mirvar(_MIPP_ 0);
    mr_mip->w6=mirvar(_MIPP_ 0);
    mr_mip->w7=mirvar(_MIPP_ 0);
    mr_mip->nib=(mr_mip->nib-1)/2;

    mr_mip->w5d=&(mr_mip->w5[mr_mip->nib+1]);   /* use top-halves */
    mr_mip->w6d=&(mr_mip->w6[mr_mip->nib+1]);
    mr_mip->w7d=&(mr_mip->w7[mr_mip->nib+1]);

    mr_mip->w8=mirvar(_MIPP_ 0);
    mr_mip->w9=mirvar(_MIPP_ 0);
    mr_mip->w10=mirvar(_MIPP_ 0);
    mr_mip->w11=mirvar(_MIPP_ 0);
    mr_mip->w12=mirvar(_MIPP_ 0);
    mr_mip->w13=mirvar(_MIPP_ 0);
    mr_mip->w14=mirvar(_MIPP_ 0);
    mr_mip->w15=mirvar(_MIPP_ 0); 
    mr_mip->depth--;
    return mr_mip;
} 

void mirkill(_MIPD_ big x)
{ /* kill a big/flash variable, that is set it to zero
     and free its memory */
    if (x==NULL) return;
    zero(x);
    mr_free(_MIPP_ x);
}

void mirexit(_MIPDO_ )
{ /* clean up after miracl */
    int i;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    mr_mip->ERCON=FALSE;
    mr_mip->active=OFF;
    mirkill(_MIPP_ mr_mip->w0);
    mirkill(_MIPP_ mr_mip->w1);
    mirkill(_MIPP_ mr_mip->w2);
    mirkill(_MIPP_ mr_mip->w3);
    mirkill(_MIPP_ mr_mip->w4);
    mirkill(_MIPP_ mr_mip->w5);
    mirkill(_MIPP_ mr_mip->w6);
    mirkill(_MIPP_ mr_mip->w7);
    mirkill(_MIPP_ mr_mip->w8);
    mirkill(_MIPP_ mr_mip->w9);
    mirkill(_MIPP_ mr_mip->w10);
    mirkill(_MIPP_ mr_mip->w11);
    mirkill(_MIPP_ mr_mip->w12);
    mirkill(_MIPP_ mr_mip->w13);
    mirkill(_MIPP_ mr_mip->w14);
    mirkill(_MIPP_ mr_mip->w15);
#ifdef MR_FLASH
    if (mr_mip->pi!=NULL) mirkill(_MIPP_ mr_mip->pi);
#endif
    for (i=0;i<MR_HASH_BYTES;i++) mr_mip->pool[i]=0;
    for (i=0;i<NK;i++) mr_mip->ira[i]=0L;
    set_io_buffer_size(_MIPP_ 0);
    if (mr_mip->PRIMES!=NULL) mr_free(_MIPP_ mr_mip->PRIMES);

#ifdef MR_KCM
    if (mr_mip->big_ndash!=NULL) mirkill(_MIPP_ mr_mip->big_ndash); 
    mirkill(_MIPP_ mr_mip->ws);
#endif

    if (mr_mip->modulus!=NULL) mirkill(_MIPP_ mr_mip->modulus);
    if (mr_mip->A!=NULL) mirkill(_MIPP_ mr_mip->A);
    if (mr_mip->B!=NULL) mirkill(_MIPP_ mr_mip->B);
    if (mr_mip->C!=NULL) mirkill(_MIPP_ mr_mip->C);

    mr_set_align(_MIPP_ 0);
    mr_free(_MIPP_ mr_mip);
#ifndef MR_GENERIC_MT
#ifndef MR_WINDOWS_MT
#ifndef MR_UNIX_MT
    mr_mip=NULL;
#endif   
#endif   
#endif   
}

int exsign(flash x)
{ /* extract sign of big/flash number */
    if ((x[0]&(MR_MSBIT))==0) return PLUS;
    else                      return MINUS;    
}

void insign(int s,flash x)
{  /* assert sign of big/flash number */
    if (x[0]==0) return;
    if (s<0) x[0]|=MR_MSBIT;
    else     x[0]&=MR_OBITS;
}   

void mr_lzero(big x)
{  /*  strip leading zeros from big number  */
    mr_small s;
    int m;
    s=(x[0]&(MR_MSBIT));
    m=(int)(x[0]&(MR_OBITS));
    while (m>0 && x[m]==0)
        m--;
    x[0]=m;
    if (m>0) x[0]|=s;
}

int getdig(_MIPD_ big x,int i)
{  /* extract a packed digit */
    int k;
    mr_small n;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    i--;
    n=x[i/mr_mip->pack+1];
    if (mr_mip->pack==1) return (int)n;
    k=i%mr_mip->pack;
    for (i=1;i<=k;i++)
        n=(n/mr_mip->apbase);
    return (int)(n%mr_mip->apbase);
}

int numdig(_MIPD_ big x)
{  /* returns number of digits in x */
    int nd;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

    if (x[0]==0) return 0;

    nd=(int)(x[0]&(MR_OBITS))*mr_mip->pack;
    while (getdig(_MIPP_ x,nd)==0)
        nd--;
    return nd;
} 

void putdig(_MIPD_ int n,big x,int i)
{  /* insert a digit into a packed word */
    int j,k,lx;
    mr_small s,m,p;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(26)

    s=(x[0]&(MR_MSBIT));
    lx=(int)(x[0]&(MR_OBITS));
    m=getdig(_MIPP_ x,i);
    p=n;
    i--;
    j=i/mr_mip->pack+1;
    k=i%mr_mip->pack;
    for (i=1;i<=k;i++)
    {
        m*=mr_mip->apbase;
        p*=mr_mip->apbase;
    }
    if (j>mr_mip->nib && (mr_mip->check || j>2*mr_mip->nib))
    {
        mr_berror(_MIPP_ MR_ERR_OVERFLOW);
        MR_OUT
        return;
    }
    x[j]=(x[j]-m)+p;
    if (j>lx) x[0]=(j|s);
    mr_lzero(x);
    MR_OUT
}

void copy(flash x,flash y)
{  /* copy x to y: y=x  */
    int nx,ny;
    if (x==y) return;

    if (x==NULL)
    { 
        zero(y);
        return;
    }

#ifdef MR_FLASH    
    ny=mr_lent(y);
    nx=mr_lent(x);
#else
    ny=(y[0]&(MR_OBITS));
    nx=(x[0]&(MR_OBITS));
#endif

    if (ny>nx) memset(&y[nx+1],0,(ny-nx)*sizeof(mr_utype));
    memcpy(y,x,(nx+1)*sizeof(mr_utype));

/*
    for (i=nx+1;i<=ny;i++)
        y[i]=0;
    for (i=0;i<=nx;i++)
        y[i]=x[i];
*/
}

void negate(flash x,flash y)
{ /* negate a big/flash variable: y=-x */
    copy(x,y);
    if (y[0]!=0) y[0]^=MR_MSBIT;
}

void absol(flash x,flash y)
{ /* y=abs(x) */
    copy(x,y);
    y[0]&=MR_OBITS;
}

BOOL mr_notint(flash x)
{ /* returns TRUE if x is Flash */
#ifdef MR_FLASH
    if ((((x[0]&(MR_OBITS))>>(MR_BTS))&(MR_MSK))!=0) return TRUE;
#endif
    return FALSE;
}

void mr_shift(_MIPD_ big x,int n,big w)
{ /* set w=x.(mr_base^n) by shifting */
    mr_small s;
    int i,bl;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    copy(x,w);
    if (w[0]==0 || n==0) return;
    MR_IN(33)

    if (mr_notint(w)) mr_berror(_MIPP_ MR_ERR_INT_OP);
    s=(w[0]&(MR_MSBIT));
    bl=(int)(w[0]&(MR_OBITS))+n;
    if (bl<=0)
    {
        zero(w);
        MR_OUT
        return;
    }
    if (bl>mr_mip->nib && mr_mip->check) mr_berror(_MIPP_ MR_ERR_OVERFLOW);
    if (mr_mip->ERNUM)
    {
        MR_OUT
        return;
    }
    if (n>0)
    {
        for (i=bl;i>n;i--)
            w[i]=w[i-n];
        for (i=1;i<=n;i++)
            w[i]=0;
    }
    else
    {
        n=(-n);
        for (i=1;i<=bl;i++)
            w[i]=w[i+n];
        for (i=1;i<=n;i++)
            w[bl+i]=0;
    }
    w[0]=(bl|s);
    MR_OUT
}

int size(big x)
{  /*  get size of big number;  convert to *
    *  integer - if possible               */
    int n;
    mr_small s,m;
    s=(x[0]&MR_MSBIT);
    m=(x[0]&MR_OBITS);
    if (m==0) return 0;
    if (m==1 && x[1]<(mr_small)MR_TOOBIG) n=(int)x[1];
    else                                  n=MR_TOOBIG;
    if (s==MR_MSBIT) return (-n);
    return n;
}

int compare(big x,big y)
{  /* compare x and y: =1 if x>y  =-1 if x<y *
    *  =0 if x=y                             */
    int m,n,sig;
    mr_small sx,sy;
    if (x==y) return 0;
    sx=(x[0]&MR_MSBIT);
    sy=(y[0]&MR_MSBIT);
    if (sx==0) sig=PLUS;
    else       sig=MINUS;
    if (sx!=sy) return sig;
    m=(int)(x[0]&MR_OBITS);
    n=(int)(y[0]&MR_OBITS);
    if (m>n) return sig;
    if (m<n) return -sig;
    while (m>0)
    { /* check digit by digit */
        if (x[m]>y[m]) return sig;
        if (x[m]<y[m]) return -sig;
        m--;
    }
    return 0;
}

#ifdef MR_FLASH

void fpack(_MIPD_ big n,big d,flash x)
{ /* create floating-slash number x=n/d from *
   * big integer numerator and denominator   */
    mr_small s;
    int i,ld,ln;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;

    MR_IN(31)

    ld=(int)(d[0]&MR_OBITS);
    if (ld==0) mr_berror(_MIPP_ MR_ERR_FLASH_OVERFLOW);
    if (ld==1 && d[1]==1) ld=0;
    if (x==d) mr_berror(_MIPP_ MR_ERR_BAD_PARAMETERS);
    if (mr_notint(n) || mr_notint(d)) mr_berror(_MIPP_ MR_ERR_INT_OP);
    s=(n[0]&MR_MSBIT);
    ln=(int)(n[0]&MR_OBITS);
    if (ln==1 && n[1]==1) ln=0;
    if ((ld+ln>mr_mip->nib) && (mr_mip->check || ld+ln>2*mr_mip->nib)) 
        mr_berror(_MIPP_ MR_ERR_FLASH_OVERFLOW);
    if (mr_mip->ERNUM)
    {
       MR_OUT
       return;
    }
    copy(n,x);
    if (n[0]==0)
    {
        MR_OUT
        return;
    }
    s^=(d[0]&MR_MSBIT);
    if (ld==0)
    {
        if (x[0]!=0) x[0]|=s;
        MR_OUT
        return;
    }
    for (i=1;i<=ld;i++)
        x[ln+i]=d[i];
    x[0]=(s|(ln+((mr_small)ld<<MR_BTS)));
    MR_OUT
}

void numer(_MIPD_ flash x,big y)
{ /* extract numerator of x */
    int i,ln,ld;
    mr_small ly,s;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    if (mr_notint(x))
    {
        s=(x[0]&MR_MSBIT);
        ly=(x[0]&MR_OBITS);
        ln=(int)(ly&MR_MSK);
        if (ln==0)
        {
            if(s==MR_MSBIT) convert(_MIPP_ (-1),y);
            else            convert(_MIPP_ 1,y);
            return;
        }
        ld=(int)((ly>>MR_BTS)&MR_MSK);
        if (x!=y)
        {
            for (i=1;i<=ln;i++) y[i]=x[i];
            for (i=ln+1;i<=mr_lent(y);i++) y[i]=0;
        }
        else for (i=1;i<=ld;i++) y[ln+i]=0;
        y[0]=(ln|s);
    }
    else copy(x,y);
}

void denom(_MIPD_ flash x,big y)
{ /* extract denominator of x */
    int i,ln,ld;
    mr_small ly;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    if (!mr_notint(x))
    {
        convert(_MIPP_ 1,y);
        return;
    }
    ly=(x[0]&MR_OBITS);
    ln=(int)(ly&MR_MSK);
    ld=(int)((ly>>MR_BTS)&MR_MSK);
    for (i=1;i<=ld;i++)
        y[i]=x[ln+i];
    if (x==y) for (i=1;i<=ln;i++) y[ld+i]=0;
    else for (i=ld+1;i<=mr_lent(y);i++) y[i]=0;
    y[0]=ld;
}

#endif

int igcd(int x,int y)
{ /* integer GCD, returns GCD of x and y */
    int r;
    if (y==0) return x;
    while ((r=x%y)!=0)
        x=y,y=r;
    return y;
}

int isqrt(int num,int guess)
{ /* square root of an integer */
    int sqr;
    for (;;)
    { /* Newtons iteration */
        sqr=guess+(((num/guess)-guess)/2);
        if (sqr==guess) return sqr;
        guess=sqr;
    }
}

/* routines to support sliding-windows exponentiation *
 * in various contexts */

int mr_testbit(_MIPD_ big x,int i)
{ /* return value of i-th bit of big */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if ((x[1+i/mr_mip->lg2b] & ((mr_small)1<<(i%mr_mip->lg2b))) >0) return 1;
    return 0;
}

int mr_window(_MIPD_ big x,int i,int *nbs,int * nzs)
{ /* returns sliding window value, max. of 5 bits,         *
   * starting at i-th bit of big x. nbs is number of bits  *
   * processed, nzs is the number of additional trailing   *
   * zeros detected. Returns valid bit pattern 1x..x1 with *
   * no two adjacent 0's. So 10101 will return 21 with     *
   * nbs=5, nzs=0. 11001 will return 3, with nbs=2, nzs=2, *
   * having stopped after the first 11..  */

    int j,r,w;
    w=5;

/* check for leading 0 bit */

    *nbs=1;
    *nzs=0;
    if (!mr_testbit(_MIPP_ x,i)) return 0;

/* adjust window size if not enough bits left */
   
    if (i-w+1<0) w=i+1;

    r=1;
    for (j=i-1;j>i-w;j--)
    { /* accumulate bits. Abort if two 0's in a row */
        (*nbs)++;
        r*=2;
        if (mr_testbit(_MIPP_ x,j)) r+=1;
        if (r%4==0)
        { /* oops - too many zeros - shorten window */
            r/=4;
            *nbs-=2;
            *nzs=2;
            break;
        }
    }
    if (r%2==0)
    { /* remove trailing 0 */
        r/=2;
        *nzs=1;
        (*nbs)--;
    }
    return r;
}

int mr_window2(_MIPD_ big x,big y,int i,int *nbs,int *nzs)
{ /* two bit window for double exponentiation */
    int r,w;
    BOOL a,b,c,d;
    w=2;
    *nbs=1;
    *nzs=0;

/* check for two leading 0's */
    a=mr_testbit(_MIPP_ x,i); b=mr_testbit(_MIPP_ y,i);

    if (!a && !b) return 0;
    if (i<1) w=1;

    if (a)
    {
        if (b) r=3;
        else   r=2;
    }
    else r=1;
    if (w==1) return r;

    c=mr_testbit(_MIPP_ x,i-1); d=mr_testbit(_MIPP_ y,i-1);

    if (!c && !d) 
    {
        *nzs=1;
        return r;
    }

    *nbs=2;
    r*=4;
    if (c)
    {
        if (d) r+=3;
        else   r+=2;
    }
    else r+=1;
    return r;
}

int mr_naf_window(_MIPD_ big x,big x3,int i,int *nbs,int *nzs)
{ /* returns sliding window value, max of 5 bits           *
   * starting at i-th bit of x. nbs is number of bits      *
   * processed. nzs is number of additional trailing       *    
   * zeros detected. x and x3 (which is 3*x) are           *
   * combined to produce the NAF (non-adjacent form)       *
   * So if x=11011(27) and x3 is 1010001, the LSB is       *
   * ignored and the value 100T0T (32-4-1=27) processed,   *
   * where T is -1. Note x.P = (3x-x)/2.P. This value will *
   * return +7, with nbs=4 and nzs=1, having stopped after *
   * the first 4 bits. Note in an NAF non-zero elements    *
   * are never side by side, so 10T10T won't happen        */

    int nb,j,r,w;
    BOOL last;
    w=5;

 /* get first bit */
    nb=mr_testbit(_MIPP_ x3,i)-mr_testbit(_MIPP_ x,i);

    *nbs=1;
    *nzs=0;
    if (nb==0) return 0;
    last=FALSE;
    if (i<=w) 
    {
        w=i;
        last=TRUE;
    }

    if (nb>0) r=1;
    else      r=(-1);

    for (j=i-1;j>i-w;j--)
    { /* scan the bits */
        (*nbs)++;
        r*=2;
        nb=mr_testbit(_MIPP_ x3,j)-mr_testbit(_MIPP_ x,j);
        if (nb==0) continue;
        if (nb>0) r+=1;
        if (nb<0) r-=1;
           
    } 
    if (!last && r%2!=0) (*nzs)++;
    while (r%2==0)
    { /* remove trailing zeros */
        r/=2;
        (*nzs)++;
        (*nbs)--;
    }     
    return r;
}

BOOL point_at_infinity(epoint *p)
{
    if (p==NULL) return FALSE;
    if (p->marker==MR_EPOINT_INFINITY) return TRUE;
    return FALSE;
}

