// Primes_and_random_numbers.cpp: Implementierung der Klasse Primes_and_random_numbers.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Primes_and_random_numbers.h"
#include "eval.h"

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
//	delete []str;
}

//================================================================================================
/*
bool Primes_and_random_numbers::Prime_test_Solovay_Strassen(Big n, long t)

		// Solovay-Strassen-Test, gibt true zurück, wenn n Primzahl ist
{
	for(int i=1;i<=t;i++)
	{
		Big a=Random_with_limits(2,n-2);
		Big r=square_und_multiply(a,(n-1)/2,n);
		if((1!=r)&&((n-1)!=r))
		{
			return(false);
		}
		Big s=jacobi(a,n);
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

//==================================================================================================
bool Primes_and_random_numbers::Prime_test_Miller_Rabin(Big n, long t)		

		// Miller-Rabin-Test, gibt true zurück, wenn n Primzahl ist
{
	long i;
	long j;
	if(2==n)
	{
		return true;
	}
	long v=0;
	Big w=n-1;
	while(0==w%2)
	{
		v++;
		w/=2;
	}
	for(j=1;j<=t;)
	{
		Big a=Random_with_limits(1,n-1);
		Big b=square_und_multiply(a,w,n);
		if((1==b)||((n-1)==b))
		{
			goto nextj;
		}
		for(i=1;i<=v-1;)
		{
			b=square_und_multiply(b,2,n);
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

//===============================================================================================
Big Primes_and_random_numbers::Random_with_limits(Big lower, Big upper)
	
		// erzeugt eine Zufallszahl rand_val, wobei gilt: lower < rand_val < upper
{
	Big ausgabe;
	ausgabe=1;
	// erzeugt eine Zufallszahl rand_val, wobei gilt: lower < rand_val < upper
	irand(123456789); // Einstellbar!
	ausgabe=rand(upper-lower+1)+lower-1;
	return ausgabe;

}


//================================================================================================
Big Primes_and_random_numbers::jacobi(Big a, Big n)

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
   Big t=1;
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
      Big b=a;
	  a=n%b;
	  n=b; // ggt - Schritt
   }
   if(1==n)
   {
	   return(t);
   }
   return 0;
}

//===================================================================================================
bool Primes_and_random_numbers::Prime_test_Fermat(Big n, long t)

		// Fermat-Test, gibt true zurück, wenn n Primzahl ist
{
	for(int i=1;i<=t;i++)
	{
		Big a=Random_with_limits(2,n-2);
		Big r=square_und_multiply(a,n-1,n);
		if(1!=r)
		{
			return(false);
		}
	}
	return(true);
}

//====================================================================================================
Big Primes_and_random_numbers::square_und_multiply(Big x, Big b, Big n)
{//BERECHNET X^B MOD N
	long i;
	Big z=1;
	Big *b_i;
	
	//b_i=(Big *) calloc(1700,sizeof(Big)); 
	b_i = new Big[1700];	
	//In b_i[0] sollte die Länge des Vektors gespeichert werden. 

	long temp=Bitlaenge(b,b_i);
	
	for (i=temp;i>=0;i--)
	{
		z =(z*z)%n;
		if (b_i[i]==1)
		{
			z=(z*x)%n;
		}
	}
	//b_i[0]=temp-1;
	delete [] b_i;
	return z;

}

//=========================================================================================
long Primes_and_random_numbers::Bitlaenge(Big x,Big *bi)
{
	Big temp=0;
		
	if (x==0)
	{
		bi[0]=temp;
		return 0;
	//	bi[1]=temp;
	}
	if (x<0) 
	{
		x=-x;
		return 0; //noch bearbeiten
	}
	
	//Vorsicht : es fehlte noch die binäre Dartstellung von negative Zahlen.
	long l=0;
	//bi[0]=0;
	//bi[1]=1;
	while (x!=1)
	{
		bi[l]=x%2;
		x=x/2;
		l=l+1;
	}
	//bi[0]=temp+1;
	bi[l]=temp+1;
	return l;

}

*/


Big Primes_and_random_numbers::extended_euclidian_algorithm(Big n, Big e)
{
	Big ausgabe;
	if (e==0)
	{
	
		ausgabe=-1;
		return ausgabe;// 0 besitzt keine Inverse modulo n
	}

	Big n0=n;
	Big e0=e;
	Big t0=0;
	Big t=1;
	Big q= (n0 / e0);
	Big r=n0-q*e0;
	while (r>0)
	{
		Big temp= t0 -q*t;
		if (temp>=0)
		{
			temp=temp%n;
		}
		if (temp<0) 
		{
			temp = n -((-temp) % n);
		}
		t0=t;
		t=temp;
		n0=e0;
		e0=r;
		q=n0/e0;
		r=n0 - q*e0;
	}
	if (e0!=1)
	{// e hat keine Inverse
	
		ausgabe=-1;
		return ausgabe;
	}
	ausgabe=t%n;
	return ausgabe;
}

Big Primes_and_random_numbers::square_und_multiply(Big x, Big b, Big n)
{//BERECHNET X^B MOD N
	
	
	ZZn X,Y;
	modulo(n);
	X= (ZZn) x;
	Y =pow(X,b);
	Big ausgabe;
	ausgabe= (Big) Y;
	return ausgabe;

 
	/*
	long i;
	Big z=1;
	Big *b_i;
	
	//b_i=(Big *) calloc(256,sizeof(Big)); 
	b_i = new Big[256];	
	//In b_i[0] sollte die Länge des Vektors gespeichert werden. 

	long temp=Bitlaenge(b,b_i);
	
	for (i=temp;i>=0;i--)
	{
		z =(z*z)%n;
		if (b_i[i]==1)
		{
			z=(z*x)%n;
		}
	}
	//b_i[0]=temp-1;
	delete [] b_i;
	return z;
	*/
}
// Eigentlich könnte man auch die Funktion Bitlaenge löschen: sollte nur achten, daß dies nicht mehr verwendet wird!!!!

long Primes_and_random_numbers::Bitlaenge(Big x,Big *bi)
{
	Big temp=0;
		
	if (x==0)
	{
		bi[0]=temp;
		return 0;
	//	bi[1]=temp;
	}
	if (x<0) 
	{
		x=-x;
		return 0; //noch bearbeiten
	}
	
	//Vorsicht : es fehlte noch die binäre Dartstellung von negative Zahlen.
	long l=0;
	//bi[0]=0;
	//bi[1]=1;
	while (x!=1)
	{
		bi[l]=x%2;
		x=x/2;
		l=l+1;
	}
	//bi[0]=temp+1;
	bi[l]=temp+1;
	return l;

}

Big Primes_and_random_numbers::random_with_limits(Big upper)
{
	Big ausgabe;
	ausgabe=1;
	// erzeugt eine Zufallszahl rand_val, wobei gilt: 1< rand_val < upper
	//irand(123456789); // Einstellbar!
	ausgabe=rand(upper);
	return ausgabe;

}


Big Primes_and_random_numbers::erzeuge_oeffentliche_Schluessel_e(Big phi_pq)
{
	Big eingabe;
	eingabe=phi_pq;
	Big z;
	CString schwer;
	schwer= konvertiere_Big_CString(eingabe);
	Big ausgabe;
	if (eingabe >2)
	{
		z=random_with_limits(eingabe);
		schwer= konvertiere_Big_CString(z);
		while (1!=ggT(z,eingabe))
		{
			z=random_with_limits(eingabe);
			schwer= konvertiere_Big_CString(z);
		}
		ausgabe=z;
		return ausgabe;
	}
	else 
	{
		ausgabe=-1;
		return ausgabe; //keine solche Zahl existiert!		
	}
}


Big Primes_and_random_numbers::ggT(Big a, Big b)
{
	Big temp;

	if (a==0) return b;
	else if (b==0) return a;
	else if (a==b) return a;
	else if (a<b) 
	{
		while (b!=0)
		{
			temp=a;
			a=b;
			b=temp%b;
		}
		return a;
	}
	else
	{
		while (a!=0)
		{
			temp=b;
			b=a;
			a=temp%a;
		}
		return b;
	}
}


long Primes_and_random_numbers::RSA_BlockLaengeBerechnung(Big x, long a)
{
	//x ist der RSA-Modul x=p*q; a ist die Anzahl der benutzten Zeichen.
	if (x==0)
	{
		//???
	}
	if (x<0) 
	{
		x=-x;
	}
	
	//Vorsicht : es fehlte noch die a-adische Dartstellung von negative Zahlen.
	long l=1;

//	Big a_big;
//	lgconv(a,a_big);

	while (x>a)
	{
		x=x/a;
		l=l+1;
	}

	//was ist wenn blocklänge =0 ist?
	return (l-1);
}

Big Primes_and_random_numbers::potenz(Big x, Big n)
{
	Big z=1;

	if (x==0 && n==0) return z;
	if (x==0 && n!=0) return (z-1);
	if (x!=0 && n==0) return z;
	do 
	{
		z=z*x;
		n=n-1;
	}
	while (n!=0);
	return z;
}

void Primes_and_random_numbers::encrypt_block(Big *Block, long blocklaenge,long anzahl_buchstaben, Big ausgabe,Big n, Big e)
{
	// n =pq ist das RSA-Modul
	// e ist RSA öffentliche Schluessel
	long i;
	ausgabe=0;
	Big anzahl_buchstaben_big;
//	lgconv(anzahl_buchstaben, anzahl_buchstaben_big);
	// Block als Zahl (ausgabe) < RSA-Modul darstellen:
	for (i=blocklaenge-1;i>=0;i--)
	{
		ausgabe=ausgabe+Block[i]*potenz(anzahl_buchstaben,blocklaenge-1-i);
		char ausgabe_char[100];
		ausgabe_char<<ausgabe;
	}

	char ausgabe_char[100];
	ausgabe_char<<ausgabe;
	//Ergebnis-Zahl verschluesseln: ausgabe^e mod n=ausgabe
	ausgabe=square_und_multiply(ausgabe, e,n);
	
	ausgabe_char<<ausgabe;
	// Ergebnis-Zahl ausgabe wieder als Block darstellen
	/*
	i=blocklaenge-1;
	Big temp;
	do
	{
		temp=ausgabe;
		Block[i]=ausgabe%anzahl_buchstaben;
		ausgabe_char<<ausgabe;
		ausgabe_char<<Block[i];
		ausgabe=ausgabe/anzahl_buchstaben;
		ausgabe_char<<ausgabe;
		i=i-1;
	}while (ausgabe>=anzahl_buchstaben && i >=1);
	if (i!=0)
	{
		Block[i]=ausgabe;
		ausgabe_char<<Block[i];
		for (j=i-1;j>=0;j--)
		{
			Block[j]=0;
			ausgabe_char<<Block[i];
		}
	}
	*/
	Block[0]=ausgabe;
	ausgabe_char<<Block[0];
}


Big Primes_and_random_numbers::konvertiere_CString_Big(CString Eingabe)
{

	
	char *str=Eingabe.GetBuffer(250);
	
	if (false==evaluateFormula::eval(t, str)) 
		return -1;//
	ausgabe=t;//
	
	return t;
	
}

CString Primes_and_random_numbers::konvertiere_Big_CString(Big Eingabe)
{
	CString ausgabe;
	
	ausgabe.GetBuffer(500) << Eingabe;
	
	return ausgabe;
}

////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////

//================================================================================================
bool Primes_and_random_numbers::Prime_test_Solovay_Strassen(Big n, long t)

		// Solovay-Strassen-Test, gibt true zurück, wenn n Primzahl ist
{
	Big a;
	Big r;
	Big s;
	for(int i=1;i<=t;i++)
	{
		a=Random_with_limits(2,n-2);
		r=square_und_multiply(a,(n-1)/2,n);
		if((1!=r)&&((n-1)!=r))
		{
			return(false);
		}
		s=jacobi(a,n);
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

//==================================================================================================
bool Primes_and_random_numbers::Prime_test_Miller_Rabin(Big n, long t)		

		// Miller-Rabin-Test, gibt true zurück, wenn n Primzahl ist
{
	long i;
	long j;
	Big a;
	Big b;
	if(2==n)
	{
		return true;
	}
	long v=0;
	Big w=n-1;
	while(0==w%2)
	{
		v++;
		w/=2;
	}
	for(j=1;j<=t;)
	{
		a=Random_with_limits(1,n-1);
		b=square_und_multiply(a,w,n);
		if((1==b)||((n-1)==b))
		{
			goto nextj;
		}
		for(i=1;i<=v-1;)
		{
			b=square_und_multiply(b,2,n);
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

//===============================================================================================
Big Primes_and_random_numbers::Random_with_limits(Big lower, Big upper)
	
		// erzeugt eine Zufallszahl rand_val, wobei gilt: lower < rand_val < upper
{
	Big ausgabe;
	ausgabe=1;
	// erzeugt eine Zufallszahl rand_val, wobei gilt: lower < rand_val < upper
	//irand(123456789); // Einstellbar!
	ausgabe=rand(upper-lower+1)+lower-1;
	return ausgabe;

}


//================================================================================================
Big Primes_and_random_numbers::jacobi(Big a, Big n)

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
   Big t=1;
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
      Big b=a;
	  a=n%b;
	  n=b; // ggt - Schritt
   }
   if(1==n)
   {
	   return(t);
   }
   return 0;
}

//===================================================================================================
bool Primes_and_random_numbers::Prime_test_Fermat(Big n, long t)

		// Fermat-Test, gibt true zurück, wenn n Primzahl ist
{
	Big a;
	Big r;
	for(int i=1;i<=t;i++)
	{
		a=Random_with_limits(2,n-2);
		r=square_und_multiply(a,n-1,n);
		if(1!=r)
		{
			return(false);
		}
	}
	return(true);
}
