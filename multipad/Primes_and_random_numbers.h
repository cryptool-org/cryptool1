// Primes_and_random_numbers.h: Schnittstelle für die Klasse Primes_and_random_numbers.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIMES_AND_RANDOM_NUMBERS_H__37116FA1_FB3E_11D4_80EF_000629C93170__INCLUDED_)
#define AFX_PRIMES_AND_RANDOM_NUMBERS_H__37116FA1_FB3E_11D4_80EF_000629C93170__INCLUDED_

#include "zzgen.h"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Primes_and_random_numbers  
{
public:
	bool Prime_test_Fermat(long,long);
	Primes_and_random_numbers();
	virtual ~Primes_and_random_numbers();
	bool Prime_test_Miller_Rabin(long,long);
	bool Prime_test_Solovay_Strassen(long,long);
	long Random_with_limits(long,long);

private:
	long jacobi(long,long);
	zzgen zz;
};

#endif // !defined(AFX_PRIMES_AND_RANDOM_NUMBERS_H__37116FA1_FB3E_11D4_80EF_000629C93170__INCLUDED_)
