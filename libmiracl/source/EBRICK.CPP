/*
 *   Test program to implement Brickell et al's method for fast
 *   computation of g^x mod n, for fixed g and n, using precomputation. 
 *   This idea can be used to substantially speed up certain phases 
 *   of the Digital Signature Standard (DSS).
 *
 *   See "Fast Exponentiation with Precomputation"
 *   by E. Brickell et al. in Proceedings Eurocrypt 1992
 *
 *   Requires: big.cpp elliptic.cpp
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <iostream.h>
#include <fstream.h>
#include <elliptic.h>
#include <ebrick.h>   /* include MIRACL system */

Miracl precision=50;

int main()
{
    ifstream common("common.ecs");
    Big a,b,x,y,e,n,r;
    int bits,i,nb;
    miracl *mip=&precision;
    common >> bits; 
    mip->IOBASE=16;
    common >> n >> a >> b >> r >> x >> y;
    mip->IOBASE=10;

    cout << "Enter size of exponent in bits = ";
    cin >> nb;

    EBrick B(x,y,a,b,n,nb); 

    e=rand(nb,2); /* random exponent */

    cout << "naive method" << endl;
    ecurve(a,b,n,MR_PROJECTIVE);
    ECn G(x,y);
    G*=e;
    G.get(x,y);
    cout << x << endl;

    x=0;
    cout << "Brickell et al. method" << endl;

    B.mul(e,x,y);

    cout << x << endl;
    return 0;
}

