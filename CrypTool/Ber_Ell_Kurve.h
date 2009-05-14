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

// Ber_Ell_Kurve.h: Schnittstelle für die Klasse Ber_Ell_Kurve.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BER_ELL_KURVE_H__DED21344_096E_11D5_8899_00062919F268__INCLUDED_)
#define AFX_BER_ELL_KURVE_H__DED21344_096E_11D5_8899_00062919F268__INCLUDED_

#include "..\LIBMIRACL\INCLUDE\BIG.H"	// Hinzugefügt von der Klassenansicht
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

#include <monty.h>
#if defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#include <iomanip.h>
#else
#include <iostream>
#include <iomanip>
using namespace std;
#endif

#define LIMIT1 10000     /* must be int, and > MULT/2 */
#define LIMIT2 1000000L  /* may be long */
#define MULT   2310      /* must be int, product of small primes 2.3... */
#define NEXT   13           /* next small prime */
#define NCURVES 20      /* number of curves to try */

class Ber_Ell_Kurve  
{
	miracl *mip;
public:
	int Disc;
	Big k_par;
	Big r_par;
	Big p_par;
	Big y_par;
	Big x_par;
	Big b_par;
	Big a_par;
//	char* s;
	char line[256];
	int GetInitPrime (CString Input, int saat);



	bool get_curve(ofstream& ofile, Big r, Big ord, int D, Big p, Big W, int saat);
	Big p;
//	char *s[100];
	bool suppress;
	bool fout;
	Big t;
	bool isacm(Big p,int D,Big &W,Big &V);
	bool isaD(int d,int pm8,int k);
	void groups(int D);
	Complex F(int j,int A,int B,int C);
	void class_poly(int A,int B,int C, int D, BOOL conj);
	int getk(int D);
	int geti(int D);
	FPoly T; // Reduced class Polynomial.
	Complex Fz(Complex z);
	Ber_Ell_Kurve();
	virtual ~Ber_Ell_Kurve();
};

#endif // !defined(AFX_BER_ELL_KURVE_H__DED21344_096E_11D5_8899_00062919F268__INCLUDED_)
