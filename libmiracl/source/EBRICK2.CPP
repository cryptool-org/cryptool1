/*
 *   Test program to implement Brickell et al's method for fast
 *   computation of g^x mod 2^m, for fixed g and n, using precomputation. 
 *   This idea can be used to substantially speed up certain phases 
 *   of the Digital Signature Standard (DSS).
 *
 *   See "Fast Exponentiation with Precomputation"
 *   by E. Brickell et al. in Proceedings Eurocrypt 1992
 *
 *   Requires: big.cpp ec2.cpp
 *
 *   Copyright (c) 2000 Shamus Software Ltd.
 */

#include <iostream.h>
#include <fstream.h>
#include <ec2.h>
#include <ebrick2.h>   /* include MIRACL system */

Miracl precision=50;

int main()
{
    ifstream common("common2.ecs");
    int m,a,b,c;
    Big a2,a6,x,y,e,r;
    int i,nb;
    miracl *mip=&precision;

    common >> m;
    mip->IOBASE=16;
    common >> a2 >> a6 >> r >> x >> y;
    mip->IOBASE=10;
    common >> a >> b >> c;

    cout << "Enter size of exponent in bits = ";
    cin >> nb;

    EBrick2 B(x,y,a2,a6,m,a,b,c,nb); 

    e=rand(nb,2); /* random exponent */

    cout << "naive method" << endl;
    ecurve2(m,a,b,c,a2,a6,FALSE,MR_PROJECTIVE);
    EC2 G(x,y);
    G*=e;
    G.get(x,y);
    cout << x << endl;
    
    x=0;
    cout << "Brickell et al. method" << endl;

    B.mul(e,x,y);

    cout << x << endl;
    return 0;
}

