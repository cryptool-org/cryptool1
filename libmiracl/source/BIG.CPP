/*
 *    MIRACL  C++ functions big.cpp
 *
 *    AUTHOR  :    N.Coghlan
 *                 Modified by M.Scott
 *             
 *    PURPOSE :    Implementation of class Big functions
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif

#include <big.h>

big Big::getbig() const         
         { return fn;}
BOOL Big::iszero() const
         { if (size(fn)==0) return TRUE; return FALSE;}
Big operator-(const Big& b)
{Big nb; negate(b.fn,nb.fn); return nb;}
Big operator+(const Big& b,int i)
{Big abi; incr(b.fn, i, abi.fn); return abi;}
Big operator+(int i,const Big& b)
{Big aib; incr(b.fn, i, aib.fn); return aib;}
Big operator+(const Big& b1, const Big& b2)
{Big abb;add_r(b1.fn,b2.fn,abb.fn);return abb;}

Big operator-(const Big& b, int i)
{Big mbi; decr(b.fn, i, mbi.fn); return mbi;}
Big operator-(int i, const Big& b)
{Big mib;decr(b.fn, i, mib.fn);negate(mib.fn,mib.fn);return mib;}
Big operator-(const Big& b1, const Big& b2)
{Big mbb; subtract(b1.fn,b2.fn,mbb.fn); return mbb;}

Big operator*(const Big& b, int i)
{Big xbi; premult(b.fn, i, xbi.fn); return xbi;}
Big operator*(int i, const Big& b)
{Big xib; premult(b.fn, i, xib.fn); return xib;}
Big operator*(const Big& b1, const Big& b2)
{Big xbb; multiply(b1.fn,b2.fn,xbb.fn); return xbb;}

Big operator/(const Big& b, int i)
{Big dbi; subdiv(b.fn, i, dbi.fn); return dbi;}
Big operator/(const Big& b1, const Big& b2)
{Big dbb; copy(b1.fn,dbb.fn); divide(dbb.fn,b2.fn,dbb.fn); return dbb;}

int operator%(const Big& b, int i)
{Big mdbi; return(subdiv(b.fn,i, mdbi.fn));}
Big operator%(const Big& b1, const Big& b2)
{Big mdbb;copy(b1.fn,mdbb.fn);divide(mdbb.fn,b2.fn,b2.fn);return mdbb;}

Big operator<<(const Big& b, int i)
{Big ms; sftbit(b.fn,i,ms.fn); return ms;}

Big operator>>(const Big& b, int i)
{Big ms; sftbit(b.fn,-i,ms.fn); return ms;}


Big from_binary(int len,char *ptr)
{Big z; bytes_to_big(len,ptr,z.fn); return z;}
int to_binary(const Big& b,int max,char *ptr)
{ return big_to_bytes(max,b.fn,ptr);}

Big modmult(const Big& b1,const Big& b2,const Big& m)
{Big z; mad(b1.fn,b2.fn,b2.fn,m.fn,m.fn,z.fn); return z;}
Big norm(const Big& b) {Big z; normalise(b.fn,z.fn); return z;}
Big sqrt(const Big& b) {Big z; nroot(b.fn, 2, z.fn); return z;}
Big abs(const Big& b) {Big z; absol(b.fn,z.fn); return z;}
Big root(const Big &b,int n) {Big z; nroot(b.fn, n, z.fn); return z;}
Big gcd(const Big& b1, const Big& b2){Big z;egcd(b1.fn,b2.fn,z.fn);return z;}
Big pow(const Big& b,int n)
{Big z;int x; if ((x=size(b.fn))<MR_TOOBIG) expint(x,n,z.fn);
              else power(b.fn,n,z.fn,z.fn);return z;}
Big pow(const Big& b1,int n, const Big& b3)
{Big z; power(b1.fn,n,b3.fn,z.fn); return z;}
Big pow(int x, const Big& b2, const Big& b3)
{Big z; powltr(x,b2.fn,b3.fn,z.fn); return z;}
Big pow(const Big& b1, const Big& b2, const Big& b3)
{Big z; powmod(b1.fn,b2.fn,b3.fn,z.fn); return z;}
Big pow(const Big& b1,const Big& b2,const Big& b3,const Big& b4,const Big& b5)
{Big z; powmod2(b1.fn,b2.fn,b3.fn,b4.fn,b5.fn,z.fn); return z;}


Big pow(int n,Big *a,Big *b,Big p)
{
    Big z;
    int i;
    big *x=(big *)mr_alloc(n,sizeof(big));
    big *y=(big *)mr_alloc(n,sizeof(big));
    for (i=0;i<n;i++)
    {
        x[i]=a[i].fn;
        y[i]=b[i].fn;
    }
    powmodn(n,x,y,p.fn,z.fn);
    mr_free(y);  mr_free(x);
    return z;
}


Big luc(const Big& b1,const Big& b2,const Big& b3,Big *b4)
{Big z; if (b4!=NULL) lucas(b1.fn,b2.fn,b3.fn,b4->fn,z.fn); 
        else          lucas(b1.fn,b2.fn,b3.fn,z.fn,z.fn);
return z;}


Big inverse(const Big& b1, const Big& b2)
{Big z; xgcd(b1.fn,b2.fn,z.fn,z.fn,z.fn);return z;}
Big rand(const Big& b) {Big z; bigrand(b.fn,z.fn); return z;}
Big rand(int n,int b) {Big z; bigdig(n,b,z.fn);  return z;}
Big nextprime(const Big& b) {Big z; nxprime(b.fn,z.fn); return z;}
Big nextsafeprime(int type,int subset,const Big& b) {Big z; 
nxsafeprime(type,subset,b.fn,z.fn); return z; }
Big trial_divide(const Big& b) {Big r; trial_division(b.fn,r.fn); return r;}

Big sqrt(const Big& x,const Big& p) {Big z; sqroot(x.fn,p.fn,z.fn); return z;}

void modulo(const Big& n) {prepare_monty(n.fn);}
Big get_modulus()      
{Big m; 
miracl *mip=get_mip();
copy(mip->modulus,m.fn); 
return m;}
Big nres(const Big& b) {Big z; nres(b.fn,z.fn); return z;}
Big redc(const Big& b) {Big z;  redc(b.fn,z.fn);return z;}
Big nres_negate(const Big& b)
{ Big z; nres_negate(b.fn,z.fn); return z;}
Big nres_modmult(const Big& b1,const Big& b2)
{ Big z; nres_modmult(b1.fn,b2.fn,z.fn); return z;}
Big nres_premult(const Big& b1,int i)
{ Big z; nres_premult(b1.fn,i,z.fn); return z;}

Big nres_modadd(const Big& b1,const Big& b2)
{ Big z; nres_modadd(b1.fn,b2.fn,z.fn); return z;}
Big nres_modsub(const Big& b1,const Big& b2)
{ Big z; nres_modsub(b1.fn,b2.fn,z.fn); return z;}
Big nres_moddiv(const Big& b1,const Big& b2)
{ Big z; nres_moddiv(b1.fn,b2.fn,z.fn); return z;}
Big nres_pow(const Big& b1,const Big& b2)
{ Big z; nres_powmod(b1.fn,b2.fn,z.fn); return z;}
Big nres_pow2(const Big& b1,const Big& b2,const Big& b3,const Big& b4)
{ Big z; nres_powmod2(b1.fn,b2.fn,b3.fn,b4.fn,z.fn); return z;}


Big nres_pown(int n,Big *a,Big *b)
{
    Big z;
    int i;
    big *x=(big *)mr_alloc(n,sizeof(big));
    big *y=(big *)mr_alloc(n,sizeof(big));
    for (i=0;i<n;i++)
    {
        x[i]=a[i].fn;
        y[i]=b[i].fn;
    }
    nres_powmodn(n,x,y,z.fn);
    mr_free(y);  mr_free(x);
    return z;
}

Big nres_luc(const Big& b1,const Big& b2,Big *b3)
{ Big z; if (b3!=NULL) nres_lucas(b1.fn,b2.fn,b3->fn,z.fn); 
         else          nres_lucas(b1.fn,b2.fn,z.fn,z.fn);
  return z;}
Big nres_sqrt(const Big& b)
{ Big z; nres_sqroot(b.fn,z.fn); return z;}

/* Note that when inputting text as a number the CR is NOT   *
 * included in the text, unlike C I/O which does include CR. */

istream& operator>>(istream& s, Big& x)
{ 
  miracl *mip=get_mip();
  if (mip->IOBASE>60) 
  {
     s.sync(); 
     s.getline(mip->IOBUFF,mip->IOBSIZ);
  }
  else s >> mip->IOBUFF;
  if (s.eof() || s.bad()) 
  {   
      zero(x.fn); 
      return s; 
  }
  cinstr(x.fn,mip->IOBUFF); 
  return s;
}

ostream& operator<<(ostream& s, const Big& x)
{
    miracl *mip=get_mip();
    cotstr(x.fn,mip->IOBUFF); 
    s << mip->IOBUFF; 
    return s;
}

char* operator<<(char *s,const Big& x)
{
    miracl *mip=get_mip();
    int i,n=cotstr(x.fn,mip->IOBUFF);
    if (s!=mip->IOBUFF) for (i=0;i<=n;i++) s[i]=mip->IOBUFF[i];
    return s;
}

