/*
 *    MIRACL C++ functions gf2m.cpp
 *
 *    AUTHOR  : M. Scott
 *    
 *    PURPOSE : Implementation of class GF2m
 *
 *    NOTE:   : Must be used in conjunction with big.h and big.cpp
 *
 *    Copyright (c) 2000 Shamus Software Ltd
 */

#include <iostream.h>
#include <gf2m.h>

BOOL GF2m::iszero() const
{ return fn.iszero(); }

BOOL modulo(int m,int a,int b,int c,BOOL check) {return prepare_basis(m,a,b,c,check);}

Big reduce2(const Big& b) {Big z; reduce2(b.fn,z.fn); return z;}

Big add2(const Big& b1,const Big& b2) 
{Big z; add2(b1.fn,b2.fn,z.fn); return z;}

Big incr2(const Big& b,int i)
{Big z; incr2(b.fn,i,z.fn); return z;}

Big mul2(const Big& b1,const Big& b2)
{Big z; modmult2(b1.fn,b2.fn,z.fn); return z;}

Big div2(const Big& b1,const Big& b2)
{Big z; inverse2(b2.fn,z.fn); modmult2(b1.fn,z.fn,z.fn); return z;}

Big sqrt2(const Big& b)
{Big z; sqroot2(b.fn,z.fn); return z;}

Big pow2(const Big& b,int m)
{Big z; power2(b.fn,m,z.fn); return z;}

GF2m operator+(const GF2m& b1,const GF2m& b2)
{GF2m abb; abb.fn=add2(b1.fn,b2.fn); return abb;}
GF2m operator*(const GF2m& b1,const GF2m& b2)
{GF2m abb; abb.fn=mul2(b1.fn,b2.fn); return abb;}
GF2m operator/(const GF2m& b1,const GF2m& b2)
{GF2m abb; abb.fn=div2(b1.fn,b2.fn); return abb;}

GF2m pow(const GF2m& b,int m)
{GF2m z; z.fn=pow2(b.fn,m); return z;}

GF2m sqrt(const GF2m& b)
{GF2m z; z.fn=sqrt2(b.fn); return z;}

