/*
 *    MIRACL  C++ Header file big.h
 *
 *    AUTHOR  :    N.Coghlan
 *                 Modified by M.Scott
 *             
 *    PURPOSE :    Definition of class Big
 *
 *   NOTE:- I/O conversion
 *
 *   To convert a hex character string to a Big
 *
 *         Big x;
 *         char c[100];
 *
 *         mip->IOBASE=16;
 *         x=c;
 *
 *   To convert a Big to a hex character string
 * 
 *         mip->IOBASE=16;
 *         c << x;
 *
 *   To convert to/from pure binary, see the from_binary()
 *   and to_binary() friend functions.
 *
 *   int len;
 *   char c[100];
 *   ...
 *   Big x=from_binary(len,c);  // creates Big x from len bytes of binary in c 
 *
 *   len=to_binary(x,100,c);    // converts Big x to len bytes binary in c[100] 
 *                              
 *   Copyright (c) 1988-2000 Shamus Software Ltd.
 */

#ifndef BIG_H
#define BIG_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif


extern "C"                    
{
    #include <miracl.h>
}

#ifndef MIRACL_CLASS
#define MIRACL_CLASS

class Miracl
{ /* dummy class to initialise MIRACL - MUST be called before any Bigs    *
   * are created. This could be a problem for static/global data declared *
   * in modules other than the main module */
    miracl *mr;
public:
    Miracl(int nd,mr_small nb=0)
                                 {mr=mirsys(nd,nb);mr->RPOINT=TRUE;}
    miracl *operator&() {return mr;}
    ~Miracl()                    {mirexit();}
};

#endif

class Big 
{ 
    big fn;
public:
    Big()        {fn = mirvar(0); } 
    Big(int i)   {fn = mirvar(i); }
    Big(long lg) {fn = mirvar(0); lgconv(lg,fn);}
    Big(char* s) {fn = mirvar(0); cinstr(fn,s);}
    Big(big& b)  {fn = mirvar(0); copy(b,fn);}
    Big(const Big& b)  {fn = mirvar(0); copy(b.fn,fn);}

    Big& operator=(int i)  {convert(i,fn); return *this;}
    Big& operator=(long lg){lgconv(lg,fn); return *this;}
    Big& operator=(const Big& b) {copy(b.fn,fn); return *this;}
    Big& operator=(char* s){cinstr(fn,s);return *this;}


    Big& operator++()      {incr(fn,1,fn); return *this;}
    Big& operator--()      {decr(fn,1,fn); return *this;}
    Big& operator+=(int i) {incr(fn,i,fn); return *this;}
    Big& operator+=(const Big& b){add_r(fn,b.fn,fn); return *this;}

    Big& operator-=(int i)  {decr(fn,i,fn); return *this;}
    Big& operator-=(const Big& b) {subtract(fn,b.fn,fn); return *this;}

    Big& operator*=(int i)  {premult(fn,i,fn); return *this;}
    Big& operator*=(const Big& b) {multiply(fn,b.fn,fn); return *this;}

    Big& operator/=(int i)  {subdiv(fn,i,fn);    return *this;}
    Big& operator/=(const Big& b) {divide(fn,b.fn,fn); return *this;}

    Big& operator%=(int i)  {convert(subdiv(fn,i,fn),fn); return *this;}
    Big& operator%=(const Big& b) {divide(fn,b.fn,b.fn); return *this;}

    Big& operator<<=(int i) {sftbit(fn,i,fn); return *this;}
    Big& operator>>=(int i) {sftbit(fn,-i,fn); return *this;}

    mr_small& operator[](int i) {return fn[i];}

    BOOL iszero() const;
    int get(int index)          { int m; m=getdig(fn,index); return m; }
    void set(int index,int n)   { putdig(n,fn,index);}
    int len()                   { return numdig(fn); }
    big getbig() const;

    friend class Flash;

    friend Big operator-(const Big&);

    friend Big operator+(const Big&,int);
    friend Big operator+(int,const Big&);
    friend Big operator+(const Big&,const Big&);

    friend Big operator-(const Big&, int);
    friend Big operator-(int,const Big&);
    friend Big operator-(const Big&,const Big&);

    friend Big operator*(const Big&, int);
    friend Big operator*(int,const Big&);
    friend Big operator*(const Big&,const Big&);

    friend Big operator/(const Big&,int);
    friend Big operator/(const Big&,const Big&);

    friend int operator%(const Big&, int);
    friend Big operator%(const Big&, const Big&);

    friend Big operator<<(const Big&, int);
    friend Big operator>>(const Big&, int);

    friend BOOL operator<=(const Big& b1,const Big& b2)
             {if (compare(b1.fn,b2.fn)<=0) return TRUE; else return FALSE;}
    friend BOOL operator>=(const Big& b1,const Big& b2)
             {if (compare(b1.fn,b2.fn)>=0) return TRUE; else return FALSE;}
    friend BOOL operator==(const Big& b1,const Big& b2)
             {if (compare(b1.fn,b2.fn)==0) return TRUE; else return FALSE;}
    friend BOOL operator!=(const Big& b1,const Big& b2)
             {if (compare(b1.fn,b2.fn)!=0) return TRUE; else return FALSE;}
    friend BOOL operator<(const Big& b1,const Big& b2)
              {if (compare(b1.fn,b2.fn)<0) return TRUE; else return FALSE;}
    friend BOOL operator>(const Big& b1,const Big& b2)
              {if (compare(b1.fn,b2.fn)>0) return TRUE; else return FALSE;}

    friend Big from_binary(int,char *);
    friend int to_binary(const Big&,int,char *);
    friend Big modmult(const Big&,const Big&,const Big&);
    friend Big norm(const Big&);
    friend Big sqrt(const Big&);
    friend Big root(const Big&,int);
    friend Big gcd(const Big&,const Big&);

    friend Big pow(const Big&,int);               // x^m
    friend Big pow(const Big&, int, const Big&);  // x^m mod n
    friend Big pow(int, const Big&, const Big&);  // x^m mod n
    friend Big pow(const Big&, const Big&, const Big&);  // x^m mod n
    friend Big pow(const Big&, const Big&, const Big&, const Big&, const Big&);
                                                         // x^m.y^k mod n 
    friend Big pow(int,Big *,Big *,Big);  // x[0]^m[0].x[1].m[1]... mod n

    friend Big luc(const Big& ,const Big&, const Big&, Big *b4=NULL);
    friend Big inverse(const Big&, const Big&);
    friend Big rand(const Big&);     // 0 < rand < parameter
    friend Big rand(int,int);        // (digits,base) e.g. (1024,2)
    friend Big abs(const Big&);
    friend int bit(const Big& b,int i)  {return mr_testbit(b.fn,i);}
    friend int bits(const Big& b) {return logb2(b.fn);}
    friend int jacobi(const Big& b1,const Big& b2) {return jack(b1.fn,b2.fn);}
    friend int toint(const Big& b)  {return size(b.fn);} 
    friend BOOL prime(const Big& b) {return isprime(b.fn);}  
    friend Big nextprime(const Big&);
    friend Big nextsafeprime(int type,int subset,const Big&);
    friend Big trial_divide(const Big& b);
    friend Big sqrt(const Big&,const Big&);

    friend void ecurve(const Big&,const Big&,const Big&,int);
    friend BOOL ecurve2(int,int,int,int,const Big&,const Big&,BOOL,int); 
    friend void modulo(const Big&);
    friend BOOL modulo(int,int,int,int,BOOL);
    friend Big get_modulus();

/* Montgomery stuff */

    friend Big nres(const Big&);
    friend Big redc(const Big&);
    friend Big nres_negate(const Big&);
    friend Big nres_modmult(const Big&,const Big&);
    friend Big nres_premult(const Big&,int);
    friend Big nres_pow(const Big&,const Big&);
    friend Big nres_pow2(const Big&,const Big&,const Big&,const Big&);
    friend Big nres_pown(int,Big *,Big *);
    friend Big nres_luc(const Big&,const Big&,Big *b3=NULL);
    friend Big nres_sqrt(const Big&);
    friend Big nres_modadd(const Big&,const Big&);
    friend Big nres_modsub(const Big&,const Big&);
    friend Big nres_moddiv(const Big&,const Big&);

/* GF(2) stuff */

    friend Big reduce2(const Big&);
    friend Big add2(const Big&,const Big&);
    friend Big incr2(const Big&,int);
    friend Big div2(const Big&,const Big&);
    friend Big mul2(const Big&,const Big&);
    friend Big pow2(const Big&,int);
    friend Big sqrt2(const Big&);

/* Note that when inputting text as a number the CR is NOT   *
 * included in the text, unlike C I/O which does include CR. */

    friend istream& operator>>(istream&, Big&);

    friend ostream& operator<<(ostream&, const Big&);

// output Big to a String
    friend char * operator<<(char * s,const Big&);

    ~Big() { mirkill(fn); }
};


#endif

