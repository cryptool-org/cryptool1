/*
 * C++ class to implement a bivariate polynomial type and to allow 
 * arithmetic on such polynomials whose coefficients are from
 * the finite field mod p
 *
 * WARNING: This class has been cobbled together for a specific use with
 * the MIRACL library. It is not complete, and may not work in other 
 * applications
 *
 * See Knuth The Art of Computer Programming Vol.2, Chapter 4.6 
 */

#include "polyxy.h"

PolyXY::PolyXY(const PolyXY& p)
{
    termXY *ptr=p.start;
    termXY *pos=NULL;
    start=NULL;
    while (ptr!=NULL)
    {  
        pos=addterm(ptr->an,ptr->nx,ptr->ny,pos);
        ptr=ptr->next;
    }    
}

PolyXY::~PolyXY()
{
   termXY *nx;
   while (start!=NULL)
   {   
       nx=start->next;
       delete start;
       start=nx;
   }
}

ZZn PolyXY::coeff(int powx,int powy)
{
    ZZn c=0;
    termXY *ptr=start;
    while (ptr!=NULL)
    {
        if (ptr->nx==powx && ptr->ny==powy)
        {
            c=ptr->an;
            return c;
        }
        ptr=ptr->next;
    }
    return c;
}

PolyXY diff_dx(const PolyXY& f)
{
    PolyXY r;
    termXY *pos=NULL;
    termXY *ptr=f.start;
    while (ptr!=NULL)
    {
        pos=r.addterm(ptr->an*ptr->nx,ptr->nx-1,ptr->ny,pos);
        ptr=ptr->next;
    }
    return r;
}

PolyXY diff_dy(const PolyXY& f)
{
    PolyXY r;
    termXY *pos=NULL;
    termXY *ptr=f.start;
    while (ptr!=NULL)
    {
        pos=r.addterm(ptr->an*ptr->ny,ptr->nx,ptr->ny-1,pos);
        ptr=ptr->next;
    }
    return r;
}

Poly PolyXY::F(const ZZn& y)
{
    Poly r;
    term *pos=NULL;
    int i,maxy=0;
    ZZn f;
    termXY *ptr=start;

    while (ptr!=NULL)
    {
        if (ptr->ny>maxy) maxy=ptr->ny;
        ptr=ptr->next;
    }

// max y is max power of y present

    ZZn *pw=new ZZn[maxy+1];   // powers of y

    pw[0]=(ZZn)1;
    for (i=1;i<=maxy;i++)
        pw[i]=y*pw[i-1];
    
    ptr=start;
    while (ptr!=NULL)
    {
        pos=r.addterm(ptr->an*pw[ptr->ny],ptr->nx,pos);
        ptr=ptr->next;
    }

    delete [] pw;

    return r;
}

ZZn PolyXY::F(const ZZn& x,const ZZn& y)
{
    Poly r=F(y);
    return r.F(x);
}

void PolyXY::clear()
{
    termXY *ptr;
    while (start!=NULL)
    {   
       ptr=start->next;
       delete start;
       start=ptr;
    }
    
}

PolyXY& PolyXY::operator=(const PolyXY& p)
{
    termXY *ptr,*pos=NULL;
    clear();
    ptr=p.start;
    while (ptr!=NULL)
    {  
        pos=addterm(ptr->an,ptr->nx,ptr->ny,pos);
        ptr=ptr->next;
    }    
    return *this;
    
}

termXY* PolyXY::addterm(const ZZn& a,int powx,int powy,termXY *pos)
{
    termXY* newone;  
    termXY* ptr;
    termXY *t,*iptr;
    ptr=start;
    iptr=NULL;
    if (a.iszero()) return pos;

// quick scan through to detect if term exists already
// and to find insertion point
    if (pos!=NULL) ptr=pos;
    while (ptr!=NULL) 
    { 
        if (ptr->nx==powx && ptr->ny==powy)
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
        if (ptr->nx>powx) iptr=ptr;
        if (ptr->nx==powx && ptr->ny>powy) iptr=ptr;
        ptr=ptr->next;
    }
    newone=new termXY;
    newone->next=NULL;
    newone->an=a;
    newone->nx=powx;
    newone->ny=powy;

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

ostream& operator<<(ostream& s,const PolyXY& p)
{
    BOOL first=TRUE;
    ZZn a;
    termXY *ptr=p.start;
    if (ptr==NULL)
    { 
        s << "0";
        return s;
    }
    while (ptr!=NULL)
    {
        a=ptr->an;
        if ((Big)a<get_modulus()/2)
        {
            if (!first) s << " + ";
        }
        else 
        {
           a=(-a);
           s << " - ";
        }
        if (ptr->nx==0 && ptr->ny==0) 
           cout << a; 
        else 
        {
            if (a!=(ZZn)1) s << a << "*";
            if (ptr->nx!=0)
            {
                s << "x";
                if (ptr->nx!=1)  s << "^" << ptr->nx;
            }
            if (ptr->ny!=0)
            {
                if (ptr->nx!=0) s << ".";
                s << "y";
                if (ptr->ny!=1)  s << "^" << ptr->ny;
            }
        }
        first=FALSE;
        ptr=ptr->next;
    }
    return s;
} 

