// Primes_and_random_numbers.h: Schnittstelle für die Klasse Primes_and_random_numbers.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIMES_AND_RANDOM_NUMBERS_H__37116FA1_FB3E_11D4_80EF_000629C93170__INCLUDED_)
#define AFX_PRIMES_AND_RANDOM_NUMBERS_H__37116FA1_FB3E_11D4_80EF_000629C93170__INCLUDED_

#include "big.h"
#include "monty.h"
//#include "zzgen.h"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define TIMES '*'
// #define RAISE '#'
#define RAISE '^'

class Primes_and_random_numbers  
{

	Miracl precision4;
public:
	miracl *mip4;
	CString konvertiere_Big_CString (Big Eingabe);
	Big konvertiere_CString_Big (CString Eingabe);
	Big t;
	Big ausgabe;
//	char *str;
	bool eval ();
	void eval_product(Big &oldn, Big &n, char op);
	void eval_sum (Big &oldn, Big &n, char op);
	void eval_power (Big &oldn, Big &n, char op);
	void encrypt_block(Big *Block, long blocklaenge,long anzahl_buchstaben, Big ausgabe,Big n, Big e);
	Big potenz (Big x, Big n);
	long RSA_BlockLaengeBerechnung (Big x , long a);
	Big ggT (Big a, Big b);
	Big erzeuge_oeffentliche_Schluessel_e(Big phi_pq);

	Big random_with_limits(Big upper);
	long Bitlaenge (Big x,Big *bi);
	Big square_und_multiply (Big x, Big b,Big n);
	Big extended_euclidian_algorithm(Big n, Big e);
	//CString GetCString (long, CString);
	//long GetLong(CString);
	//long oeff_param_pq(CString, CString);
	bool Prime_test_Fermat(Big n, long t);
	Big jacobi(Big a, Big n);
	Big Random_with_limits(Big lower, Big upper);
	bool Prime_test_Miller_Rabin(Big n, long t);
	bool Prime_test_Solovay_Strassen(Big n, long t);
		Primes_and_random_numbers();
	virtual ~Primes_and_random_numbers();
/*
public:
	bool Prime_test_Fermat(Big,long);
	Primes_and_random_numbers();
	virtual ~Primes_and_random_numbers();
	bool Prime_test_Miller_Rabin(Big,long);
	bool Prime_test_Solovay_Strassen(Big,long);
	Big Random_with_limits(Big,Big);
	Big square_und_multiply(Big, Big, Big);
	long Bitlaenge(Big x,Big *bi);
*/

private:
	//Big jacobi(Big,Big);
	//zzgen zz;
};

#endif // !defined(AFX_PRIMES_AND_RANDOM_NUMBERS_H__37116FA1_FB3E_11D4_80EF_000629C93170__INCLUDED_)




	
