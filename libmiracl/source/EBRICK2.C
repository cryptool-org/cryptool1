/*
 *   Test program to implement Brickell et al's method for fast
 *   computation of g^x mod n, for fixed g and n, using precomputation. 
 *   This idea can be used to substantially speed up certain phases 
 *   of the Digital Signature Standard (DSS).
 *
 *   See "Fast Exponentiation with Precomputation"
 *   by E. Brickell et al. in Proceedings Eurocrypt 1992
 *
 *   Copyright (c) 2000 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

int main()
{
    FILE *fp;
    int m,a,b,c;
    big e,a2,a6,x,y,r;
    epoint *g;
    ebrick2 binst;
    int i,d,ndig,nb,best,time,store,base;
    miracl *mip=mirsys(50,0);
    e=mirvar(0);
    a2=mirvar(0);
    a6=mirvar(0);
    x=mirvar(0);
    y=mirvar(0);
    r=mirvar(0);

    fp=fopen("common2.ecs","r");
    fscanf(fp,"%d\n",&m);
    mip->IOBASE=16;
    cinnum(a2,fp);
    cinnum(a6,fp);
    cinnum(r,fp);
    cinnum(x,fp);
    cinnum(y,fp);
    mip->IOBASE=10;

    fscanf(fp,"%d\n",&a);
    fscanf(fp,"%d\n",&b);
    fscanf(fp,"%d\n",&c);
    
    printf("modulus is %d bits in length\n",m);
    printf("Enter size of exponent in bits = ");
    scanf("%d",&nb);
    getchar();

    ebrick2_init(&binst,x,y,a2,a6,m,a,b,c,nb);

    printf("%d big numbers have been precomputed and stored\n",binst.store);

    bigdig(nb,2,e);  /* random exponent */  

    printf("naive method\n");
    ecurve2_init(m,a,b,c,a2,a6,FALSE,MR_PROJECTIVE);
    g=epoint2_init();
    epoint2_set(x,y,0,g);
    ecurve2_mult(e,g,g);
    epoint2_get(g,x,y);
    cotnum(x,stdout);
    cotnum(y,stdout);

    zero(x); zero(y);
    printf("Brickel et al method\n");
    mul2_brick(&binst,e,x,y);

    ebrick2_end(&binst);
    
    cotnum(x,stdout);
    cotnum(y,stdout);

    return 0;
}


