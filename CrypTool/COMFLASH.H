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
 * Quick and dirty complex data type using flash arithmetic
 * Should be extended
 */


#ifndef COMFLASH_H
#define COMFLASH_H

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif
#include "flash.h"

class Complex
{
    Flash x,y;
public:
    Complex() {x=(Flash)0; y=(Flash)0; }
    Complex(int a) {x=(Flash)a; y=(Flash)0; }
    Complex(const Flash& a) {x=a; y=(Flash)0; }
    Complex(const Flash& a,const Flash& b) {x=a;y=b;}
    Complex(const Complex& a) {x=a.x;y=a.y;}

    Complex& operator=(const Complex &);
    Complex& operator+=(const Complex &);
    Complex& operator-=(const Complex &);
    Complex& operator*=(const Complex &);
    Complex& operator/=(const Complex &);

    friend Flash real(const Complex &);
    friend Flash imaginary(const Complex &);


    friend Complex operator-(const Complex&);

    friend BOOL operator==(const Complex&,const Complex&);
    friend BOOL operator!=(const Complex&,const Complex&);

    friend Complex operator+(const Complex &, const Complex &);
    friend Complex operator-(const Complex &, const Complex &);
    friend Complex operator*(const Complex &, const Complex &);
    friend Complex operator/(const Complex &, const Complex &);
    friend Complex exp(const Complex &);
    friend Complex log(const Complex &);
    friend Complex pow(const Complex &,const Complex &);    
    friend Complex pow(const Complex &,int);
    friend Complex nroot(const Complex&,int);
    friend ostream& operator<<(ostream&,const Complex&);
    ~Complex() {}
};

#endif

