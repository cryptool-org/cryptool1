/*
 * Quick and dirty complex data type using flash arithmetic
 * Should be extended
 */


#ifndef COMFLASH_H
#define COMFLASH_H

#include <iostream.h>
#include <flash.h>

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

