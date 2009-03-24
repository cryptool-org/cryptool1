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


#if !defined(AFX_DLGPRIMESGENERATOR_H__0F161EA1_E56B_11D4_80D9_000629C93170__INCLUDED_)
#define AFX_DLGPRIMESGENERATOR_H__0F161EA1_E56B_11D4_80D9_000629C93170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPrimesGenerator.h : Header-Datei
//

#include "IntegerArithmetic.h"
#include <map>

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgPrimesGeneratorDemo 

class CDlgPrimesGeneratorDemo : public CDialog
{

public:
	CDlgPrimesGeneratorDemo(CWnd* pParent = NULL);   // Standardkonstruktor
	CDlgPrimesGeneratorDemo(CString,CString,CWnd* pParent = NULL);
	BOOL GetRandomPrime( CString &OutStr, GeneratePrimes &P );

	// call this function to enable the "generate a set of prime numbers" functionality
	void enableGenerateASetOfPrimeNumbersFunctionality();
	
	bool m_hide_button_accept;
// Dialogfelddaten
	//{{AFX_DATA(CDlgPrimesGeneratorDemo)
	enum { IDD = IDD_PRIMES_GENERATOR_DEMO };
	CEdit	m_control_edit2;
	CEdit	m_control_edit1;
	CButton	m_control_button_generate;
	CButton	m_control_button_accept;
	CEdit	m_control_edit4;
	CEdit	m_control_edit3;
	CEdit m_control_edit5;
	CEdit m_control_edit6;
	CEdit m_control_separator;
	int m_radio1;
	int m_radio4;
	int m_radio6;
	CString	m_edit1;
	CString	m_edit2;
	CString	m_edit3;
	CString	m_edit4;
	CString	m_edit5;
	CString	m_edit6;
	CString separator;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgPrimesGeneratorDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgPrimesGeneratorDemo)
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGenerate();
	afx_msg void OnButtonAccept();
	afx_msg void OnEndDialog();
	afx_msg void OnUpdateEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	// this variable indicates if the generation of multiple prime numbers is possible
	BOOL generateMultiplePrimeNumbersEnabled;
	// this variable indicates that the prime number generation thread is to be aborted
	BOOL abortGenerationMultiplePrimeNumbers;
	// this variable indicates if the generation thread was aborted by the user
	BOOL primeNumberGenerationAborted;
	// this struct holds the comparison function to sort the map filled with primes
	struct primeComparison {
		bool operator()(const CString &one, const CString &two) const {
			if(one.GetLength() > two.GetLength())
				return false;
			if(one.GetLength() < two.GetLength())
				return true;
			for(int i=0; i<one.GetLength(); i++) {
				if(one[i] > two[i])
					return false;
				if(one[i] < two[i])
					return true;
			}
			return false;
		}
	};
	// this map variable holds all generated prime numbers
	std::map<CString, CString, primeComparison> mapGeneratedPrimeNumbers;
	// this is a map iterator (see above)
	std::map<CString, CString, primeComparison>::iterator mapGeneratedPrimeNumbersIterator;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGPRIMESGENERATOR_H__0F161EA1_E56B_11D4_80D9_000629C93170__INCLUDED_
