/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


/*
 * C++ class to implement a polynomial type and to allow 
 * arithmetic on polynomials whose elements are flash numbers
 *
 * WARNING: This class has been cobbled together for a specific use with
 * the MIRACL library. It is not complete, and may not work in other 
 * applications
 *
 * See Knuth The Art of Computer Programming Vol.2, Chapter 4.6 
 */

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif
#include "fpoly.h"


FPoly::FPoly(const FPoly& p)
{
    fterm *ptr=p.start;
    fterm *pos=NULL;
    start=NULL;
    while (ptr!=NULL)
    {  
        pos=addterm(ptr->an,ptr->n,pos);
        ptr=ptr->next;
    }    
}

FPoly::~FPoly()
{
   fterm *nx;
   while (start!=NULL)
   {   
       nx=start->next;
       delete start;
       start=nx;
   }
}

Flash FPoly::coeff(int power)
{
    Flash c=0;
    fterm *ptr=start;
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

FPoly operator*(const FPoly& a,const FPoly& b)
{
    FPoly prod;
    fterm *iptr,*pos;
    fterm *ptr=b.start;
    if (&a==&b)
    { // squaring
        pos=NULL;
        while (ptr!=NULL)
        { // diagonal terms
            pos=prod.addterm(ptr->an*ptr->an,ptr->n+ptr->n,pos);
            ptr=ptr->next;
        }
        ptr=b.start;
        while (ptr!=NULL)
        { // above the diagonal
            iptr=ptr->next;
            pos=NULL;
            while (iptr!=NULL)
            {
                pos=prod.addterm(2*ptr->an*iptr->an,ptr->n+iptr->n,pos);
                iptr=iptr->next;
            }
            ptr=ptr->next; 
        }

    }
    else while (ptr!=NULL)
    {
        FPoly t=a; 
        t.multerm(ptr->an,ptr->n);
        ptr=ptr->next;
        prod+=t;
    }

    return prod;
}

int degree(const FPoly& p)
{
    return p.start->n;
}

void FPoly::clear()
{
    fterm *ptr;
    while (start!=NULL)
    {   
       ptr=start->next;
       delete start;
       start=ptr;
    }
    
}

FPoly &FPoly::operator=(const FPoly& p)
{
    fterm *ptr,*pos=NULL;
    clear();
    ptr=p.start;
    while (ptr!=NULL)
    {  
        pos=addterm(ptr->an,ptr->n,pos);
        ptr=ptr->next;
    }    
    return *this;
    
}

FPoly& FPoly::operator+=(const FPoly& p)
{
    fterm *ptr,*pos=NULL;
    ptr=p.start;
    while (ptr!=NULL)
    {  
        pos=addterm(ptr->an,ptr->n,pos);
        ptr=ptr->next;
    }    
    return *this;
}

FPoly& FPoly::operator-=(const FPoly& p)
{
    fterm *ptr,*pos=NULL;
    ptr=p.start;
    while (ptr!=NULL)
    {  
        pos=addterm(-(ptr->an),ptr->n,pos);
        ptr=ptr->next;
    }    
    return *this;
}
 
void FPoly::multerm(Flash a,int power)
{
    fterm *ptr=start;
    while (ptr!=NULL)
    {
        ptr->an*=a;
        ptr->n+=power;
        ptr=ptr->next;
    }
}

fterm* FPoly::addterm(Flash a,int power,fterm *pos)
{
    fterm* newone;  
    fterm* ptr;
    fterm *t,*iptr;
    ptr=start;
    iptr=NULL;
    if (a.iszero()) return pos;
// quick scan through to detect if term exists already
// and to find insertion point

    if (pos!=NULL) ptr=pos;
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
    newone=new fterm;
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

ostream& operator<<(ostream& s,const FPoly& p)
{
    int first=1;
    Flash a;
    fterm *ptr=p.start;
    if (ptr==NULL)
    { 
        s << "0";
        return s;
    }
    while (ptr!=NULL)
    {
        
        a=ptr->an;
        if (a>0)
        {
            if (!first) s << " + ";
        }
        else            s << " - ";

        if (a<0) a=(-a);
        if (ptr->n==0) 
           cout << a; 
        else 
        {
            if (a!=(Flash)1) s << a << "*x"; 
            else            s << "x";
            if (ptr->n!=1)  s << "^" << ptr->n;
        }
        first=0;
        ptr=ptr->next;
    }
    return s;
} 

