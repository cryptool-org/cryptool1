/*
 *   Proposed Digital Signature Standard
 *
 *   Elliptic Curve Variation GF(p) - See Dr. Dobbs Journal April 1997
 *
 *   This program generates one set of public and private keys in files 
 *   public.ecs and private.ecs respectively. Notice that the public key 
 *   can be much shorter in this scheme, for the same security level.
 *
 *   It is assumed that Curve parameters are to be found in file common.ecs
 *
 *   The curve is y^2=x^3+Ax+b mod p
 *
 *   The file common.ecs is presumed to exist, and to contain the domain
 *   information {p,A,B,q,x,y}, where A and B are curve parameters, (x,y) are
 *   a point of order q, p is the prime modulus, and q is the order of the 
 *   point (x,y). In fact normally q is the prime number of points counted
 *   on the curve. 
 * 
 *   Copyright (c) 1997 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

int main()
{
    FILE *fp;
    int ep,bits;
    epoint *g;
    big a,b,p,q,x,y,d;
    long seed;
    miracl *mip;
    
    fp=fopen("common.ecs","r");
    if (fp==NULL)
    {
        printf("file common.ecs does not exist\n");
        return 0;
    }
    fscanf(fp,"%d\n",&bits); 

    mip=mirsys(3+bits/MIRACL,0);
    a=mirvar(0);
    b=mirvar(0);
    p=mirvar(0);
    q=mirvar(0);
    x=mirvar(0);
    y=mirvar(0);
    d=mirvar(0);

    mip->IOBASE=16;
    cinnum(p,fp);
    cinnum(a,fp);
    cinnum(b,fp);
    cinnum(q,fp);
    cinnum(x,fp);
    cinnum(y,fp);
    mip->IOBASE=10;
    fclose(fp);

/* randomise */
    printf("Enter 9 digit random number seed  = ");
    scanf("%ld",&seed);
    getchar();
    irand(seed);

    ecurve_init(a,b,p,MR_PROJECTIVE);  /* initialise curve */

    g=epoint_init();

    epoint_set(x,y,0,g); /* initialise point of order q */

/* generate public/private keys */

    bigrand(q,d);
    ecurve_mult(d,g,g);
    
    ep=epoint_get(g,x,x); /* compress point */

    printf("public key = %d ",ep);
    cotnum(x,stdout);

    fp=fopen("public.ecs","w");
    fprintf(fp,"%d ",ep);
    cotnum(x,fp);
    fclose(fp);

    fp=fopen("private.ecs","w");
    cotnum(d,fp);
    fclose(fp);
    return 0;
}

