/*
 *   Benchmarking program for PK implementations
 *
 *   Copyright (c) 1988-1999 Shamus Software Ltd.
 */

#include <stdio.h>
#include <time.h>
#include <miracl.h>

/* define minimum duration of each timing, and min. number of iterations */

#define MIN_TIME 10.0
#define MIN_ITERS 20 

/* random "safe" primes - (p-1)/2 is also prime */

char p512[]="A89BmxRFLAnMTGV1EofBF3t9vxHwLw3upSiJQqGrSSJanNwAWm4qeIpR0QZos81Cb0T3GSB8Vvioo2ShdHeocZl";
char p1024[]="33pn5XYfRZ6oa1SgeSZ0gLXbIHYKsAL2vf2hMPp4BShBUUwVqJSaZMHBtYRr2C8CtD2ql3cKco8tsbol9KiiW0kmgYdmX2OYuDirwVHBXU6iarsuWLsFI8f9IcXF5mQUhhIfNL1UgB9iOopI4DZJdaAkweMrr0L7H6DTcJCv4uOG8l";
char p2048[]="9JhODtckdgHoisG3BF7icLO1W2kQN8uERdD45ta8ECK2pSl74xmjtptZhoFRXLCn8SHJtmwXTuf6aUbUUGsT6dE8GMWSkdg3qN4owcJE6wuCUiKKDOrsUEaFA6GCaSoHrHd6upEOTFJrSt5JZvvPUmZExbgTtVkZaM3EHVO5hhmaOglEXNmWbQlSZR57EPH4VS5nYPHsj3YEqtQjBxOg509VY3Efa3WCBXSILEksrBCdxBFeboPQ2ImO8gt52UX68ClTq4hUO7HltCJ8DEXT0QitGp5G39H3EGlBM7a1Pto1XRctShgDCJkKtedRvCTHJ81IaLUM2QRgVvY2oAUfU6DpqPl";


/* 160-bit Elliptic Curve A= -3 (1,y) is of prime order r wrt prime p */

char b160[]="547961736808018748879088091015409822321903727720";
char y160[]="1184021062507719516935416374276431034553065993786";
char p160[]="1243254415344564576487568858887587143562341624873";
char r160[]="1243254415344564576487570064860738948886682236669";


/* 192-bit Elliptic Curve A= -3 (1,y) is of prime order r wrt prime p */

char b192[]="4061049254666112630970447728594959377821841236338949398359";
char y192[]="939373580274738592696031201994651073677369517020051213856";
char p192[]="4361274637164371634176431764172114141371368173651736587859";
char r192[]="4361274637164371634176431764042976768701814568420333347189";

/* 224-bit Elliptic Curve A= -3 (1,y) is of prime order r wrt prime p */

char b224[]="17383927112623192126321700675122043803151281370446907580591543997888";
char y224[]="6566202929975094781252846334642707436688198986599754639429350077046";
char p224[]="26237462376427386428736423786423764364625346524653462546544347644653";
char r224[]="26237462376427386428736423786423773752689811507809031319417547459991";

/* 256-bit Elliptic Curve A= -3 (1,y) is of prime order r wrt prime p */

char b256[]="25389140340672155341527372976612393184553582461816899055687141548002290977046";
char y256[]="51289739734510562976895380525256763300476168821636300126346201758371757118206";
char p256[]="115324781748134865946503563657643838352352623747656242345890742746828256867467";
char r256[]="115324781748134865946503563657643838352221626521810006206950260876359658535911";

/* Elliptic Curve wrt GF(2^163). This is NIST standard Curve */ 

int  A163=1;
char B163[]="20A601907B8C953CA1481EB10512F78744A3205FD";
char x163[]="3F0EBA16286A2D57EA0991168D4994637E8343E36";
char y163[]="D51FBC6C71A0094FA2CDD545B11C5C0C797324F1";
int  m163=163;
int  a163=7;
int  b163=6;
int  c163=3;
char r163[]="5846006549323611672814742442876390689256843201587";
int cf163=2;

/* Elliptic Curve wrt GF(2^233). This is NIST standard Curve */ 

int  A233=1;
char B233[]="66647EDE6C332C7F8C0923BB58213B333B20E9CE4281FE115F7D8F90AD";
char x233[]="FAC9DFCBAC8313BB2139F1BB755FEF65BC391F8B36F8F8EB7371FD558B";
char y233[]="1006A08A41903350678E58528BEBF8A0BEFF867A7CA36716F7E01F81052";
int  m233=233;
int  a233=74;
int  b233=0;
int  c233=0;
char r233[]="6901746346790563787434755862277025555839812737345013555379383634485463";
int cf233=2;

/* Elliptic Curve wrt GF(2^283). This is NIST standard Curve */ 

int  A283=1;
char B283[]="27B680AC8B8596DA5A4AF8A19A0303FCA97FD7645309FA2A581485AF6263E313B79A2F5";
char x283[]="5F939258DB7DD90E1934F8C70B0DFEC2EED25B8557EAC9C80E2E198F8CDBECD86B12053";
char y283[]="3676854FE24141CB98FE6D4B20D02B4516FF702350EDDB0826779C813F0DF45BE8112F4";
int  m283=283;
int  a283=12;
int  b283=7;
int  c283=5;
char r283[]="7770675568902916283677847627294075626569625924376904889109196526770044277787378692871"; 
int cf283=2;

void primemod(int bits,big p)
{
    do {
        printf("%d bit prime.....\n",bits);
        bigdig(bits,2,p);
        nxprime(p,p);
    } while (logb2(p)!=bits);
}

double powers(int gb,int eb,big p)
{
    int iterations=0;
    big g,e,w;
    clock_t start;
    double elapsed;
    g=mirvar(0);
    e=mirvar(0);
    w=mirvar(0);
    bigdig(gb,2,g);
    bigdig(eb,2,e);
    start=clock();

    do {
       powmod(g,e,p,w);
       iterations++;
       elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);

    elapsed=1000.0*elapsed/iterations;
    printf("R - %8d iterations of %4d/%4d ",iterations,gb,eb);
    printf(" %8.2lf ms per iteration\n",elapsed);
    mirkill(w);
    mirkill(e);
    mirkill(g);
    return elapsed;
}

double mults(int eb,epoint *g)
{
    big e;
    int iterations=0;
    clock_t start;
    double elapsed;
    epoint *w=epoint_init();
    epoint *r=epoint_init();
    e=mirvar(0);
    bigdig(eb,2,e);
    ecurve_mult(e,g,r);   /* generate a random point on the curve */
    bigdig(eb,2,e);
    start=clock();

    do {
       ecurve_mult(e,r,w);
       iterations++;
       elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);

    elapsed=1000.0*elapsed/iterations;
    printf("ER - %8d iterations             ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

    epoint_free(r);
    epoint_free(w);
    mirkill(e);
    return elapsed;
}

double mults2(int eb,epoint *g)
{
    big e;
    int iterations=0;
    clock_t start;
    double elapsed;
    epoint *w=epoint2_init();
    epoint *r=epoint2_init();
    e=mirvar(0);
    bigdig(eb,2,e);
    ecurve2_mult(e,g,r);   /* generate a random point on the curve */
    bigdig(eb,2,e);
    start=clock();

    do {
       ecurve2_mult(e,r,w);
       iterations++;
       elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);

    elapsed=1000.0*elapsed/iterations;
    printf("ER - %8d iterations             ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

    epoint2_free(r);
    epoint2_free(w);
    mirkill(e);
    return elapsed;
}

double powers_small_base(int g,int eb,big p)
{
    int iterations=0;
    big e,w;
    clock_t start;
    double elapsed;
    e=mirvar(0);
    w=mirvar(0);
    bigdig(eb,2,e);
    start=clock();

    do {
        powltr(g,e,p,w);
        iterations++;
        elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);

    elapsed=1000.0*elapsed/iterations;
    printf("S - %8d iterations of  g=%d/%4d ",iterations,g,eb);
    printf(" %8.2lf ms per iteration\n",elapsed);

    mirkill(w);
    mirkill(e);
    return elapsed;
}

double powers_double(int gb,int eb,big p)
{
    int iterations=0;
    clock_t start;
    double elapsed;
    big g1,e1,g2,e2,w;
    g1=mirvar(0);
    e1=mirvar(0);
    g2=mirvar(0);
    e2=mirvar(0);
    w=mirvar(0);
    bigdig(gb,2,g1);
    bigdig(gb,2,g2);
    bigdig(eb,2,e1);
    bigdig(eb,2,e2);
    start=clock();
    do {
        powmod2(g1,e1,g2,e2,p,w);
        iterations++;
        elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);

    elapsed=1000.0*elapsed/iterations;
    printf("D - %8d iterations of %4d/%4d ",iterations,gb,eb);
    printf(" %8.2lf ms per iteration\n",elapsed);

    mirkill(w);
    mirkill(e2);
    mirkill(g2);
    mirkill(e1);
    mirkill(g1);
    return elapsed;
}

double mult_double(int eb,epoint *g)
{
    big e1,e2;
    int iterations=0;
    clock_t start;
    double elapsed;
    epoint *w=epoint_init();
    epoint *r1=epoint_init();
    epoint *r2=epoint_init();
    e1=mirvar(0);
    e2=mirvar(0);
    bigdig(eb,2,e1);
    ecurve_mult(e1,g,r1);   /* generate a random point on the curve */
    bigdig(eb,2,e2);
    ecurve_mult(e2,g,r2);   /* generate a random point on the curve */
    bigdig(eb,2,e1);
    bigdig(eb,2,e2);
    start=clock();

    do {
       ecurve_mult2(e1,r1,e2,r2,w);
       iterations++;
       elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);

    elapsed=1000.0*elapsed/iterations;
    printf("ED - %8d iterations             ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

    epoint_free(r2);
    epoint_free(r1);
    epoint_free(w);
    mirkill(e2);
    mirkill(e1);
    return elapsed;
}


double mult2_double(int eb,epoint *g)
{
    big e1,e2;
    int iterations=0;
    clock_t start;
    double elapsed;
    epoint *w=epoint2_init();
    epoint *r1=epoint2_init();
    epoint *r2=epoint2_init();
    e1=mirvar(0);
    e2=mirvar(0);
    bigdig(eb,2,e1);
    ecurve2_mult(e1,g,r1);   /* generate a random point on the curve */
    bigdig(eb,2,e2);
    ecurve2_mult(e2,g,r2);   /* generate a random point on the curve */
    bigdig(eb,2,e1);
    bigdig(eb,2,e2);
    start=clock();

    do {
       ecurve2_mult2(e1,r1,e2,r2,w);
       iterations++;
       elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);

    elapsed=1000.0*elapsed/iterations;
    printf("ED - %8d iterations             ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

    epoint2_free(r2);
    epoint2_free(r1);
    epoint2_free(w);
    mirkill(e2);
    mirkill(e1);
    return elapsed;
}

double powers_precomp(int gb,int eb,big p)
{
    int iterations=0;
    clock_t start;
    double elapsed;
    brick binst;
    big g,e,w;
    g=mirvar(0);
    e=mirvar(0);
    w=mirvar(0);
    bigdig(gb,2,g);
   
    brick_init(&binst,g,p,eb);
 
    bigdig(eb,2,e);

    start=clock();
    do {
        pow_brick(&binst,e,w);
        iterations++;
        elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);

    elapsed=1000.0*elapsed/iterations;
    printf("P - %8d iterations of %4d/%4d ",iterations,gb,eb);
    printf(" %8.2lf ms per iteration\n",elapsed);

    brick_end(&binst);
   
    mirkill(w);
    mirkill(e);
    mirkill(g);
    return elapsed;
}

double mult_precomp(int eb,big x,big y,big a,big b,big p)
{
    big e,c,d;
    int iterations=0;
    ebrick binst;
    clock_t start;
    double elapsed;
    e=mirvar(0);
    c=mirvar(0);
    d=mirvar(0);
    ebrick_init(&binst,x,y,a,b,p,eb);
    bigdig(eb,2,e);
    start=clock();

    do {
       mul_brick(&binst,e,c,d);
       iterations++;
       elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);

    elapsed=1000.0*elapsed/iterations;
    printf("EP - %8d iterations             ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

    ebrick_end(&binst);
    mirkill(d);
    mirkill(c);
    mirkill(e);
    return elapsed;
}

double mult2_precomp(int eb,big x,big y,big a2,big a6,int M,int A,int B,int C)
{
    big e,c,d;
    int iterations=0;
    ebrick2 binst;
    clock_t start;
    double elapsed;
    e=mirvar(0);
    c=mirvar(0);
    d=mirvar(0);
    ebrick2_init(&binst,x,y,a2,a6,M,A,B,C,eb);
    bigdig(eb,2,e);
    start=clock();

    do {
       mul2_brick(&binst,e,c,d);
       iterations++;
       elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);

    elapsed=1000.0*elapsed/iterations;
    printf("EP - %8d iterations             ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

    ebrick2_end(&binst);
    mirkill(d);
    mirkill(c);
    mirkill(e);
    return elapsed;
}

double powers_small_exp(int gb,long ex,big p)
{
    int iterations=0;
    big g,e,w;
    clock_t start;
    double elapsed;
    g=mirvar(0);
    e=mirvar(0);
    w=mirvar(0);
    bigdig(gb,2,g);
    start=clock();
    lgconv(ex,e);
    do {
       power(g,ex,p,w);
       iterations++;
       elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);

    elapsed=1000.0*elapsed/iterations;
    if (ex==257L)
        printf("V - %8d iterations of %4d/e=F3 ",iterations,gb,ex);
    if (ex==65537L)
        printf("V - %8d iterations of %4d/e=F4 ",iterations,gb,ex);
    if (ex!=257L && ex!=65537L)
        printf("V - %8d iterations of %4d/e=%2ld ",iterations,gb,ex);
    printf(" %8.2lf ms per iteration\n",elapsed);
    mirkill(w);
    mirkill(e);
    mirkill(g);
    return elapsed;
}

int main()
{
    int i,j,k,m;
    big a,b,x,y,p,A2;
    epoint *g;
    double tr1,tr2,ts,tv1,tv2,tp,td;
    miracl *mip=mirsys(300,0);
    p=mirvar(0);
    a=mirvar(-3);
    b=mirvar(0);
    x=mirvar(1);
    y=mirvar(0);
    A2=mirvar(0);
    mip->IOBASE=60;

    irand((long)clock());

    printf("MIRACL - %d bit version\n",MIRACL);
#ifdef MR_LITTLE_ENDIAN
    printf("Little Endian processor\n");
#endif
#ifdef MR_BIG_ENDIAN
    printf("Big Endian processor\n");
#endif
#ifdef MR_NOASM
    printf("C-Only Version of MIRACL\n");
#else
    printf("Using some assembly language\n");
#endif
#ifdef MR_STRIPPED_DOWN
    printf("Stripped down version of MIRACL - no error messages\n");
#endif
#ifdef MR_KCM
    k=MR_KCM*MIRACL;
    printf("Using KCM method \n");
    printf("Optimized for %d, %d, %d, %d...etc. bit moduli\n",k,k*2,k*4,k*8);
#endif
#ifdef MR_COMBA
    k=MR_COMBA*MIRACL;
    printf("Using COMBA method \n");
    printf("Optimized for %d bit moduli\n",k);
#endif
#ifdef MR_PENTIUM
    printf("Floating-point co-processor arithmetic used for Pentium\n");
#endif
#ifndef MR_KCM
#ifndef MR_COMBA
#ifndef MR_PENTIUM
    printf("No special optimizations\n");
#endif
#endif
#endif
printf("NOTE: No optimizations/assembly language apply to GF(2^m) Elliptic Curves\n");
#ifdef MR_NOFULLWIDTH
    printf("No Fullwidth base possible\n");
#endif

    printf("NOTE: times are elapsed real-times - so make sure nothing else is running!\n\n");
    printf("Modular exponentiation benchmarks - calculating g^e mod p\n");
    printf("From these figures it should be possible to roughly estimate the time\n");
    printf("required for your favourite PK algorithm, RSA, DSA, DH, etc.\n");
    printf("Key R - random base bits/random exponent bits \n");
    printf("    V - random base bits/(small exponent e)   \n");
    printf("    S - (small base g)  /random exponent bits \n");
    printf("    P - exponentiation with precomputation (fixed base g)\n");
    printf("    D - double exponentiation g^e.a^b mod p\n");
   
    printf("F3 = 257, F4 = 65537\n");
    printf("RSA - Rivest-Shamir-Adleman\n");
    printf("DH  - Diffie Hellman Key exchange\n");
    printf("DSA - Digital Signature Algorithm\n");

    printf("\n512 bit prime....\n");
    cinstr(p,p512);

    k=512;
    j=160;

    tr1=powers(k,j,p);
    td=powers_double(k,j,p);
    tr2=powers(k,k,p);
    ts=powers_small_base(3,j,p);
    tp=powers_precomp(k,j,p);

    printf("\n");
    printf("%4d bit RSA decryption               %8.2lf ms \n",2*k,2*tr2);
    printf("%4d bit DH %d bit exponent:-\n",k,j);
    printf("         offline, no precomputation   %8.2lf ms \n",tr1);
    printf("         offline, small base          %8.2lf ms \n",ts);
    printf("         offline, w. precomputation   %8.2lf ms \n",tp);
    printf("         online                       %8.2lf ms \n",tr1);                           
    printf("%4d bit DSA %d bit exponent:-\n",k,j);
    printf("         signature no precomputation  %8.2lf ms \n",tr1);
    printf("         signature w. precomputation  %8.2lf ms \n",tp);
    printf("         verification                 %8.2lf ms \n",td);
          
    printf("\n1024 bit prime....\n");
    cinstr(p,p1024);        

    k=1024; j=160;
    tr1=powers(k,j,p);
    td=powers_double(k,j,p);
    tr2=powers(k,k,p);
    tv1=powers_small_exp(k,3,p);
    tv2=powers_small_exp(k,65537L,p);
    ts=powers_small_base(3,j,p);
    tp=powers_precomp(k,j,p);

    printf("\n");
    printf("%4d bit RSA decryption               %8.2lf ms \n",2*k,2*tr2);
    printf("%4d bit RSA encryption e=3           %8.2lf ms \n",k,tv1);
    printf("%4d bit RSA encryption e=65537       %8.2lf ms \n",k,tv2);
    printf("%4d bit DH %d bit exponent:-\n",k,j);
    printf("         offline, no precomputation   %8.2lf ms \n",tr1);
    printf("         offline, small base          %8.2lf ms \n",ts);
    printf("         offline, w. precomputation   %8.2lf ms \n",tp);
    printf("         online                       %8.2lf ms \n",tr1);                           
    printf("%4d bit DSA %d bit exponent:-\n",k,j);
    printf("         signature no precomputation  %8.2lf ms \n",tr1);
    printf("         signature w. precomputation  %8.2lf ms \n",tp);
    printf("         verification                 %8.2lf ms \n",td);

    printf("\n2048 bit prime....\n");
    cinstr(p,p2048);

    k=2048; j=256;

    tr1=powers(k,j,p);
    td=powers_double(k,j,p);
    powers(k,k,p);
    tv1=powers_small_exp(k,3,p);
    tv2=powers_small_exp(k,65537L,p);
    ts=powers_small_base(3,j,p);
    tp=powers_precomp(k,j,p);

    printf("\n");
    printf("%4d bit RSA encryption e=3           %8.2lf ms \n",k,tv1);
    printf("%4d bit RSA encryption e=65537       %8.2lf ms \n",k,tv2);
    printf("%4d bit DH %d bit exponent:-\n",k,j);
    printf("         offline, no precomputation   %8.2lf ms \n",tr1);
    printf("         offline, small base          %8.2lf ms \n",ts);
    printf("         offline, w. precomputation   %8.2lf ms \n",tp);
    printf("         online                       %8.2lf ms \n",tr1);                           
    printf("%4d bit DSA %d bit exponent:-\n",k,j);
    printf("         signature no precomputation  %8.2lf ms \n",tr1);
    printf("         signature w. precomputation  %8.2lf ms \n",tp);
    printf("         verification                 %8.2lf ms \n",td);
  
    printf("\n");
    printf("Elliptic Curve point multiplication benchmarks - calculating r.P\n");
    printf("From these figures it should be possible to roughly estimate the time\n");
    printf("required for your favourite EC PK algorithm, ECDSA, ECDH, etc.\n");
    printf("Key - ER - Elliptic Curve point multiplication r.P\n");
    printf("      ED - Elliptic Curve double multiplication r.P + s.Q\n");
    printf("      EP - Elliptic Curve multiplication with precomputation\n");
    printf("EC    - Elliptic curve GF(p) - p of no special form \n");
    printf("ECDH  - Diffie Hellman Key exchange\n");
    printf("ECDSA - Digital Signature Algorithm\n");

    mip->IOBASE=10;

    printf("\n160 bit GF(p) Elliptic Curve....\n");
    k=160;
    cinstr(p,p160);
    cinstr(b,b160);
    cinstr(y,y160);

    ecurve_init(a,b,p,MR_PROJECTIVE);
    g=epoint_init();
    epoint_set(x,y,0,g);

    tr1=mults(k,g);
    td=mult_double(k,g);
    tp=mult_precomp(k,x,y,a,b,p);

    printf("\n");
    printf("%4d bit ECDH :-\n",k);
    printf("         offline, no precomputation   %8.2lf ms \n",tr1);
    printf("         offline, w. precomputation   %8.2lf ms \n",tp);
    printf("         online                       %8.2lf ms \n",tr1);                           
    printf("%4d bit ECDSA :-\n",k);
    printf("         signature no precomputation  %8.2lf ms \n",tr1);
    printf("         signature w. precomputation  %8.2lf ms \n",tp);
    printf("         verification                 %8.2lf ms \n",td);

    printf("\n192 bit GF(p) Elliptic Curve....\n");
    k=192;
    cinstr(p,p192);
    cinstr(b,b192);
    cinstr(y,y192);

    ecurve_init(a,b,p,MR_PROJECTIVE);
    g=epoint_init();
    epoint_set(x,y,0,g);

    tr1=mults(k,g);
    td=mult_double(k,g);
    tp=mult_precomp(k,x,y,a,b,p);

    printf("\n");
    printf("%4d bit ECDH :-\n",k);
    printf("         offline, no precomputation   %8.2lf ms \n",tr1);
    printf("         offline, w. precomputation   %8.2lf ms \n",tp);
    printf("         online                       %8.2lf ms \n",tr1);                           
    printf("%4d bit ECDSA :-\n",k);
    printf("         signature no precomputation  %8.2lf ms \n",tr1);
    printf("         signature w. precomputation  %8.2lf ms \n",tp);
    printf("         verification                 %8.2lf ms \n",td);

    printf("\n224 bit GF(p) Elliptic Curve....\n");
    k=224;
    cinstr(p,p224);
    cinstr(b,b224);
    cinstr(y,y224);

    ecurve_init(a,b,p,MR_PROJECTIVE);
    g=epoint_init();
    epoint_set(x,y,0,g);

    tr1=mults(k,g);
    td=mult_double(k,g);
    tp=mult_precomp(k,x,y,a,b,p);

    printf("\n");
    printf("%4d bit ECDH :-\n",k);
    printf("         offline, no precomputation   %8.2lf ms \n",tr1);
    printf("         offline, w. precomputation   %8.2lf ms \n",tp);
    printf("         online                       %8.2lf ms \n",tr1);                           
    printf("%4d bit ECDSA :-\n",k);
    printf("         signature no precomputation  %8.2lf ms \n",tr1);
    printf("         signature w. precomputation  %8.2lf ms \n",tp);
    printf("         verification                 %8.2lf ms \n",td);

    printf("\n256 bit GF(p) Elliptic Curve....\n");
    k=256;
    cinstr(p,p256);
    cinstr(b,b256);
    cinstr(y,y256);

    ecurve_init(a,b,p,MR_PROJECTIVE);
    g=epoint_init();
    epoint_set(x,y,0,g);

    tr1=mults(k,g);
    td=mult_double(k,g);
    tp=mult_precomp(k,x,y,a,b,p);

    printf("\n");
    printf("%4d bit ECDH :-\n",k);
    printf("         offline, no precomputation   %8.2lf ms \n",tr1);
    printf("         offline, w. precomputation   %8.2lf ms \n",tp);
    printf("         online                       %8.2lf ms \n",tr1);                           
    printf("%4d bit ECDSA :-\n",k);
    printf("         signature no precomputation  %8.2lf ms \n",tr1);
    printf("         signature w. precomputation  %8.2lf ms \n",tp);
    printf("         verification                 %8.2lf ms \n",td);

    printf("\n163 bit GF(2^m) Elliptic Curve....\n");
    k=163;
    mip->IOBASE=16;
    cinstr(b,B163);
    cinstr(x,x163);
    cinstr(y,y163);
    mip->IOBASE=10;
    convert(A163,A2);
    ecurve2_init(m163,a163,b163,c163,A2,b,FALSE,MR_PROJECTIVE);
    g=epoint2_init();
    epoint2_set(x,y,0,g);

    tr1=mults2(k,g);
    td=mult2_double(k,g);
    tp=mult2_precomp(k,x,y,A2,b,m163,a163,b163,c163);

    printf("\n");
    printf("%4d bit ECDH :-\n",k);
    printf("         offline, no precomputation   %8.2lf ms \n",tr1);
    printf("         offline, w. precomputation   %8.2lf ms \n",tp);
    printf("         online                       %8.2lf ms \n",tr1);                           
    printf("%4d bit ECDSA :-\n",k);
    printf("         signature no precomputation  %8.2lf ms \n",tr1);
    printf("         signature w. precomputation  %8.2lf ms \n",tp);
    printf("         verification                 %8.2lf ms \n",td);

    printf("\n233 bit GF(2^m) Elliptic Curve....\n");
    k=233;
    mip->IOBASE=16;
    cinstr(b,B233);
    cinstr(x,x233);
    cinstr(y,y233);
    mip->IOBASE=10;
    convert(A233,A2);
    ecurve2_init(m233,a233,b233,c233,A2,b,FALSE,MR_PROJECTIVE);
    g=epoint2_init();
    epoint2_set(x,y,0,g);

    tr1=mults2(k,g);
    td=mult2_double(k,g);
    tp=mult2_precomp(k,x,y,A2,b,m233,a233,b233,c233);

    printf("\n");
    printf("%4d bit ECDH :-\n",k);
    printf("         offline, no precomputation   %8.2lf ms \n",tr1);
    printf("         offline, w. precomputation   %8.2lf ms \n",tp);
    printf("         online                       %8.2lf ms \n",tr1);                           
    printf("%4d bit ECDSA :-\n",k);
    printf("         signature no precomputation  %8.2lf ms \n",tr1);
    printf("         signature w. precomputation  %8.2lf ms \n",tp);
    printf("         verification                 %8.2lf ms \n",td);

    printf("\n283 bit GF(2^m) Elliptic Curve....\n");
    k=283;
    mip->IOBASE=16;
    cinstr(b,B283);
    cinstr(x,x283);
    cinstr(y,y283);
    mip->IOBASE=10;

    convert(A283,A2);
    ecurve2_init(m283,a283,b283,c283,A2,b,FALSE,MR_PROJECTIVE);
    g=epoint2_init();
    epoint2_set(x,y,0,g);

    tr1=mults2(k,g);
    td=mult2_double(k,g);
    tp=mult2_precomp(k,x,y,A2,b,m283,a283,b283,c283);

    printf("\n");
    printf("%4d bit ECDH :-\n",k);
    printf("         offline, no precomputation   %8.2lf ms \n",tr1);
    printf("         offline, w. precomputation   %8.2lf ms \n",tp);
    printf("         online                       %8.2lf ms \n",tr1);                           
    printf("%4d bit ECDSA :-\n",k);
    printf("         signature no precomputation  %8.2lf ms \n",tr1);
    printf("         signature w. precomputation  %8.2lf ms \n",tp);
    printf("         verification                 %8.2lf ms \n",td);

    return 0;
}

