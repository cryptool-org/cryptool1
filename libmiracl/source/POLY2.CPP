/*
 * C++ class to implement a polynomial type and to allow 
 * arithmetic on polynomials whose elements are from
 * the finite field GF(2^m)
 *
 * WARNING: This class has been cobbled together for a specific use with
 * the MIRACL library. It is not complete, and may not work in other 
 * applications
 *
 * See Knuth The Art of Computer Programming Vol.2, Chapter 4.6 
 */

#include "poly2.h"

extern "C"
{
    extern miracl *mr_mip;
}

Poly2::Poly2(const Poly2& p)
{
    term2 *ptr=p.start;
    term2 *pos=NULL;
    start=NULL;
    while (ptr!=NULL)
    {  
        pos=addterm(ptr->an,ptr->n,pos);
        ptr=ptr->next;
    }    
}

Poly2::~Poly2()
{
   term2 *nx;
   while (start!=NULL)
   {   
       nx=start->next;
       delete start;
       start=nx;
   }
}

GF2m Poly2::coeff(int power)  const
{
    GF2m c=0;
    term2 *ptr=start;
    while (ptr!=NULL)
    {
        if (ptr->n==power)
        {
            c=ptr->an;
            return c;
        }
        ptr=ptr->next;
    }
    return c;
}

GF2m Poly2::F(const GF2m& x) const
{
    GF2m f=0;
    int diff;
    term2 *ptr=start;

// Horner's rule

    if (ptr==NULL) return f;
    f=ptr->an;

    while (ptr->next!=NULL)
    {
        diff=ptr->n-ptr->next->n;
        if (diff==1) f=f*x+ptr->next->an;
        else         f=f*pow(x,diff)+ptr->next->an;    
        ptr=ptr->next;
    }
    f*=pow(x,ptr->n);

    return f;
}

GF2m Poly2:: min() const
{
    term2 *ptr=start;
    if (start==NULL) return (GF2m)0;
    
    while (ptr->next!=NULL) ptr=ptr->next;
    return (ptr->an);
}

Poly2 operator*(const Poly2& a,const Poly2& b)
{
    int i,d,dega,degb,deg;
    GF2m t;
    Poly2 prod;
    term2 *iptr,*pos;
    term2 *ptr=b.start;

    if (&a==&b)
    { // squaring - only diagonal terms count!
        pos=NULL;
        while (ptr!=NULL)
        { // diagonal terms
            pos=prod.addterm(ptr->an*ptr->an,ptr->n+ptr->n,pos);
            ptr=ptr->next;
        }
        return prod;
    }

    dega=degree(a);
    deg=dega;
    degb=degree(b);
    if (degb<dega) deg=degb;  // deg is smallest


    if (deg>=KARAT_BREAK_EVEN)
    { // use fast method 
        int len,m,inc;

        big *A,*B,*C,*T;
        deg=dega;
        if (dega<degb) deg=degb;   // deg is biggest
        m=deg; inc=1;
        while (m!=0) { m/=2; inc++; }

        len=2*(deg+inc);

        A=(big *)mr_alloc(deg+1,sizeof(big));
        B=(big *)mr_alloc(deg+1,sizeof(big));
        C=(big *)mr_alloc(len,sizeof(big));
        T=(big *)mr_alloc(len,sizeof(big));
        for (i=0;i<len;i++)
        {
            C[i]=mirvar(0);
            T[i]=mirvar(0);
        }

        ptr=a.start;
        while (ptr!=NULL)
        {
            A[ptr->n]=getbig(ptr->an);
            ptr=ptr->next;
        }

        ptr=b.start;
        while (ptr!=NULL)
        {
            B[ptr->n]=getbig(ptr->an);
            ptr=ptr->next;
        }

        karmul2_poly(deg+1,T,A,B,C);

        pos=NULL;
        for (d=dega+degb;d>=0;d--)
        {
            t=C[d];
            if (t.iszero()) continue;
            pos=prod.addterm(t,d,pos);
        }

        for (i=0;i<len;i++)
        {
            mr_free(T[i]);
            mr_free(C[i]);
        }
        mr_free(T);
        mr_free(C);
        mr_free(B);
        mr_free(A);
        return prod;
    }

    while (ptr!=NULL)
    {
        pos=NULL;
        iptr=a.start;
        while (iptr!=NULL)
        {
            pos=prod.addterm(ptr->an*iptr->an,ptr->n+iptr->n,pos);
            iptr=iptr->next;
        }
        ptr=ptr->next;
    }

    return prod;
}

Poly2& Poly2::operator%=(const Poly2& v)
{
    GF2m m,pq;
    int power;
    term2 *rptr=start;
    term2 *vptr=v.start;
    term2 *ptr,*pos;
    if (degree(*this)<degree(v)) return *this;
    m=((GF2m)1/vptr->an);

    while (rptr!=NULL && rptr->n>=vptr->n)
    {
        pq=rptr->an*m;
        power=rptr->n-vptr->n;
        pos=NULL;
        ptr=v.start;
        while (ptr!=NULL)
        {
            pos=addterm(ptr->an*pq,ptr->n+power,pos);
            ptr=ptr->next;
        } 
        rptr=start;
    }
    return *this;
}

Poly2 operator%(const Poly2& u,const Poly2& v)
{
    Poly2 r=u;
    r%=v;
    return r;
}

Poly2 fulldiv(Poly2& r,const Poly2 &v)
{
    Poly2 q;
    GF2m pq,m;
    int power;
    term2 *rptr=r.start;
    term2 *vptr=v.start;
    term2 *ptr,*pos;
    m=(GF2m)1/vptr->an;

    while (rptr!=NULL && rptr->n>=vptr->n)
    {
        pq=rptr->an*m;
        power=rptr->n-vptr->n;
        q.addterm(pq,power);

        pos=NULL;
        ptr=v.start;
        while (ptr!=NULL)
        {
            pos=r.addterm(ptr->an*pq,ptr->n+power,pos);
            ptr=ptr->next;
        } 
        rptr=r.start;
    }
    return q;
}

Poly2 operator/(const Poly2& u,const Poly2 &v)
{
    Poly2 r=u;
    return fulldiv(r,v);
}

void swap(Poly2 &x,Poly2 &y)
{
    term2 *t;
    t=x.start;
    x.start=y.start;
    y.start=t;
}

Poly2 inverse(const Poly2& f,const Poly2& m)
{
    Poly2 r,s,q,p,x;
    term2 *ptr;
    x=f%m;
    r=1;
    s=0;
    p=m;
    while (!iszero(p))
    { // main euclidean loop */
        q=fulldiv(x,p);
        r+=s*q;
        swap(r,s);
        swap(x,p);
    }
    ptr=x.start;
    r.multerm((GF2m)1/ptr->an,0);
    return r;
}

Poly2 gcd(const Poly2& f,const Poly2& g)
{
    Poly2 a,b;
    a=f; b=g;
    term2 *ptr;

    forever
    {
        if (b.start==NULL)
        {
            ptr=a.start;
            a.multerm((GF2m)1/ptr->an,0);
            return a;
        }
        a%=b;
        if (a.start==NULL)
        {
            ptr=b.start;
            b.multerm((GF2m)1/ptr->an,0);
            return b;
        }
        b%=a;
    }
}

Poly2 pow(const Poly2& f,int k)
{
    Poly2 u;
    int w,e,b;

    if (k==0)
    {
        u.addterm((GF2m)1,0);
        return u;
    }
    u=f;
    if (k==1) return u;

    e=k;
    b=0; while (k>1) {k>>=1; b++; }
    w=(1<<b);
    e-=w; w/=2;
    while (w>0)
    {
        u=(u*u);
        if (e>=w)
        {
           e-=w;
           u=(u*f);
        }
        w/=2; 
    }
    return u;
}

Poly2 pow(const Poly2& f,const Big& k,const Poly2& m)
{
    Poly2 u,t;
    Big w,e;
    if (k==0) 
    {
        u.addterm((GF2m)1,0);
        return u;
    }
    u=(f%m);
    if (k==1) return u;

    e=k;
    w=pow((Big)2,bits(e)-1);
    e-=w; w/=2;
    while (w>0)
    {
        u=(u*u)%m;
        if (e>=w)
        {
           e-=w;
           u=(u*f)%m;
        }
        w/=2; 
    }
    return u;
}

int degree(const Poly2& p)
{
    if (p.start==NULL) return 0;
    else return p.start->n;
}


BOOL iszero(const Poly2& p) 
{
    if (degree(p)==0 && p.coeff(0)==0) return TRUE;
    else return FALSE;
}

BOOL isone(const Poly2& p)
{
    if (degree(p)==0 && p.coeff(0)==1) return TRUE;
    else return FALSE;
}

void Poly2::clear()
{
    term2 *ptr;
    while (start!=NULL)
    {   
       ptr=start->next;
       delete start;
       start=ptr;
    }
    
}

Poly2& Poly2::operator=(int m)
{
    clear();
    if (m!=0) addterm((GF2m)m,0);
    return *this;
}

Poly2 &Poly2::operator=(const Poly2& p)
{
    term2 *ptr,*pos=NULL;
    clear();
    ptr=p.start;
    while (ptr!=NULL)
    {  
        pos=addterm(ptr->an,ptr->n,pos);
        ptr=ptr->next;
    }    
    return *this;
}

Poly2 operator+(const Poly2& a,const Poly2& b)
{
    Poly2 sum;
    sum=a;
    sum+=b;
    return sum;
}

Poly2 operator+(const Poly2& a,const GF2m& b)
{
    Poly2 sum=a;
    sum.addterm(b,0);
    return sum;
}

Poly2& Poly2::operator+=(const Poly2& p)
{
    term2 *ptr,*pos=NULL;
    ptr=p.start;
    while (ptr!=NULL)
    {  
        pos=addterm(ptr->an,ptr->n,pos);
        ptr=ptr->next;
    }    
    return *this;
}

Poly2& Poly2::operator*=(const GF2m& x)
{
    term2 *ptr=start;
    while (ptr!=NULL)
    {
        ptr->an*=x;
        ptr=ptr->next;
    }
    return *this;
}


Poly2 operator*(const GF2m& z,const Poly2 &p)
{
    Poly2 r=p;
    r*=z;
    return r;
}

Poly2 operator*(const Poly2 &p,const GF2m& z)
{
    Poly2 r=p;
    r*=z;
    return r;
}

Poly2 operator/(const Poly2& a,const GF2m& b)
{
    Poly2 quo;
    quo=a;
    quo/=(GF2m)b;
    return quo;
}


Poly2& Poly2::operator/=(const GF2m& x)
{
    GF2m t=(GF2m)1/x;
    term2 *ptr=start;
    while (ptr!=NULL)
    {
        ptr->an*=t;
        ptr=ptr->next;
    }
    return *this;
}

void Poly2::multerm(const GF2m& a,int power)
{
    term2 *ptr=start;
    while (ptr!=NULL)
    {
        ptr->an*=a;
        ptr->n+=power;
        ptr=ptr->next;
    }
}

Poly2 invmodxn(const Poly2& a,int n)
{ // Newton's method to find 1/a mod x^n
    int i,k;
    Poly2 b;
    k=0; while ((1<<k)<n) k++;
    b.addterm((GF2m)1/a.coeff(0),0); // important that a0 != 0
    for (i=1;i<=k;i++)
         b=modxn (a*(b*b),1<<i);
    b=modxn(b,n);
    return b;
}

Poly2 modxn(const Poly2& a,int n)
{ // reduce polynomial mod x^n
    Poly2 b;
    term2* ptr=a.start;
    term2 *pos=NULL;
    while (ptr!=NULL && ptr->n>=n) ptr=ptr->next;
    while (ptr!=NULL)
    {
        pos=b.addterm(ptr->an,ptr->n,pos);
        ptr=ptr->next;
    }
    return b;
}

Poly2 divxn(const Poly2& a,int n)
{ // divide polynomial by x^n
    Poly2 b;
    term2 *ptr=a.start;
    term2 *pos=NULL;
    while (ptr!=NULL)
    {
        if (ptr->n>=n)
            pos=b.addterm(ptr->an,ptr->n-n,pos);
        else break;
        ptr=ptr->next;
    }
    return b;
}

Poly2 mulxn(const Poly2& a,int n)
{ // multiply polynomial by x^n
    Poly2 b;
    term2 *ptr=a.start;
    term2 *pos=NULL;
    while (ptr!=NULL)
    {
        pos=b.addterm(ptr->an,ptr->n+n,pos);
        ptr=ptr->next;
    }
    return b;
}

Poly2 reverse(const Poly2& a)
{
    term2 *ptr=a.start;
    int deg=degree(a);
    Poly2 b;
    while (ptr!=NULL)
    {
        b.addterm(ptr->an,deg-ptr->n);
        ptr=ptr->next;
    } 
    return b;
}

// add term to polynomial. The pointer pos remembers the last
// accessed element - this is faster. 
// Polynomial is stored with large powers first, down to low powers
// e.g. 9x^6 + x^4 + 3x^2 + 1

term2* Poly2::addterm(const GF2m& a,int power,term2 *pos)
{
    term2* newone;  
    term2* ptr;
    term2 *t,*iptr;
    ptr=start;
    iptr=NULL;
    if (a.iszero()) return pos;
// quick scan through to detect if term exists already
// and to find insertion point
    if (pos!=NULL) ptr=pos;      // start looking from here
    while (ptr!=NULL) 
    { 
        if (ptr->n==power)
        {
            ptr->an+=a;
            if (ptr->an.iszero()) 
            { // delete term
                if (ptr==start)
                { // delete first one
                    start=ptr->next;
                    delete ptr;
                    return start;
                }
                iptr=ptr;
                ptr=start;
                while (ptr->next!=iptr)ptr=ptr->next;
                ptr->next=iptr->next;
                delete iptr;
                return ptr;
            }
            return ptr;
        }
        if (ptr->n>power) iptr=ptr;
        else break;
        ptr=ptr->next;
    }
    newone=new term2;
    newone->next=NULL;
    newone->an=a;
    newone->n=power;
    pos=newone;
    if (start==NULL)
    {
        start=newone;
        return pos;
    }

// insert at the start

    if (iptr==NULL)
    { 
        t=start;
        start=newone;
        newone->next=t;
        return pos;
    }

// insert new term

    t=iptr->next;
    iptr->next=newone;
    newone->next=t;
    return pos;    
}

ostream& operator<<(ostream& s,const Poly2& p)
{
    BOOL first=TRUE;
    GF2m a;
    term2 *ptr=p.start;
    if (ptr==NULL)
    { 
        s << "0";
        return s;
    }
    while (ptr!=NULL)
    {
        a=ptr->an;
        if (!first) s << " + ";
        if (ptr->n==0) 
           cout << a; 
        else 
        {
            if (a!=(GF2m)1)  s << a << "*x"; 
            else            s << "x";
            if (ptr->n!=1)  s << "^" << ptr->n;
        }
        first=FALSE;
        ptr=ptr->next;
    }
    return s;
} 

