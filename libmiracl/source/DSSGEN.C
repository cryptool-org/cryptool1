/*
 *   Proposed Digital Signature Standard
 *
 *   See Communications ACM July 1992, Vol. 35 No. 7
 *   This new standard for digital signatures has been proposed by 
 *   the American National Institute of Standards and Technology (NIST)
 *   under advisement from the National Security Agency (NSA). 
 *
 *   This program generates one set of public and private keys in files 
 *   public.dss and private.dss respectively
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

int main()
{
    FILE *fp;
    big p,q,g,x,y;
    long seed;
    int bits;
    miracl *mip;
/* get common data */
    fp=fopen("common.dss","r");
    if (fp==NULL)
    {
        printf("file common.dss does not exist\n");
        return 0;
    }
    fscanf(fp,"%d\n",&bits);

    mip=mirsys(3+bits/MIRACL,0);
    p=mirvar(0);
    q=mirvar(0);
    g=mirvar(0);
    x=mirvar(0);
    y=mirvar(0);

    mip->IOBASE=16;
    cinnum(p,fp);
    cinnum(q,fp);
    cinnum(g,fp);
    mip->IOBASE=10;
    fclose(fp);

/* randomise */
    printf("Enter 9 digit random number seed  = ");
    scanf("%ld",&seed);
    getchar();
    irand(seed);

/* generate public/private keys */
    bigrand(q,x);
    powmod(g,x,p,y);
    printf("public key = ");
    cotnum(y,stdout);
    fp=fopen("public.dss","w");
    cotnum(y,fp);
    fclose(fp);
    fp=fopen("private.dss","w");
    cotnum(x,fp);
    fclose(fp);
    mirexit();
    return 0;
}

