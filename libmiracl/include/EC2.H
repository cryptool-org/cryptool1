/*
 *    MIRACL  C++ Header file ec2.h
 *
 *    AUTHOR  : M. Scott
 *  
 *    PURPOSE : Definition of class EC2  (Arithmetic on an Elliptic Curve,
 *               over GF(2^m)
 *
 *    NOTE    : Must be used in conjunction with ec2.cpp and big.cpp
 *              The active curve is set dynamically (via the Big ecurve2() 
 *              routine) - so beware the pitfalls implicit in declaring
 *              static or global EC2's (which are initialised before the 
 *              curve is set!). Uninitialised data is OK 
 *
 *    Copyright (c) 2000 Shamus Software Ltd.
 */

#ifndef EC2_H
#define EC2_H

#include <big.h>

class EC2
{
    epoint *p;
public:
    EC2()                         { p=epoint2_init();}
   
    EC2(const Big &x,const Big& y)  {p=epoint2_init(); 
                                   epoint2_set(x.getbig(),y.getbig(),0,p); }
    
  // This next constructor restores a point on the curve from "compressed" 
  // data, that is the full x co-ordinate, and the LSB of y/x  (0 or 1)

    EC2(const Big& x,int cb)       {p=epoint2_init();
                                   epoint2_set(x.getbig(),x.getbig(),cb,p); }
                   
    EC2(const EC2 &b)             {p=epoint2_init(); epoint2_copy(b.p,p);}

    epoint *get_point() const;
    
    EC2& operator=(const EC2& b)  {epoint2_copy(b.p,p);return *this;}

    EC2& operator+=(const EC2& b) {ecurve2_add(b.p,p); return *this;}
    EC2& operator-=(const EC2& b) {ecurve2_sub(b.p,p); return *this;}

  // Multiplication of a point by an integer. 

    EC2& operator*=(const Big& k) {ecurve2_mult(k.getbig(),p,p); return *this;}

    void clear() {epoint2_set(NULL,NULL,0,p);}
    BOOL set(const Big& x,const Big& y)    {return epoint2_set(x.getbig(),y.getbig(),0,p);}
    int get(Big& x,Big& y) const;
    BOOL iszero() const;
  // This gets the point in compressed form. Return value is LSB of y-coordinate
    int get(Big& x) const;

  // point compression

  // This sets the point from compressed form. cb is LSB of y/x 

    BOOL set(const Big& x,int cb=0)  {return epoint2_set(x.getbig(),x.getbig(),cb,p);}

    friend EC2 operator-(const EC2&);
    friend void multi_add(int,EC2 *,EC2 *);
  
    friend EC2 mul(const Big&, const EC2&, const Big&, const EC2&);
    friend EC2 mul(int, const Big *, EC2 *);
  
    friend void normalise(EC2 &e) {epoint2_norm(e.p);}

    friend BOOL operator==(const EC2& a,const EC2& b)
                                  {return epoint2_comp(a.p,b.p);}    
    friend BOOL operator!=(const EC2& a,const EC2& b)
                                  {return (!epoint2_comp(a.p,b.p));}    

    friend EC2 operator*(const Big &,const EC2&);
    friend ostream& operator<<(ostream&,const EC2&);

    ~EC2() {epoint2_free(p); }

};

#endif

