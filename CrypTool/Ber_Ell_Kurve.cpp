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

// Ber_Ell_Kurve.cpp: Implementierung der Klasse Ber_Ell_Kurve.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "CrypToolApp.h"
#include "eval.h"
#include "Ber_Ell_Kurve.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////



Ber_Ell_Kurve::Ber_Ell_Kurve()
{
//	mip = &g_precision;
}

Ber_Ell_Kurve::~Ber_Ell_Kurve()
{
//	mip = 0;
}

// F(z) Function A.13.3



Complex Ber_Ell_Kurve::Fz(Complex z)
{
	int i=1;
    int j=2;
    int inci=1;
    int incj=2;
    int sign=1;

    Complex sum=(Flash)1;
    forever
    { 
        Complex t=pow(z,i)+pow(z,j);
// this works! (due to floating-slash rounding)   
        if (t==(Complex)0) break;   
        if (sign) sum-=t;
        else      sum+=t;
        inci+=3;
        incj+=3;
        i+=inci;
        j+=incj;
        sign=1-sign;
    }
    return sum;
}



int Ber_Ell_Kurve::geti(int D)
{
	int d=D%8;
    if (d==1 || d==2 || d==6 || d==7) return 3;
    if (d==3)
    {
       if (D%3==0) return 2;
       else        return 0;
    } 
    if (d==5) return 6;
    return 0;
}

int Ber_Ell_Kurve::getk(int D)
{
	int d=D%8;
    if (d==1 || d==2 || d==6) return 2;
    if (d==3 || d==7) return 1;
    if (d==5) return 4;
    return 0;
}

// A.13.3

void Ber_Ell_Kurve::class_poly(int A,int B,int C, int D, BOOL conj)
{
	int g,i,j,k,l,m,n,dm8,ac,t;
    Complex cinv,lam;
    g=igcd(D,3);
    ac=A*C;
    if (ac%2==1) 
    {
        j=0;
        l=A-C+A*A*C;
    }
    if (C%2==0)  j=1;
    if (A%2==0)  j=2;

    if (A%2==0)
    {
        t=(C*C-1)/8;
        if (t%2==0) m=1;
        else        m=-1;
    }
    else
    {
        t=(A*A-1)/8;
        if (t%2==0) m=1;
        else        m=-1;
    }
    
    dm8=D%8;
    i=geti(D);
    k=getk(D);
    switch (dm8)
    {
    case 1: 
    case 2:    n=m;
               if (C%2==0) l=A+2*C-A*C*C;
               if (A%2==0) l=A-C-A*C*C;
               break;
    case 3:    if (ac%2==1) n=1;
               else         n=-m;
               if (C%2==0) l=A+2*C-A*C*C;
               if (A%2==0) l=A-C+5*A*C*C;
               break;
    case 5:    n=1;
               if (C%2==0) l=A-C+A*A*C;
               if (A%2==0) l=A-C-A*C*C;
               break;
    case 6:    n=m;
               if (C%2==0) l=A+2*C-A*C*C;
               if (A%2==0) l=A-C-A*C*C;
               break;
    case 7:    if (ac%2==0) n=1;
               else         n=m;
               if (C%2==0) l=A+2*C-A*C*C;
               if (A%2==0) l=A-C-A*C*C;
               break;
               
    default: break;
    }
    lam=exp(Complex((Flash)0,-k*pi()/(Flash)24));


    cinv=pow(n*pow(lam,-B*l)*pow((Flash)2,Flash(-i,6))*pow(F(j,A,B,C),k),g);
    if (cinv!=0)
    { // multiply polynomial by new term(s)
        FPoly F;
        if (conj)
        { // conjugate pair
          // t^2-2a+(a^2+b^2) , where cinv=a+ib
            F.addterm((Flash)1,2);
            F.addterm(-2*real(cinv),1);
            F.addterm(real(cinv)*real(cinv)+imaginary(cinv)*imaginary(cinv),0);
        }
        else 
        { // t-cinv
            F.addterm((Flash)1,1);
            F.addterm(-real(cinv),0);
        }
        T=T*F;    // acumulate Polynomial
    }
}

Complex Ber_Ell_Kurve::F(int j,int A,int B,int C)
{
	Complex t,theta;
    Flash sd;
    int D=A*C-B*B;
    sd=-sqrt((Flash)D);

    t=Complex(sd*pi()/A,(pi()*B)/A);
    theta=exp(t);
    if (theta==0) return 0;  
    if (j!=2) t=nroot(theta,-24);    // nroot - n-th root of a complex
    else      t=nroot(theta,12);

    if (j==0) return (t*Fz(-theta)/Fz(theta*theta));
    if (j==1) return (t*Fz(theta)/Fz(theta*theta));
    if (j==2) return (sqrt((Flash)2)*t*Fz(theta*theta*theta*theta)/Fz(theta*theta));
    return 0;
}

void Ber_Ell_Kurve::groups(int D)
{
	int s,t,A,C,B,lim;
    s=(int)sqrt(D/3.0);
    for (B=0;B<=s;B++)
    {
        t=D+B*B;
        lim=(int)sqrt((double)t);
        A=2*B;
        if (A==0) A++;
        for(;;)
        {
            while (t%A!=0) 
            {
                A++;
                if (A>lim) break;
            }

            if (A>lim) break;;
            C=t/A;
           
            if (igcd(igcd(A,2*B),C)==1)
            { // output more class group members
                BOOL conj=FALSE;
                if (2*B>0 && C>A && A>2*B) conj=TRUE;
                class_poly(A,B,C,D,conj);
            }
            A++;
        }        
    }
}

// check congruence conditions A14.2.1

bool Ber_Ell_Kurve::isaD(int d,int pm8,int k)
{
	int i,dm8;
   BOOL sqr;
   dm8=d%8;
   if (k==1 && dm8!=3) return FALSE;
   if ((k==2 || k==3) && dm8==7) return FALSE;
   if (pm8==3 && (dm8==1 || dm8==4 || dm8==5 || dm8==6)) return FALSE;
   if (pm8==5 && dm8%2==0) return FALSE;
   if (pm8==7 && (dm8==1 || dm8==2 || dm8==4 || dm8==5)) return FALSE;
   sqr=FALSE;
   for (i=2;;i++)
   {
       if (d%(i*i)==0)
       {
           sqr=TRUE;
           break;
       }
       if (i*i>d) break;
   }
   if (sqr) return FALSE;
   return TRUE;
}

// Testing for CM discriminants A.14.2.2


bool Ber_Ell_Kurve::isacm(Big p,int D,Big &W,Big &V)
{
	Big B2,A,B,C,t,X,Y,ld,delta;
    B=sqrt(p-D,p);
    A=p;
    C=(B*B+D)/p;
    X=1;
    Y=0;
    ld=0;
    while (1)
    {
        if (C>=A)
        {
            B2=2*B;
            if (B2<0) B2=-B2;
            if (A>=B2) break;
        } 
        delta=(2*B+C)/(2*C);
        if (delta<0 && ((2*B+C)%(2*C)) !=0) delta=delta-1;
// are we stuck in hopeless loop? This can't happen now - thanks Marcel
        if (delta==0 && ld==0) return FALSE;
        ld=delta;
        t=X;
        X=(delta*X+Y);
        Y=-t;

        t=C;
        C=(A+C*delta*delta-2*B*delta);
        B=(t*delta-B);
        A=t;        
    }
    if (D==11 && A==3)
    {
        t=X;
        X=Y;
        Y=-t;
        B=-B;
        t=C;
        C=A;
        A=t;        
    }      
    if (D==1 || D==3) 
    {
       W=2*X;
       V=2*Y;
       return TRUE;
    }
    else V=0;

    if (A==1) 
    {
        W=2*X;
        return TRUE;
    }

    if (A==4) 
    {
        W=4*X+B*Y;
        return TRUE;
    }

    return FALSE;
}


// Constructing a Curve and Point
// A.14.4

bool Ber_Ell_Kurve::get_curve(ofstream& ofile, Big r, Big ord, int D, Big p, Big W, int saat)
{
	Poly polly;
	Big A0,B0,k;
    BOOL unstable;
    int i,terms;
    k=r/ord;

	modulo(p);

// A.14.4.1
    
    if (D==1)
    {
        A0=1; B0=0;
    }
    if (D==3)
    {
        A0=0; B0=1;
    }

    if (D!=1 && D!=3)
    {
        Flash f,rem;
        T.clear();
        T.addterm(1,0);   
//		constructing polynomial
        groups(D);
        terms=degree(T);
        unstable=FALSE;
        for (i=terms;i>=0;i--)
        {
            f=T.coeff(i);
            if (f>0)
                 f+=Flash(1,10000);
            else f-=Flash(1,10000);
            polly.addterm((ZZn)f.trunc(&rem),i);
            if (fabs(rem)>Flash(1,100)) 
            {
                unstable=TRUE; 
                break; 
            }
        }
        T.clear();
        if (unstable) 
        {
//			Curve abandoned - numerical instability
//			finding a nearly prime order
			LoadString(AfxGetInstanceHandle(),IDS_STRING37102,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str);
			AfxMessageBox(line);
            return FALSE;
        }
    }

    ECn pt,G;
    Big a,b,x,y;
    Big w,eps;
    int at;
//	char c;

    Poly g;

	irand(saat);

    forever
    {
        if (D!=1 && D!=3)
        {
//			Factoring polynomial of degree
            if (W%2==0)
            {
                ZZn V;
                g=factor(polly,1);
                V=-g.coeff(0);
                V=pow(V,24/(igcd(D,3)*getk(D)));
                V*=pow((ZZn)2,(4*geti(D))/getk(D));
                if (D%2!=0) V=-V;
                A0=(Big)((ZZn)(-3)*(V+64)*(V+16));   
                B0=(Big)((ZZn)2*(V+64)*(V+64)*(V-8));
            }
            else
            {
                Poly V,w,w1,w2,w3,a,b;

                g=factor(polly,3);
                if (D%3!=0)
                    w.addterm(-1,24);
                else
                    w.addterm(-256,8);
                V=w%g;
                w.clear();
                w1=V; w2=V; w3=V;
                w1.addterm(64,0);
                w2.addterm(256,0);
                w3.addterm(-512,0);
                a=w1*w2;
                a.multerm(-3,0);
                a=a%g;
                b=w1*w1*w3;
                b.multerm(2,0);
                b=b%g;

                a=((a*a)*a)%g;
                b=(b*b)%g;
                for (int d=degree(g)-1 ;d>=0;d--)
                {
                    ZZn t,c=a.coeff(d);
                    if (c!=(ZZn)0)
                    {
                        t=b.coeff(d);
                        A0=(Big)(c*t);
                        B0=(Big)(c*t*t);
                        if (d==1) break;
                    }     
                }
            }
        }

// A.13.4.2
// but try -3 first, followed by small positive values for A

        a=A0;
        b=B0;
        at=-3;
        if (D==3) at=1;
        forever
        {
            if (D==1)
            {
                if (at<100)
                    eps=(ZZn)at/(ZZn)A0;
                else eps=rand(p);
                a=modmult(A0,eps,p);
            }
            if (D==3) 
            {
                if (at<100)
                    eps=(ZZn)at/(ZZn)B0;
                else eps=rand(p);
                b=modmult(B0,eps,p);
            }
            if (D!=1 && D!=3)
            {
                if (at<100)
                { // transform a to be simple if possible
                    w=(ZZn)at/ZZn(A0);
                    if (jacobi(w,p)!=1) 
                    {   
                        if (at==-3) at=1;
                        else at++; 
                        continue;
                    }
                    eps=sqrt(w,p);
                } else eps=rand(p);
                a=modmult(A0,pow(eps,2,p),p);
                b=modmult(B0,pow(eps,3,p),p);   
            } 
            ecurve(a,b,p,MR_PROJECTIVE);
            for (int xc=1;;xc++)
            {
                if (!pt.set((Big)xc)) continue;

                pt*=k;
                pt.get(x,y);
                if (x==0 && y==0) continue;
                break;
            }
            G=pt;
            pt*=ord;
            pt.get(x,y);
            if (x==0 && y==0) break;
            if (at==-3) at=1;
            else at++;
        }
        if (a==(p-3)) a=-3;
// check MOV condition
// A.12.1
        w=1;
        for (i=0;i<100;i++)
        {
            w=modmult(w,p,ord);
            if (w==1) 
            {
//				Failed MOV condition
//				finding a nearly prime order
                LoadString(AfxGetInstanceHandle(),IDS_SEEK_NEXT_PRIME,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str);
				AfxMessageBox(line);
				return FALSE;
            }
        }
    
//		Curve and Point Found
//		MOV condition OK

		a_par=a;
		b_par=b;
		G.get(x,y);
		x_par=x;
		y_par=y;
		p_par=p;
		r_par=ord;
		k_par=k;
		
/*		if (D!=1 && D!=3 )
        {
            polly=polly/g;
            if (degree(polly)>0)
            {
                //cout << "Try for different random factorisation (Y/N)? ";
                //cin >> c;
				c='n';
                if (c=='Y' || c=='y') continue;
            }
        }
*/

        break;
    }
    /* Roger 28.02.2001
	cout << "\nCurve and Point OK (Y/N)? " ;
    cin >> c;
    if (c=='N' || c=='n') 
    {
        if (!suppress) cout << "finding a nearly prime order..." << endl;
        return FALSE;
    }
	*/
	fout=TRUE;
	if (fout)
	    {
		ofile << bits(p) << endl;
        mip->IOBASE=10;
		ofile << p << endl;
		ofile << a << endl;
        ofile << b << endl;
        ofile << ord << endl;
        ofile << x << endl;
        ofile << y << endl;
        mip->IOBASE=10;
		}


	polly.clear();
	return TRUE;
}

int Ber_Ell_Kurve::GetInitPrime(CString Eingabe, int saat)
{	

	ofstream ofile="EcPrime.txt";
    Big W,V,r,ord;
    Big p,rmin;
    BOOL good,dir;
    int i,ip,k,K,D;

    irand(0L);
//    Program finds Elliptic Curve mod a prime P and point of prime order
//      that is a point (X,Y) on the curve y^2=x^3+Ax+B of order R
//      where R is large and prime > |P/K|. (K defaults to 256)
//      2#192-2#64-1
//      the commentary will make some sense to readers of IEEE P1363 Annex
//      nFreeware from Shamus Software, Dublin, Ireland
//      Full C++ source code and MIRACL multiprecision library available
//      Email to mscott@indigo.ie for details
//
//     gprime(10000);
    ip=0;
    k=256;
    suppress=FALSE;
    fout=FALSE;
	dir=FALSE;
	char *str=Eingabe.GetBuffer(100);//neu

	if (false==evaluate::CEvalIntExpr(t, str)) 
		return -1;

    p=t; 

	if (!prime(p))
    {

        int incr=0;
//		That number is not prime
		LoadString(AfxGetInstanceHandle(),IDS_STRING37100,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str);
		AfxMessageBox(line);
    
        {
//			Looking for next higher prime
            LoadString(AfxGetInstanceHandle(),IDS_STRING37106,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str);
			AfxMessageBox(line);
			p+=1; incr++;
            while (!prime(p)) { p+=1;  incr++; }
        }
    }
    if (p<1000000)
    {
//		Prime is too small - use another method
		LoadString(AfxGetInstanceHandle(),IDS_STRING37105,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str);
		AfxMessageBox(line);
        return -1;
    }
    if (bits(p)>258)
    {
//		Prime is too big
		LoadString(AfxGetInstanceHandle(),IDS_STRING37104,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str);
		AfxMessageBox(line);
        return -1;
    }
    rmin=(p-2*sqrt(p))/k;

    W=sqrt(p)+1;

    K=toint((W*W)/rmin);

    for (D=0;D<12000;D++)
    {
        if (!isaD(D,p%8,K)) continue;
        if (jacobi(p-D,p)==-1) continue;
        good=TRUE;
// A.14.2.3
        for (i=1;;i++)
        {
            int sp=mip->PRIMES[i];
            if (D==sp || sp*sp>D) break;
            if (D%sp==0 && jacobi(p,(Big)sp)==-1)
            {
                good=FALSE;
                break;
            }
        }
        if (!good) continue;
        if (!isacm(p,D,W,V)) continue;

        r=p+1+W;
		Disc=D;
        ord=trial_divide(r);
        if (ord>rmin && prime(ord))
		{
			get_curve(ofile,r,ord,D,p,W,saat);
			goto sprung;
		}
		
        r=p+1-W;
        ord=trial_divide(r);
        if (ord>rmin && prime(ord))
		{
			get_curve(ofile,r,ord,D,p,W,saat);
			goto sprung;
		}

        if (D==1)
        {
            r=p+1+V;
            ord=trial_divide(r);
            if (ord>rmin && prime(ord)) 
			{
				get_curve(ofile,r,ord,D,p,W,saat);
				goto sprung;
			}
            r=p+1-V;
            ord=trial_divide(r);
            if (ord>rmin && prime(ord))
			{
				get_curve(ofile,r,ord,D,p,W,saat);
				goto sprung;
			}
            
        }
        if (D==3)
        {
            r=p+1+(W+3*V)/2;
            ord=trial_divide(r);
            if (ord>rmin && prime(ord)) 
			{
				get_curve(ofile,r,ord,D,p,W,saat);
				goto sprung;
			}

            r=p+1-(W+3*V)/2;
            ord=trial_divide(r);
            if (ord>rmin && prime(ord))
			{
				get_curve(ofile,r,ord,D,p,W,saat);
				goto sprung;
			}

            r=p+1+(W-3*V)/2;
            ord=trial_divide(r);
            if (ord>rmin && prime(ord))
			{
				get_curve(ofile,r,ord,D,p,W,saat);
				goto sprung;
			}

            r=p+1-(W-3*V)/2;
            ord=trial_divide(r);
            if (ord>rmin && prime(ord))
			{
				get_curve(ofile,r,ord,D,p,W,saat);
				goto sprung;
			}
        }
    }
//	No satisfactory curve found
	LoadString(AfxGetInstanceHandle(),IDS_STRING37103,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(line,pc_str);
	AfxMessageBox(line);
	return -1;


sprung:
	return 0;

}

