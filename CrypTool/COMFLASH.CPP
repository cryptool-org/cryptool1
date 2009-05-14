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

