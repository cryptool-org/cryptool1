/*
 *    MIRACL  C++ Header file crt.h
 *
 *    AUTHOR  : M. Scott
 *  
 *    PURPOSE : Definition of class Crt  (Chinese Remainder Thereom)
 *    NOTE    : Must be used in conjunction with big.cpp
 *              Can be used with either Big or utype moduli
 *                
 *    Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#ifndef CRT_H
#define CRT_H

#include <big.h>

#define BIGS   0
#define SMALLS 1

class Crt 
{ 
    big_chinese bc;
    small_chinese sc;
    int type;
public:
    Crt(int,Big *);
    Crt(int,mr_utype *);

    Big eval(Big *);       
    Big eval(mr_utype *);

    ~Crt() 
    {  /* destructor */
        if (type==BIGS) crt_end(&bc);
        if (type==SMALLS) scrt_end(&sc);
    }
};

#endif

