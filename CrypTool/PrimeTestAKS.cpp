
#include <vector>
#include <math.h>
#include <time.h>
#include <iostream>


#include "PrimeTestAKS.h"
#include "PrimePolynom.h"

/*******************************************************
  Konstruktor erzeugt Zahl aus String.
 ******************************************************/
PrimeTestAKS::PrimeTestAKS(int *cancel) : n(0), pcancelled(cancel), aks_index(0), aks_limit(0)
{
}

/*******************************************************
  Konstruktor erzeugt Zahl aus String.
 ******************************************************/
PrimeTestAKS::PrimeTestAKS(string s, int *cancel) : n(s), pcancelled(cancel), aks_index(0), aks_limit(0)
{
}

/*******************************************************
  Konstruktor erzeugt Zahl aus integer.
 ******************************************************/
PrimeTestAKS::PrimeTestAKS(int s, int *cancel) : n(s), pcancelled(cancel), aks_index(0), aks_limit(0)
{
}

/*******************************************************
  Konstruktor erzeugt Zahl aus integer.
 ******************************************************/
PrimeTestAKS::PrimeTestAKS(mpz_class s, int *cancel) : n(s), pcancelled(cancel), aks_index(0), aks_limit(0)
{
}

double PrimeTestAKS::getProgress()
{
	if (aks_limit == 0) { // first loop not yet finished
		return 0.0;
	} else { // second loop
		return double(aks_index) / double(aks_limit);
	}
}
/*******************************************************
  Fuehrt den Primzahltest AKS auf n aus.
  Basiert auf 
  [1] Agrawal, Kayal, Saxena, "PRIMES is in P", 2002, v6
      http://www.cse.iitk.ac.in/~manindra/algebra/primality_v6.pdf
  Bugfixes: Joerg Schneider

  Return: 1 = prime
          0 = not prime
	      2 = too large
	      3 = aborted
 ******************************************************/
int PrimeTestAKS::aks()
{
  int size = loga();
  int r; // r <= size^5 according to [1 p.3] =>  r will not overflow if size <= 73; overflow is checked below
  int gcd; // <= r
  int lim1 = 0; // lim1 = size^2  =>  will overflow if size > 46340; overflow checked below
  aks_limit = 0; // aks_limit = sqrt(r)*size <= size^3.5 <= r
  aks_index = 0;
  std::vector<mpz_class> v1(2);
  std::vector<mpz_class> v2;
  std::vector<mpz_class>::iterator v2_it;
  PrimePolynom::set_m(n);

  // test if n is < 2
  if(n < 2)
  {
    return 0;
  }

  // test ob n = a^b
  if (perf_pow())
  {
    return 0;
  }

  r=1;
  if (size > 46340) // size > sqrt(2^32-1)  =>  lim1 overflow?
  	return 2; 
  lim1 = size*size;

  // ...
  do{
      r++;
      if (r < 0) // overflow?
      	return 2; // this cannot happen if size <= 73; will take a *very* long time... 
      gcd = euclid(r);
      if( 1 < gcd && gcd < n)
      {
        return 0;
      }
      if(r >= n)
        return 1;
  }while (small_ord(r,lim1)  && !cancelled());
  PrimePolynom::set_field(r);
  int sqrt_r = int_sqrt(r-1,2); // should be sqrt(phi(r)) according to [1], larger value should not hurt
  aks_limit = size * sqrt_r;
  //std::cout << "r: " << r << " aks_limit: " << aks_limit << endl;
  v1[1] = 1;

  v2 = PrimePolynom::create_rhs();
  mpz_class val_0 = v2[0];

  //std::cout << "r=" << r << "\tlim1=" << lim1 << "\taks_limit=" << aks_limit << "\n";
  // ... 
  for( aks_index = 1 ; aks_index <= aks_limit && !cancelled() ; aks_index++)
  { 
    v1[0] = aks_index;
    v2[0] = val_0 + aks_index;
    if (v2[0] >= n)
      v2[0] -= n;
    PrimePolynom p1(v1);
    PrimePolynom p2(v2);
    p1 = p1^n;
    p2 = p2.mod_pol(r);
    if (p1 != p2)
    {
      return 0; // not prime
    }
  }
  if (cancelled())
	  return 3;
  return 1;     // number n is prime
}

/*******************************************************
  Testet ob a^b<=n ist. Falls ja wird a^b ausgegeben, 
  andernfalls wird n+1 ausgegeben.
  Es wird hoechstens so lange gerechnet bis die Ergebnisse
  n uebersteigen.
 ******************************************************/
mpz_class PrimeTestAKS::pow(const mpz_class& a, int b)
{
  mpz_class x , y;
  int s = b;
  x = 1;
  y = a;
   while (s >= 1 && x*y <= n)
   {
      if (s%2)
        {
           x = x * y;
        }
      s >>= 1;
      y = y*y;
   }

   if (s < 1)
   {
     return x;
   }
   else
   {
     return n+1;
   }
}

/*******************************************************
  berechnet a^b modulo n mittels repeated squaring
 ******************************************************/
mpz_class PrimeTestAKS::pow(const mpz_class& a, const mpz_class& b)
{
  mpz_class x , y;
  mpz_class s = b;
  signed long int odd;
  mpz_class s2;
  x = 1;
  y = a;
   while (s >= 1)
   {
     s2=s%2;
     odd = mpz_get_si(s2.get_mpz_t());
      if (odd)
      {
           x = x * y;
           if (x >= n)
           {
             x = x % n;
           }
      }
      s >>= 1;
      y = y*y;
      if(y >= n)
      {
        y = y % n;
      }
   }
   return x;
}

/*******************************************************
  Es wird getestet ob n von der Form a^b mit a,b>1 ist.
  Dabei werden b=1,..,log n nacheinander getestet fuer
  verschiedene a's, die mittels Binaersuche bestimmt 
  werden. Dadurch ist die Laufzeit O((log n)^3). 
 ******************************************************/
int PrimeTestAKS::perf_pow()
{
  int b = 2;
  mpz_class c = 1;
  while (c <= n)
  {
    if (is_int_sqrt(b))
      return 1;
    b++;
    c <<= 1;
  }
  return 0;
}

/*******************************************************
 Berechnet den Logarithmus einer Zahl, nach oben 
 gerundet
 ******************************************************/
int PrimeTestAKS::loga()
{
  mpz_class n2 = n;
  int res = 0;
  bool flag = 1;
  while (n2 != 0)
  {
    if (flag == 1 && (n2 != 1) && (n2 % 2) == 1)
      flag = 0;
      
    n2 = n2 >> 1;
    res = res + 1;
  }
  if (flag == 1)
    res = res - 1;
  return res;
}

/*******************************************************
  Berechnet den ganzzahligen Anteil der b'ten Wurzel
  von n mittels binaerer Suche. Liegt in O(log n);
 ******************************************************/
int PrimeTestAKS::int_sqrt(int r,int b)
{
  int u = 1;
  int v = r;
  int a,w;

  while (v-u >= 2)
  {
    a = (u+v)>>1;
    mpz_class help = pow(a,b);
    w = mpz_get_si(help.get_mpz_t());
    if (w == r) 
    {
      return a;
    }
    else if (w < r)
    {
      u = a;
    }
    else
    {
      v = a;
    }
  }
  return v;
}

/*******************************************************
  Bestimmt ob n eine ganzzahlige b`te Wurzel hat mittels 
  binaerer Suche. Liegt in O(log n);
 ******************************************************/
int PrimeTestAKS::is_int_sqrt(int b)
{
  mpz_class u = 1;
  mpz_class v = n;
  mpz_class a,w;

  while (v-u >= 2)
  {
    a = (u+v)>>1;
    w = pow(a,b);
    if (w == n) 
    {
      return 1;
    }
    else if (w < n)
    {
      u = a;
    }
    else
    {
      v = a;
    }
  }
  return 0;
}

/*******************************************************
  Ermittelt den ggt von n und m mittels des einfachen
  euklidischen Algorithmus.
 ******************************************************/
int PrimeTestAKS::euclid(int m)
{
  mpz_class n2 = n % m;

  int r = mpz_get_si(n2.get_mpz_t());

  int n3;
  while (r != 0)
  {
    n3 = m;
    m = r;
    r = n3 % m;
  }
  return m;
}

/*******************************************************
  Testet ob ord(n)<=lim modulo r. Dabei werden die 
  Potenzen sukzessive durchgegangen, bis sie 1 sind
  oder lim ueberschreiten.
 ******************************************************/
int PrimeTestAKS::small_ord(int r, int lim)
{
  // ord_r(n) <= r-1
  if (r-1 <= lim)
  	return 1;
  mpz_class n2 = n % r;
  mpz_class n3 = n2;
  int i = 1;
  while (n2 != 1 && i <= lim)
  { 
    n2 = (n3*n2) % r;
    i++;
  }
  if (n2 == 1)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

#if 0

#include <iostream>
#include "PrimeTestAKS.h"

using namespace std;

int isprime(int n)
{
	for (int i = 2; i*i <=n; i++)
		if (n % i == 0)
			return 0;
	return 1;
}
int main(int argc, char *argv[])
{
	mpz_class a(argv[1]);
	mpz_class b(argc == 3 ? argv[2] : argv[1]);
	for (mpz_class n = a; n <= b; n++) {
		int prime = n.fits_sint_p() ? isprime(n.get_si()) : 2;
		PrimeTestAKS aks(n);
		int primeaks = aks.aks();
		//if (n % 100 == 0)
			cerr << n << "\r";
		cerr.flush();
		if (prime != primeaks) 
			cerr << n << "\tprime: " << prime << "\taks: " << primeaks << endl;
	}
	return 0;

}

#endif
