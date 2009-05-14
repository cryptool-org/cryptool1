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


#include <vector>
#include <math.h>
#include <time.h>

#include "PrimeTest.h"
#include "PrimePolynom.h"

/*******************************************************
  Konstruktor erzeugt Zahl aus String.
 ******************************************************/
PrimeTest::PrimeTest(string s)
{
  n = s;
}

/*******************************************************
  Konstruktor erzeugt Zahl aus integer.
 ******************************************************/
PrimeTest::PrimeTest(int s)
{
  n = s;
}




/*******************************************************
  Konstruktor erzeugt Zahl aus integer.
 ******************************************************/
PrimeTest::PrimeTest(mpz_class s)
{
  n = s;
}

/*******************************************************
  Waehlt abhaengig von alg einen der Primzahltests aus
  und stoppt die Ausfuehrungszeit, die in der Member-
  variablen test-time gespeichert wird.

  Return: 1 = prime
          0 = not prime
         -1 = error: wrong precision for solovay_strassen
         -2 = error: wrong algo
 ******************************************************/
int PrimeTest::test_n(int alg)
{
  clock_t   time1, time2;
  time_t    time_sek1,  time_sek2;
  int result = -1;
  switch (alg)
  {
     case 1: time_sek1 = time(NULL);
             time1 = clock();
             result = aks();
             time2 = clock();
             time_sek2 = time(NULL);
             test_time = ((double)time2 - (double)time1)/CLOCKS_PER_SEC;
             test_time_sek = difftime(time_sek2, time_sek1);
             break;
     case 2: time_sek1 = time(NULL);
             time1 = clock();
             result = solovay_strassen("99.99999999999999999999");
             time2 = clock();
             time_sek2 = time(NULL);
             test_time = ((double)time2 - (double)time1)/CLOCKS_PER_SEC;
             test_time_sek = difftime(time_sek2, time_sek1);
             break;
     case 3: time_sek1 = time(NULL);
             time1 = clock(); 
             result = sieve_era();
             time2 = clock();
             time_sek2 = time(NULL);
             test_time = ((double)time2 - (double)time1)/CLOCKS_PER_SEC;
             test_time_sek = difftime(time_sek2, time_sek1);
             break;
    default: 
             // wrong algo input parameter
             result = -2;
             break;
  }
  return result;
}

/*******************************************************
  Fuehrt den Primzahltest AKS auf n aus.

  Return: 1 = prime
          0 = not prime
 ******************************************************/
int PrimeTest::aks()
{
  int size = (*this).loga();
  int lim1,lim2;
  int r,gcd;
  std::vector<mpz_class> v1(2);
  std::vector<mpz_class> v2;
  std::vector<mpz_class>::iterator v2_it;
  PrimePolynom::set_m(n);

  // test ob n = a^b
  if ((*this).perf_pow() == 1)
  {
    return 0;
  }

  r=1;
  lim1 = 4*size^2;
  do{
      r++;
      gcd = (*this).euclid(r);
      if( 1 < gcd && gcd < n)
      {
        return 0;
      }
      if(r >= n)
        return 1;
  }while ((*this).small_ord(r,lim1));

 
  PrimePolynom::set_field(r);
  //bedienung::set_field(r);

  int sqrt_r = (*this).int_sqrt(r,2);
  lim2 = 2 * size * sqrt_r;
  v1[1] = 1;

  v2 = PrimePolynom::create_rhs();
  mpz_class val_0 = v2[0];

  for( int a = 1 ; a <= lim1 ; a++)
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
      // not prime
      return 0;
    }
  }

  // number n is prime
  return 1;
}

/*******************************************************
 Fuehrt den Solovay-Strassen Test aus, bis eine Wahr-
 scheinlichkein von per_s Prozent vorliegt, dass der 
 Test stimmt.
   Return: 1 = prime
           0 = not prime
          -1 = falsches format von per_s
 ******************************************************/
int PrimeTest::solovay_strassen(const string& per_s)
{ 
  int size = (int) ceil(3.321 * per_s.length());
  mpf_class per(per_s, size);

  if(n < 2)
  {
    return 0;
  }

  if(n == 2)
  {
    return 1;
  }

  if ((per >= 0) && (per<100))
  {
  
    mpf_class val(50.0,size+1);
    mpf_class res(50.0,size+1);
    int i = 1;
    bool sol = sol_stra_once();
    while ((per > res) && (sol == true))
    {
      sol = sol_stra_once();
      val = val/2;
      res = res + val ;
      i++;
    }

    if(sol)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return -1;
    //throw XPercent();
  }
  
}




/*******************************************************
  Testet nach dem Prinzip des Sieb des Eratosthenes
 ******************************************************/
int PrimeTest::sieve_era()
{
  mpz_class prod = 0;
  mpz_class j = 0;
  for(mpz_class i=2;i<n;i++)
  {
    for(j=1;j<n;j++)
    {
      prod = prod + i;
      if(prod == n)
      {
        return 0;
      }
      if(prod > n)
      {
        break;
      }
    }
    if(i>=j)
    {
      return 1;
    }
    prod = 0;
    j = 0;
  }
  return 1;
}


/*******************************************************
  Testet nach Miller-Rabin
  Verwendet die GMP-Lib
   Return: 2 = probably prime
           1 = prime
           0 = not prime
           
 ******************************************************/
int PrimeTest::miller_rabin()
{
  int erg = mpz_probab_prime_p (n.get_mpz_t(), 10);
  
  switch (erg)
  {
    case 1:
      return 2;
    break;
    case 2:
      return 1;
    break;
    default:
      return erg;
  }
}







/*******************************************************
 Berechnet das Jacobi-Symbol
 ******************************************************/
int PrimeTest::jacobi(mpz_class a, mpz_class b)
{
  int res = 1;
  mpz_class c,d;
  while(true)
  {
    if (a >= b)
    {
      a = a % b;
    }
    if (a == 0)
      return 0;
    while ( (a % 2) == 0)
    {
      a = a >> 1;
      c = b % 8; 
      if ( (c == 3)||(c == 5))
      {
        res = -res;
      }
    }
    if (a == 1)
      return res;
    c = a % 4;
    d = b % 4;
    if ((c == 3) && (d == 3))
        res = -res;
    c = a;
    a = b;
    b = c;
  }
  return 0;
}



/*******************************************************
  Testet ob a^b<=n ist. Falls ja wird a^b ausgegeben, 
  andernfalls wird n+1 ausgegeben.
  Es wird hoechstens so lange gerechnet bis die Ergebnisse
  n uebersteigen.
 ******************************************************/

mpz_class PrimeTest::pow(const mpz_class& a, int b)
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

mpz_class PrimeTest::pow(const mpz_class& a, const mpz_class& b)
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
  berechnet a^b mittels repeated squaring
 ******************************************************/

mpz_class PrimeTest::pow2(const mpz_class& a, const mpz_class& b)
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
      }
      s >>= 1;
      y = y*y;
   }
   
   return x;

}












/*******************************************************
  Es wird getestet ob n von der Form a^b mit a,b>1 ist.
  Dabei werden b=1,..,log n nacheinander getestet fuer
  verschiedene a's, die mittels Binaersuche bestimmt 
  werden. Dadurch ist die Laufzeit O((log n)^3). 
 ******************************************************/
int PrimeTest::perf_pow()
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
int PrimeTest::loga()
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
int PrimeTest::int_sqrt(int r,int b)
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
int PrimeTest::is_int_sqrt(int b)
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
int PrimeTest::euclid(int m)
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
int PrimeTest::small_ord(int r, int lim)
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

/*******************************************************
  Fuehrt eine Iteration des Solovay-Strassen Tests aus
  und gibt aus, ob demnach n eine Primzahl ist.
 ******************************************************/
bool PrimeTest::sol_stra_once()
{
  if (n == 1)
    return 1;
  mpz_class a = rand_mpz();
  int jac = jacobi(a,n);
  if (jac == 0)
  {
    return false;
  }
  mpz_class n_halbe = (mpz_class) (n -1)/2;
  mpz_class power = pow(a,n_halbe);
  if ((jac == power) || ((jac == -1) && (power == n-1)))
  {
    return true;
  }
  else 
  {
    return false;
  }
}

/*******************************************************
  Ermittelt eine Zufallszahl zwischen 1 und n-1.
  Wirft Exception XDatUrandom, falls der Zugriff auf Datei 
  "/dev/urandom" nicht funktioniert.
  Gibt n zurueck, falls n==1 oder n==0.
 ******************************************************/
mpz_class PrimeTest::rand_mpz()
{
  //unsigned long int randnum;
  mpz_class res = 0;
  unsigned int end = 0;
  int zuf;
  static unsigned long seed = 0;

  if(seed == 0)
    srand( (unsigned)time( NULL ) );
    seed = rand();
  if (n <= 1)
    return n;
  while((res == 0) && (end < mpz_get_ui(n.get_mpz_t())))
  {
    gmp_randclass rand(gmp_randinit_default);
    
    rand.seed(seed);
    res = rand.get_z_range(n);
    end++;
    if(res == 0)
      seed++;
    zuf = mpz_get_ui(res.get_mpz_t());
    //printf("rand: %i\n",mpz_get_ui(res.get_mpz_t()));
  }
  return res;
}