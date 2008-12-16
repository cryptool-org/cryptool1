#ifndef PRIM_AKS_H
#define PRIM_AKS_H

#include <stdio.h>
#include <string>
#include <gmpxx.h>

using namespace std;

class PrimeTestAKS
{
  public:
  
    mpz_class n;

    // constructors
	PrimeTestAKS(int *cancel = 0);
    PrimeTestAKS(string s, int *cancel = 0);
    PrimeTestAKS(mpz_class s, int *cancel = 0);
    PrimeTestAKS(int s, int *cancel = 0);
    
    int loga();
    int aks();
	virtual double getProgress();
  private:
    int aks_index; // current index in second loop of aks(); used for getProgress()
	int aks_limit; // upper limit of second loop of aks(); used for getProgress()
	int *pcancelled; // if not null points to a flag to periodically check for cancel
	int cancelled() const { return pcancelled && *pcancelled; }
    mpz_class pow(const mpz_class& a, int b);
    mpz_class pow(const mpz_class& a, const mpz_class& b);
    int perf_pow();
    int is_int_sqrt(int b);
    int int_sqrt(int r, int b);
    int euclid(int m);
    int small_ord(int r, int lim);
};
#endif
