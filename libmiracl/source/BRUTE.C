/*
 *   Program to factor numbers using brute force.
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>
#define LIMIT 15000

int main()
{ /* find factors by brute force division */
    big x,y;
    int n,p;
    miracl *mip=mirsys(50,0);
    x=mirvar(0);
    y=mirvar(0);
    gprime(LIMIT);
    printf("input number to be factored\n");
    cinnum(x,stdin);
    if (isprime(x))
    {
        printf("this number is prime!\n");
        return 0;
    }
    n=0;
    p=mip->PRIMES[0];
    printf("factors are \n");
    forever
    { /* try division by each prime in turn */
        if (subdiv(x,p,y)==0)
        { /* factor found */
            copy(y,x);
            printf("prime factor     ");
            printf("%d\n",p);
            if (size(x)==1) return 0;
            continue;
        }
        if (size(y)<=p) 
        { /* must be prime */
            printf("prime factor     ");
            cotnum(x,stdout);
            return 0;
        }
        p=mip->PRIMES[++n];
        if (p==0) break;
    }
    if (isprime(x)) printf("prime factor     ");
    else            printf("composite factor ");
    cotnum(x,stdout);
    return 0;
}

