/*
 *    MIRACL C++ Header file gf2m.h
 *
 *    AUTHOR  : M.Scott
 *    
 *    PURPOSE : Definition of class GF2m (Arithmetic in the field GF(2^m)
 *
 *    NOTE:   : The field basis is set dynamically via the modulo() routine.
 *              Must be used with big.h and big.cpp
 *
 *    Copyright (c) 2000 Shamus Software Ltd.
 */

#ifndef GF2M_H
#define GF2M_H

#include <big.h>

class GF2m
{
    Big fn;
public:
    GF2m()   { }
    GF2m(int i)        {if (i==0) fn=0; else fn=reduce2((Big)i);}
    GF2m(long lg)      {if (lg==0L) fn=0; else fn=reduce2((Big)lg);}
    GF2m(const Big& b) {fn=reduce2(b); }   /* Big -> GF2m */
    GF2m(big& b)       {copy(b,fn.getbig());}
    GF2m(const GF2m& b) {fn=b.fn;}
    GF2m(char *s)      {fn=reduce2((Big)s);}
   
    GF2m& operator=(int i)   {if (i==0) fn=0; else fn=reduce2((Big)i); return *this; }
    GF2m& operator=(long lg) 
                    {if (lg==0L) fn=0; else fn=reduce2((Big)lg); return *this;}

    GF2m& operator=(const GF2m b) {fn=b.fn; return *this;}
    GF2m& operator=(char *s)      {fn=reduce2((Big)s); return *this;}

    GF2m& operator++() {fn=incr2(fn,1); return *this; }
    GF2m& operator+=(int i) {fn=add2(fn,i); return *this; }
    GF2m& operator+=(const GF2m& b) {fn=add2(fn,b.fn); return *this;}
    GF2m& operator*=(const GF2m& b) {fn=mul2(fn,b.fn); return *this;}

    BOOL iszero() const;
    operator Big() {return fn;}   /* GF2m -> Big */
    friend big getbig(GF2m& z) {return z.fn.getbig();}
    friend int trace(GF2m & z) {return trace2(z.fn.getbig());}


    GF2m& operator/=(const GF2m& b) {fn=div2(fn,b.fn); return *this;}
    
    friend GF2m operator+(const GF2m&,const GF2m&);
    friend GF2m operator*(const GF2m&,const GF2m&);
    friend GF2m operator/(const GF2m&,const GF2m&);
    
    friend BOOL operator==(const GF2m& b1,const GF2m& b2)
    { if (b1.fn==b2.fn) return TRUE; else return FALSE;}
    friend BOOL operator!=(const GF2m& b1,const GF2m& b2)
    { if (b1.fn!=b2.fn) return TRUE; else return FALSE;}
     
    friend GF2m pow(const GF2m&,int);
    friend GF2m sqrt(const GF2m&);
        
    ~GF2m() { }
};


#endif  

