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

#if !defined(AFX_DLGDIFFIEHELLMANPUBLICPARAMETERS_H__4D741E0D_E4AE_11D6_A894_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANPUBLICPARAMETERS_H__4D741E0D_E4AE_11D6_A894_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>



// DlgDiffieHellmanPublicParameters.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanPublicParameters 
struct factor {
	int		exp;
	int     isPrime;
	CString strNum;

	factor(CString STRNUM, int ISPRIME)
	{ exp = 1; isPrime = ISPRIME; strNum = STRNUM; }
	void incExp() { exp++; }
};


class CDlgDiffieHellmanPublicParameters : public CDialog
{
// Konstruktion
	std::list<factor> factorlistPhiOfP;

public:
	CDlgDiffieHellmanPublicParameters(CWnd* pParent = NULL);				// Standardkonstruktor
	CDlgDiffieHellmanPublicParameters(std::string,std::string,CWnd* pParent = NULL);	// Zusatzkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanPublicParameters)
	enum { IDD = IDD_DIFFIEHELLMAN_PUBLICPARAMETERS };
	CEdit	m_PrimeControl;
	CEdit	m_GeneratorControl;
	CString	m_Generator;
	CString	m_Prime;
	//}}AFX_DATA

	BOOL b_isSavePrime;
	int  b_errType;
	int checkGenerator();

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanPublicParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanPublicParameters)
	virtual void OnOK();
	afx_msg void OnGeneratePrime();
	afx_msg void OnGenerateGenerator();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangePrime();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANPUBLICPARAMETERS_H__4D741E0D_E4AE_11D6_A894_00025532117A__INCLUDED_
