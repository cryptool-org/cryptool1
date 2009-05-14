/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/


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

