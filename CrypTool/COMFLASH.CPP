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



#include "comflash.h"


Complex& Complex::operator=(const Complex& a)
{x=a.x; y=a.y; return *this;}

Complex& Complex::operator+=(const Complex& a)
{x+=a.x; y+=a.y; return *this;}

Complex& Complex::operator-=(const Complex& a)
{x-=a.x; y-=a.y; return *this;}

Complex& Complex::operator*=(const Complex& a)
{Flash t=x*a.x-y*a.y; y=y*a.x+x*a.y; x=t; return *this;}

Complex& Complex::operator/=(const Complex& a)
{Flash t,d=a.x*a.x+a.y*a.y;
 t=(x*a.x+y*a.y)/d; y=(y*a.x-x*a.y)/d; x=t; return *this;}

Flash real(const Complex &a) {Flash f; f=a.x; return f;}
Flash imaginary(const Complex &a) {Flash f; f=a.y; return f;}

Complex operator-(const Complex& a)
{Complex c; c.x=-a.x; c.y=-a.y; return c;}

BOOL operator==(const Complex& a,const Complex& b)
{ if (a.x==b.x && a.y==b.y) return TRUE; else return FALSE;}

BOOL operator!=(const Complex& a,const Complex& b)
{ if (a.x!=b.x || a.y!=b.y) return TRUE; else return FALSE;}


Complex operator+(const Complex &a,const Complex &b)
{Complex c; c.x=a.x+b.x; c.y=a.y+b.y; return c;}

Complex operator-(const Complex &a,const Complex &b)
{Complex c; c.x=a.x+b.x; c.y=a.y+b.y; return c;}

Complex operator*(const Complex &a,const Complex &b)
{Complex c; c.x=a.x*b.x-a.y*b.y; c.y=a.x*b.y+a.y*b.x; return c;}

Complex operator/(const Complex &a,const Complex &b)
{Complex c; 
 Flash d=b.x*b.x+b.y*b.y;
 c.x=(a.x*b.x+a.y*b.y)/d; c.y=(a.y*b.x-a.x*b.y)/d; return c;}

Complex exp(const Complex& a)
{Complex c; 
 Flash d=exp(a.x);
 c.x=d*cos(a.y); 
 c.y=d*sin(a.y); return c;}

Complex log(const Complex& a)
{Complex c;
 c.x=log(sqrt(a.x*a.x+a.y*a.y));
 if (a.x==0) c.y=pi()/2;
 else c.y=atan(a.y/a.x);  return c; }

Complex pow(const Complex& a,const Complex& b)
{Complex c; 
 c=exp(b*log(a)); return c;}

Complex pow(const Complex& a, int b)
{Complex w=1;
 Complex c=a; 

 if (b==0) return w;
 if (b<0)
 {
    b=-b; c=1/c;
 }
 if (b==1) return c;
 forever
 {
    if (b%2!=0) w=c*w;
    b/=2;
    if (b==0) break;
    c=c*c;
 }
 return w; 
}


Complex nroot(const Complex &a,int n)
{Complex c;
 Flash t,r,theta;
 if (a==0) return (Complex)0;
 if (a.x==0) theta=pi()/2; 
 else theta=atan(a.y/a.x);
 if (a.y==0) r=a.x;
 if (a.x==0) r=a.y;
 if (a.x!=0 && a.y!=0) r=sqrt(a.x*a.x+a.y*a.y);
 t=nroot(r,n);
 r=theta/n;
 c.x=t*cos(r); c.y=t*sin(r);
 return c;
} 

ostream& operator<<(ostream& s,const Complex&a)
{
    s << "(" << a.x << "," << a.y << ")";
    return s;
}

