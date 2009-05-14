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

#include "PrimePolynom.h"
#include <vector>
#include <stdio.h>
#include <iostream>
#include "gmp.h"
// #include "gmpxx.h"





/*********************************************
 Bestimmen den Ring aus dem das Polynom 
 stammt: Z_n[x]/(x^field-1).
**********************************************/
mpz_class PrimePolynom::m = 0;
int PrimePolynom::field = 0;


void PrimePolynom::set_m(const mpz_class& n)
{
  m = n;
}

void PrimePolynom::set_field(int r)
{
  field = r;
}

int PrimePolynom::get_field(void)
{
  return field;
}


/*********************************************
  bildet leeres Polynom, degree wird negativ
  gesetzt
**********************************************/
PrimePolynom::PrimePolynom()
{
  degree = -1;
}





/*********************************************
  bildet Polynom aus Vektor v, der degree
  des Polynoms wird entsprechend dem Vektor
  gesetzt.
**********************************************/
PrimePolynom::PrimePolynom(const std::vector<mpz_class>& v)
{
  vec = v;
  degree = (*this).ref_deg();
}






/*********************************************
  aktualisiert den degree mit dem eingegebenen
  Vektor
**********************************************/
int PrimePolynom::ref_deg()
{
  int i = (int)(vec.size()-1);
  vector<mpz_class>::reverse_iterator vec_it = vec.rbegin();
  for(vec_it; vec_it!=vec.rend(); vec_it++)
  {
    if (*vec_it != 0)
    {
      degree = i;
      return i;
    }
    i--;
  }
  return 0;
}





/*********************************************
  Rueckgabe des degrees
**********************************************/
int PrimePolynom::get_degree()
{
  return degree;
}




/*********************************************
  gibt Koeffizient vom von x^pos zurueck   				      
**********************************************/
mpz_class PrimePolynom::operator[](int pos)
{
  if(pos < vec.size())
  {
    return vec[pos];
  }
  else
  {
    return -1;
  }
}



/*********************************************
  Test auf Gleichheit
**********************************************/
int PrimePolynom::operator==(const PrimePolynom& p)
{
  if ((degree == p.degree) && (vec == p.vec))
    {
      return 1;
    }
  else
  {
    return 0;
  }
}



/*********************************************
  Test auf Ungleichheit
**********************************************/
int PrimePolynom::operator!=(const PrimePolynom& p)
{
  if ((*this) == p)
    return 0;
  else
    return 1;
    
}





/*********************************************
  Komponentenweise Addition von zwei Polynomen
  Der degree wird entsprechend gesetzt.
**********************************************/
PrimePolynom PrimePolynom::operator+(const PrimePolynom& p)
{
  PrimePolynom res;
  mpz_class coef;
  vector<mpz_class>::iterator vec_it = vec.begin();
  vector<mpz_class>::const_iterator p_vec_it = p.vec.begin();
  for(vec_it; vec_it != vec.end(); vec_it++)
  {
    if (p_vec_it != p.vec.end())
    {
      coef = (*vec_it) + (*p_vec_it);
      if (m != 0  && coef >= m)
        coef = coef - m;
      res.vec.push_back(coef);
      p_vec_it++;
    }
    else
    {
      res.vec.push_back(*vec_it);
    }
  }
  for(p_vec_it; p_vec_it != p.vec.end(); p_vec_it++)
  {
    res.vec.push_back(*p_vec_it); 
  }
  res.ref_deg();
  return res;
}




/*********************************************
  triviale Multiplikation von zwei Polynomen
  der degree wird entsprechend gesetzt.
**********************************************/
/*polynom polynom::operator*(const polynom& p)
{
  polynom res;
  mpz_class coef;
  vector<mpz_class>::iterator vec_it = vec.begin();
  vector<mpz_class>::const_iterator p_vec_it = p.vec.begin();
  int i = 0;
  for(vec_it; vec_it != vec.end(); vec_it++)
  {
    if(*vec_it != 0)
    {      
      
      vector<mpz_class> help_v(i);
      for(p_vec_it; p_vec_it != p.vec.end(); p_vec_it++)
	{
	  coef = *vec_it**p_vec_it;
	  if (m != 0 && coef >= m)
	    coef = coef % m;
	  help_v.push_back(coef);
	}
      polynom help_p(help_v);
      res = res + help_p;
      p_vec_it = p.vec.begin();
    }
    i++;
  }
  res.ref_deg();
  return res;
}
*/


/*********************************************
 Polynommultiplikation mittes binaerer 
 Segmentierung
**********************************************/
PrimePolynom PrimePolynom::operator*(const PrimePolynom& p)
{
  mpz_class coef;
  int b;
  vector<mpz_class>::iterator vec_it = vec.begin();
  vector<mpz_class>::const_iterator p_vec_it = p.vec.begin();
  mpz_class maximum;
  mpz_class max_x = 0;
  mpz_class max_y = 0;
  vector<mpz_class> help_v(0);

  
  for(vec_it; vec_it != vec.end(); vec_it++)
  {
    if (*vec_it > max_x)
    {
      max_x = *vec_it;
    }
  }
  for(p_vec_it; p_vec_it != p.vec.end(); p_vec_it++)
  {
    if (*p_vec_it > max_y)
    {
      max_y = *p_vec_it;
    }
  }

  maximum = max_x * max_y;

  if(p.degree > degree)
  {
    maximum = (p.degree + 1) * maximum;
  }
  else
  {
    maximum = (degree + 1) * maximum;
  }
  

  b = mpz_sizeinbase(maximum.get_mpz_t(),2);


  mpz_class X = 0;
  mpz_class Y = 0;
  mpz_class u; 
  
  
  vec_it = vec.begin();
  int sh = 0;
  mpz_class plus = 0;
  for(vec_it; vec_it != vec.end(); vec_it++)
  {
    plus = *vec_it << sh;
    X = X + plus;
    sh = sh + b;
  }
  
  p_vec_it = p.vec.begin();
  sh = 0;
  for(p_vec_it; p_vec_it != p.vec.end(); p_vec_it++)
  {
    plus = *p_vec_it << sh;
    Y = Y + plus;
    sh = sh + b;
  }

  u = X*Y;


  mpz_class pot_b = 1;
  pot_b = pot_b << b;
  for(int l = 0 ; l < p.degree + degree + 1; l++)
  {
    coef = u % pot_b;
    if (m != 0 && coef >= m)
      coef = coef % m;
    help_v.push_back(coef);
    u = u >> b;
  }
  
  PrimePolynom res(help_v);
  res.ref_deg();
  return res;
  
}




/*********************************************
  Das Polynom wird mir b potenziert. Da dafuer
  * benutzt wird, wird automatisch modulo m
  gerechnet. Ausserdem wird modulo (x^field - 1)
  gerechnet.
**********************************************/
PrimePolynom PrimePolynom::operator^(mpz_class b)
{
  vector<mpz_class> v(1);
  v[0]=1;
  PrimePolynom res(v),p(vec);
    while (b >= 1)
    {
      if ((b % 2)==1)
        {
           res = res * p;
        }
      b >>= 1;
      p = p*p;
      if (field != 0 && p.degree >= field)
      {
        p = p.mod_pol(field);
      }
      if (field != 0 && res.degree >= field)
      {
        res = res.mod_pol(field);
      }
    }
  return res;
}



/*********************************************
  Das Polynom wird modulo x^r-1 genommen.
  Die Koeffizienten sind dabei aus Z/nZ
**********************************************/
PrimePolynom PrimePolynom::mod_pol(int r)
{
  PrimePolynom res(vec);
  int a = degree - r;
  
	// flomar and Joerg Schneider, 12/18/2008: bug fix
	// if the degree of our polynom (degree) is smaller than the degree of the 
	// divisor polynom (r), we should directly return; proceeding regardless 
	// of the difference in degrees leads to an invalid vector and thus 
	// to a program crash (at least under Vista)
	if(degree < r) {
		return res;
	}

  vector<mpz_class>::reverse_iterator vec_it = res.vec.rbegin();

  /*vec_it2 zeigt auf x^(degree-r), die zweite Stelle von der abgezogen *
   *werden muss                                                         */ 
  vector<mpz_class>::reverse_iterator vec_it2 = res.vec.rbegin()+r;

  for(a; a>=0; a--)
  {
    *vec_it2 = *vec_it2 + *vec_it;
    if(m != 0 && *vec_it2 >= m)
      *vec_it2 = *vec_it2 - m;
    *vec_it = 0;
    vec_it ++;
    vec_it2++;
  }
  res.ref_deg();
  vector<mpz_class>::iterator it_beg = res.vec.begin()+res.degree+1;
  vector<mpz_class>::iterator it_end = res.vec.end();
  res.vec.erase(it_beg ,it_end);
  return res;
}






/*********************************************
  Erster Teil der Bestimmung der rechten Seite 
  der Kongruenzauswertung: x^n mod x^r-1
**********************************************/
vector<mpz_class> PrimePolynom::create_rhs()
{
  std::vector<mpz_class> res;
  mpz_class exp = m;
  int exp2;
  mpz_class coef = 1;
  mpz_class val;
  while (exp >= field)
  {
    exp = exp % field;
      
    if (res.size() > exp)
    {
      val = coef;
      exp2 = mpz_get_ui(exp.get_mpz_t());
      val += res[exp2];
      if (val == (m - 1))
        val = 0;
      res[exp2] = val;
    }
    else
    {
      while (res.size() < exp)
      {
        res.push_back(0);
      }
      res.push_back(coef);
    }
    exp = exp / field;
    coef = m - coef;
  }
  return res;
}









/*********************************************
  Ausgabe eines Polynoms auf dem Bildschirm
**********************************************/
int PrimePolynom::print()
{
  //cout << degree<<endl;
  //cout << vec.size()<<endl;
  vector<mpz_class>::iterator vec_it = vec.begin();
  int i = 0;
  int plus = 0;
  for(vec_it; vec_it != vec.end(); vec_it++)
  {
    
    if(*vec_it != 0)
    {
      if (plus != 0)
      {
        //cout << " +";
        plus = 0;
      }
      gmp_printf(" %Zd", (*vec_it).mpz_class::get_mpz_t ());
      plus = 1;
      if (i == 0);
      else if (i == 1)
      {
        std::cout << "x";
      }
      else 
      {
        std::cout << "x^" << i ;
      }
    }
    i++;
  }
  cout << endl;

  return 0;
}

