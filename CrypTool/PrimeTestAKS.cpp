
#include <vector>
#include <math.h>
#include <time.h>


#include "PrimeTestAKS.h"
#include "PrimePolynom.h"

/*******************************************************
  Konstruktor erzeugt Zahl aus String.
 ******************************************************/
PrimeTestAKS::PrimeTestAKS()
{
  stopProcessing = 1;
  n = 0;
}

/*******************************************************
  Konstruktor erzeugt Zahl aus String.
 ******************************************************/
PrimeTestAKS::PrimeTestAKS(string s)
{
  stopProcessing = 1;
  n = s;
}

/*******************************************************
  Konstruktor erzeugt Zahl aus integer.
 ******************************************************/
PrimeTestAKS::PrimeTestAKS(int s)
{
  stopProcessing = 1;
  n = s;
}

/*******************************************************
  Konstruktor erzeugt Zahl aus integer.
 ******************************************************/
PrimeTestAKS::PrimeTestAKS(mpz_class s)
{
  stopProcessing = 1;
  n = s;
}

/*******************************************************
  Fuehrt den Primzahltest AKS auf n aus.

  Return: 1 = prime
          0 = not prime
 ******************************************************/
int PrimeTestAKS::aks()
{
  int size = (*this).loga();
  int lim1,lim2;
  int r,gcd;
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
  if ((*this).perf_pow() == 1)
  {
    return 0;
  }

  r=1;
  lim1 = 4*size^2;

  // ...
  do{
      r++;
      gcd = (*this).euclid(r);
      if( 1 < gcd && gcd < n)
      {
        return 0;
      }
      if(r >= n)
        return 1;
  }while (((*this).small_ord(r,lim1))  && (stopProcessing != 0));

  PrimePolynom::set_field(r);
  
  int sqrt_r = (*this).int_sqrt(r,2);
  lim2 = 2 * size * sqrt_r;
  v1[1] = 1;

  v2 = PrimePolynom::create_rhs();
  mpz_class val_0 = v2[0];

  // ... 
  for( int a = 1 ; (a <= lim1) && (stopProcessing != 0) ; a++)
  { 
    v1[0] = a;
    v2[0] = val_0 + a;
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
    if ((*this).is_int_sqrt(b))
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
    mpz_class help = (*this).pow(a,b);
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
    w = (*this).pow(a,b);
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
  Testet ob ord(n)<lim modulo r. Dabei werden die 
  Potenzen sukzessive durchgegangen, bis sie 1 sind
  oder lim ueberschreiten.
 ******************************************************/
int PrimeTestAKS::small_ord(int r, int lim)
{
  mpz_class n2 = n % r;
  mpz_class n3 = n2;
  int i = 0;
  while (n2 != 1 && i < lim)
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
