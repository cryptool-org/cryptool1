/*
 *   Program to calculate roots
 *
 *   Requires: flash.cpp
 * 
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <iostream.h>
#include <flash.h>

Miracl precision=50;

int main()
{ /* Find roots */
    Flash x,y;
    int n;
    miracl *mip=&precision;  
    mip->RPOINT=ON;
    cout << "enter number\n";
    cin >> x;
    cout << "to the power of 1/2\n";
    y=sqrt(x);
    cout << y;
    x=y*y;
    cout << "\nto the power of 2 = \n";
    cout << x;
    if (mip->EXACT) cout << "\nResult is exact!\n";
    return 0;
}

