/*
 *   Test program to implement Brickell et al's method for fast
 *   computation of g^x mod n, for fixed g and n, using precomputation. 
 *   This idea can be used to substantially speed up certain phases 
 *   of the Digital Signature Standard (DSS).
 *
 *   See "Fast Exponentiation with Precomputation"
 *   by E. Brickell et al. in Proceedings Eurocrypt 1992
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

int main()
{
    FILE *fp;
    big e,n,a,b,x,y,r;
    epoint *g;
    ebrick binst;
    int i,d,ndig,nb,best,time,store,base,bits;
    miracl *mip=mirsys(50,0);
    n=mirvar(0);
    e=mirvar(0);
    a=mirvar(0);
    b=mirvar(0);
    x=mirvar(0);
    y=mirvar(0);
    r=mirvar(0);

    fp=fopen("common.ecs","r");
    fscanf(fp,"%d\n",&bits);

    mip->IOBASE=16;
    cinnum(n,fp);
    cinnum(a,fp);
    cinnum(b,fp);
    cinnum(r,fp);
    cinnum(x,fp);
    cinnum(y,fp);
    mip->IOBASE=10;

    printf("modulus is %d bits in length\n",logb2(n));
    printf("Enter size of exponent in bits = ");
    scanf("%d",&nb);
    getchar();

    ebrick_init(&binst,x,y,a,b,n,nb);

    printf("%d big numbers have been precomputed and stored\n",binst.store);

    bigdig(nb,2,e);  /* random exponent */  

    printf("naive method\n");
    ecurve_init(a,b,n,MR_PROJECTIVE);
    g=epoint_init();
    epoint_set(x,y,0,g);
    ecurve_mult(e,g,g);
    epoint_get(g,x,y);
    cotnum(x,stdout);
    cotnum(y,stdout);

    printf("Brickel et al method\n");
    mul_brick(&binst,e,x,y);

    ebrick_end(&binst);
    
    cotnum(x,stdout);
    cotnum(y,stdout);

    return 0;
}


