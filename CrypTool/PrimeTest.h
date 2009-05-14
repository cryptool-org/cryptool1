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

#ifndef PRIM_H
#define PRIM_H

#include <stdio.h>

#include <gmp.h>
#include "gmpxx.h"

#include "PrimePolynom.h"

class PrimeTest
{
  public:
  
    // supported algorithms
    static enum Algo { AKS=1, SOLOVAY_STRASSEN=2, ERATOSTENES=3 };

    mpz_class n;
    double test_time;
    double test_time_sek;
    
    // constructors
    PrimeTest(string s);
    PrimeTest(mpz_class s);
    PrimeTest(int s);
    
    bool test_while();
    static mpz_class pow2(const mpz_class& a, const mpz_class& b);
    int test_n(int alg);
    int loga();

    int solovay_strassen(const string& per_s);
    int sieve_era();
    int aks();
    int miller_rabin();

  private:
    mpz_class pow(const mpz_class& a, int b);
    mpz_class pow(const mpz_class& a, const mpz_class& b);
    int perf_pow();
    int is_int_sqrt(int b);
    int int_sqrt(int r, int b);
    int euclid(int m);
    int small_ord(int r, int lim);
    bool sol_stra_once();
    mpz_class rand_mpz();
    long int times(const mpf_class& per, int size);
    int jacobi(mpz_class a, mpz_class b);


};
#endif