// Primes_and_random_numbers.cpp: Implementierung der Klasse Primes_and_random_numbers.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Primes_and_random_numbers.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Primes_and_random_numbers::Primes_and_random_numbers()
{

}

Primes_and_random_numbers::~Primes_and_random_numbers()
{

}

bool Primes_and_random_numbers::Prime_test_Solovay_Strassen(long n, long t)

		// Solovay-Strassen-Test, gibt true zurück, wenn n Primzahl ist
{
	for(int i=1;i<=t;i++)
	{
		long a=Random_with_limits(2,n-2);
		long r=long(zz.powermod(unsigned long(a),unsigned long((n-1)/2),unsigned long(n)));
		if((1!=r)&&((n-1)!=r))
		{
			return(false);
		}
		long s=jacobi(a,n);
		if(s<0)
		{
			s=n-1;				// Achtung für negative Zahlen ist der Operator "%" kein Modulo !
		}						
		if((s%n)!=r)
		{
			return(false);
		}
	}
	return(true);
}

bool Primes_and_random_numbers::Prime_test_Miller_Rabin(long n, long t)		

		// Miller-Rabin-Test, gibt true zurück, wenn n Primzahl ist
{
	long i,j;
	if(2==n)
	{
		return true;
	}
	long v=0,w=n-1;
	while(0==w%2)
	{
		v++;
		w/=2;
	}
	for(j=1;j<=t;)
	{
		long a=Random_with_limits(1,n-1);
		long b=long(zz.powermod(unsigned long(a),unsigned long(w),unsigned long(n)));
		if((1==b)||((n-1)==b))
		{
			goto nextj;
		}
		for(i=1;i<=v-1;)
		{
			b=long(zz.powermod(unsigned long(b),2,unsigned long(n)));
			if((n-1)==b)
			{
				goto nextj;
			}
			if(1==b)
			{
				return false;
			}
			i++;
		}
		return false;
nextj: j++;
	}
	return true;
}

long Primes_and_random_numbers::Random_with_limits(long lower, long upper)
	
		// erzeugt eine Zufallszahl rand_val, wobei gilt: lower <= rand_val <= upper
{
	long rand_val=zz.zzgen4();
	rand_val*=256;
	rand_val+=zz.zzgen4();
	rand_val*=256;
	rand_val+=zz.zzgen4();
	rand_val*=128;
	rand_val+=((zz.zzgen4()-1)/2);
	rand_val%=(upper-lower+1);
	return(rand_val+lower);
}

long Primes_and_random_numbers::jacobi(long a, long n)

// jacobi.cpp : Definiert den Einsprungpunkt für die Konsolenanwendung.
// ========================================================
// Henrik Koy Januar 2000
//
//               / a \
// Jacobisymbol | --- | berechnen
//               \ n /
//
// INPUT:  n >= 0 ungerade, a ganzzahlig
//
// OUTPUT: Jacobisymbol "a über n"
//         Aussage über die nicht Lösbarkeit der Kongruenz
//
//         x^2 = a mod n
//
//         (nicht Lösbar, falls jacobi(a,n) = -1)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Quelle: Johannes Blömer, Skript zur Vorlesung
//         Algorithmen in der Zahlentheorie (WS 1997/98)
//         Seite 27-33.
//
//         Siehe www.mi.informatik.uni-frankfurt.de
//         Link über "Vorlesungen"
// ---------------------------------------------------------
{
   // FEHLER SITUATIONEN
   if((n<0)||(0==n%2))
   {  // hier kann evtl. eine Fehlerbehandlung implementiert
      // Werden: Das Jacobisymbol ist für diese Eingaben nicht
      // definiert !
      return(0);
   }
   long t=1;
   if(a<0)
   {
      if(1==((n-1)/2)%2) 
	  {
		  t=-1;
	  }
	  a=-a;
   }
   while(0!=a)
   {
      while(0==(a%2))
      {
          //  jacobi(2,n) heraus Multiplizieren!
          //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          //  jacobi(2,n) = -1 <==> n == {3,5} mod 8
          //  (Siehe Satz 5.5 im Blömer Skript
          a>>=1;
          if((3==n%8)||(5==n%8))
		  {
             t=-t;
		  }
      }
      // jetzt sind a und n ungerade! Es gilt
      // jacobi(a,n) == jacobi(n,a) ausser
      // n == 3 mod 4 und a == 3 mod 4 (Satz 5.5 Skript)
      if((3==n%4)&&(3==a%4))
	  {
         t=-t;
	  }
      long b=a;
	  a=n%b;
	  n=b; // ggt - Schritt
   }
   if(1==n)
   {
	   return(t);
   }
   return 0;
}

bool Primes_and_random_numbers::Prime_test_Fermat(long n, long t)
{
	for(int i=1;i<=t;i++)
	{
		long a=Random_with_limits(2,n-2);
		long r=zz.powermod(long(a),long(n-1),long(n));
		if(1!=r)
		{
			return(false);
		}
	}
	return(true);
}
