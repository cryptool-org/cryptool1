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
	GeneratePrimes P;
	GeneratePrimes Q;
public:
	// this variable indicates that the prime number generation thread is to be aborted
	BOOL abortGenerationPrimeNumbers;
	// this variable indicates if the prime number generation thread was aborted by the user
	BOOL generationPrimeNumbersAborted;
	// this variable indicates if the generation of multiple prime numbers is possible
	BOOL generateMultiplePrimeNumbersEnabled;
	// this variable indicates that the multiple prime number generation thread is to be aborted
	BOOL abortGenerationMultiplePrimeNumbers;
	// this variable indicates if the multiple prime number generation thread was aborted by the user
	BOOL generationMultiplePrimeNumbersAborted;
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
