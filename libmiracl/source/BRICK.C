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
    big e,n,g,a;
    brick binst;
    int i,d,ndig,nb,best,time,store,base,bits;
    miracl *mip=mirsys(100,0);
    n=mirvar(0);
    e=mirvar(0);
    a=mirvar(0);
    g=mirvar(0);
    fp=fopen("common.dss","r");
    fscanf(fp,"%d\n",&bits);
    mip->IOBASE=16;
    cinnum(n,fp);
    cinnum(g,fp);
    cinnum(g,fp);  
    mip->IOBASE=10;  

    printf("modulus is %d bits in length\n",logb2(n));
    printf("Enter size of exponent in bits = ");
    scanf("%d",&nb);
    getchar();

    brick_init(&binst,g,n,nb);

    printf("%d big numbers have been precomputed and stored\n",binst.store);
    printf("Using base %d\n",binst.base);

    bigdig(nb,2,e);  /* random exponent */  

    printf("naive method\n");
    powmod(g,e,n,a);
    cotnum(a,stdout);

    printf("Brickel et al method\n");
    pow_brick(&binst,e,a);

    brick_end(&binst);
    
    cotnum(a,stdout);

    return 0;
}


