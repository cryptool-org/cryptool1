#ifndef PRIM_AKS_H
#define PRIM_AKS_H

#include <stdio.h>

#include "PrimePolynom.h"

class PrimeTestAKS
{
  public:
  
    mpz_class n;

    // 1 = run
    // 0 = stop
    int stopProcessing;

    // constructors
    PrimeTestAKS();
    PrimeTestAKS(string s);
    PrimeTestAKS(mpz_class s);
    PrimeTestAKS(int s);
    
    int loga();
    int aks();

  private:
    mpz_class pow(const mpz_class& a, int b);
    mpz_class pow(const mpz_class& a, const mpz_class& b);
    int perf_pow();
    int is_int_sqrt(int b);
    int int_sqrt(int r, int b);
    int euclid(int m);
    int small_ord(int r, int lim);
};
#endif