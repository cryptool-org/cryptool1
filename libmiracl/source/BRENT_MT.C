/*
 *   Program to factor big numbers using Brent-Pollard method.
 *   See "An Improved Monte Carlo Factorization Algorithm"
 *   by Richard Brent in BIT Vol. 20 1980 pp 176-184
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

#define min(a,b) ((a) < (b)? (a) : (b))

int main()
{  /*  factoring program using Brents method */
    long k,r,i,m,iter;
    big x,y,z,n,q,ys,c3;
    miracl *mip=mirsys(50,0);
    x=mirvar(mip,0);
    y=mirvar(mip,0);
    ys=mirvar(mip,0);
    z=mirvar(mip,0);
    n=mirvar(mip,0);
    q=mirvar(mip,0);
    c3=mirvar(mip,3);
    printf("input number to be factored\n");
    cinnum(mip,n,stdin);
    if (isprime(mip,n))
    {
        printf("this number is prime!\n");
        return 0;
    }
    m=10L;
    r=1L;
    iter=0L;
    do
    {
        printf("iterations=%5ld",iter);
        convert(mip,1,q);
        do
        {
            copy(y,x);
            for (i=1L;i<=r;i++)
                mad(mip,y,y,c3,n,n,y);
            k=0;
            do
            {
                iter++;
                if (iter%10==0) printf("\b\b\b\b\b%5ld",iter);
                fflush(stdout);  
                copy(y,ys);
                for (i=1L;i<=min(m,r-k);i++)
                {
                    mad(mip,y,y,c3,n,n,y);
                    subtract(mip,y,x,z);
                    mad(mip,z,q,q,n,n,q);
                }
                egcd(mip,q,n,z);
                k+=m;
            } while (k<r && size(z)==1);
            r*=2;
        } while (size(z)==1);
        if (compare(z,n)==0) do 
        { /* back-track */
            mad(mip,ys,ys,c3,n,n,ys);
            subtract(mip,ys,x,z);
        } while (egcd(mip,z,n,z)==1);
        if (!isprime(mip,z))
             printf("\ncomposite factor ");
        else printf("\nprime factor     ");
        cotnum(mip,z,stdout);
        if (compare(z,n)==0) return 0;
        divide(mip,n,z,n);
        divide(mip,y,n,n);
    } while (!isprime(mip,n));
    printf("prime factor     ");
    cotnum(mip,n,stdout);
    return 0;
}

