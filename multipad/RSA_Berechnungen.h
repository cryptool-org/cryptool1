// RSA_Berechnungen.h: Schnittstelle f�r die Klasse RSA_Berechnungen.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RSA_BERECHNUNGEN_H__4D7B9813_FC37_11D4_BEF3_0006291976BD__INCLUDED_)
#define AFX_RSA_BERECHNUNGEN_H__4D7B9813_FC37_11D4_BEF3_0006291976BD__INCLUDED_

//#include "zzgen.h"	// Hinzugef�gt von der Klassenansicht
#include "Primes_and_random_numbers.h"	// Hinzugef�gt von der Klassenansicht
#include "big.h"
#include "..\LIBMIRACL\INCLUDE\BIG.H"	// Hinzugef�gt von der Klassenansicht

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TIMES '*'
// #define RAISE '#'
#define RAISE '^'





#include <big.h>
#include "elliptic.h"
#include "comflash.h"
#include "fpoly.h"
#include "poly.h"

//#include <mrrand.h>
#include <monty.h>
#include <iostream.h>
#include <iomanip.h>




class RSA_Berechnungen  
{
	Miracl precision3;
public:
	CString konvertiere_Big_CString (Big Eingabe);
	Big konvertiere_CString_Big (CString Eingabe);
	miracl *mip3;
	Big t;
	char *s;
	bool eval ();
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
	RSA_Berechnungen();
	virtual ~RSA_Berechnungen();
private:
	//zzgen zz;
};

#endif // !defined(AFX_RSA_BERECHNUNGEN_H__4D7B9813_FC37_11D4_BEF3_0006291976BD__INCLUDED_)
