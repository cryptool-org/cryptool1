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