/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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
