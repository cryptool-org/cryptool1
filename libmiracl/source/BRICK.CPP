/*
 *   Test program to implement Brickell et al's method for fast
 *   computation of g^x mod n, for fixed g and n, using precomputation. 
 *   This idea can be used to substantially speed up certain phases 
 *   of the Digital Signature Standard (DSS).
 *
 *   See "Fast Exponentiation with Precomputation"
 *   by E. Brickell et al. in Proceedings Eurocrypt 1992
 *
 *   Requires: big.cpp
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <iostream.h>
#include <fstream.h>
#include <brick.h>   /* include MIRACL system */

Miracl precision=100;

int main()
{
    ifstream common("common.dss");
    Big a,e,n,g;
    int i,d,ndig,nb,best,time,store,base,bits;
    miracl *mip=&precision;
    common >> bits;
    mip->IOBASE=16;
    common >> n >> g >> g;
    mip->IOBASE=10;
    
    cout << "Enter size of exponent in bits = ";
    cin >> nb;

    Brick b(g,n,nb); 

    e=rand(nb,2); /* random exponent */

    cout << "naive method" << endl;
    a=pow(g,e,n);
    cout << a << endl;

    cout << "Brickell et al. method" << endl;

    a=b.pow(e);

    cout << a << endl;
    return 0;
}

