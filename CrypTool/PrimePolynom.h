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

#ifndef POLY_H
#define POLY_H

#include <vector>

#include "gmp.h"
#include "gmpxx.h"
//
using namespace std;

//typedef mpz_class INT; 

class PrimePolynom
{
  public:
  PrimePolynom();
  PrimePolynom(const std::vector<mpz_class>& v);
  mpz_class operator[](int pos);
  int operator==(const PrimePolynom& p);
  int operator!=(const PrimePolynom& p);
  PrimePolynom operator+(const PrimePolynom& p);
  PrimePolynom operator*(const PrimePolynom& p);
  PrimePolynom operator^(mpz_class b);
  PrimePolynom mod_pol(int r);
  int get_degree();
  static void set_m(const mpz_class& n);
  static void set_field(int r);
  static int get_field(void);
  static vector<mpz_class> create_rhs();
  int print();

  private:
  std::vector<mpz_class> vec;
  int degree;
  static int field;
  static mpz_class m;
  int ref_deg();

};
#endif