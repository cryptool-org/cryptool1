/*
 *   Example program
 *
 *   Requires: flash.cpp 
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <iostream.h>
#include <flash.h>

Miracl precision=(-35);

int main()
{ /* Brents example program */
    Flash x;
    cout << pi() << endl;
    x=exp(pi()*sqrt((Flash)"163/9"));
    cout << x << endl;
    cout << pow(x,3) << endl;
    return 0;
}

