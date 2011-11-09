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

#if !defined(AFX_DLGTUTORIALFACTORISATION_H__7EFC6C44_6316_11D5_BB4A_000777640932__INCLUDED_)
#define AFX_DLGTUTORIALFACTORISATION_H__7EFC6C44_6316_11D5_BB4A_000777640932__INCLUDED_

#include "IntegerArithmetic.h"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTutorialFactorisation.h : Header-Datei
//

#include "DlgFactorisationList.h"


#define NUMBER_NOT_FACTORISED 0
#define NUMBER_RSA_MODUL 1
#define NUMBER_NOT_RSA_MODUL 2

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFactorisationDemo 

struct NumFactor;

struct NumFactor {
	BOOL isPrime;
	long exponent;
	CString factorStr;
	NumFactor *next;
};
struct zeit {
	int day;
	int hour;
	int min;
	int sec;
	int msec;
};

class CDlgFactorisationDemo : public CDialog
{
// Konstruktion
	NumFactor *factorList;
	void expandFactorisation( CString &, CString &, CString &);
public:
	BOOL m_inputReadOnly;
	void InitialiseFactorList();
	int GetRSAFactorisation(CString &str_p, CString &str_q);
	zeit zeit_condtruct1, zeit_condtruct2;
	double duration1, duration2;
	clock_t FactFinish;
	clock_t FactStart;
	CDlgFactorisationList DetailsFactorisation;

	void CheckEdit(CString &m_edit, int & sels, int & sele);
	CString Search_First_Composite_Factor();
	void Set_NonPrime_Factor_Red();
	CDlgFactorisationDemo(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgFactorisationDemo();

// Dialogfelddaten
	//{{AFX_DATA(CDlgFactorisationDemo)
	enum { IDD = IDD_FACTORISATION_DEMO };
	CButton	m_DialogeDetails;
	CButton	m_bruteForceCtrl;
	CEdit	m_CompositeNoCtrl;
	CButton	m_vollstaendig;
	CButton	m_weiter;
	CRichEditCtrl	m_FactorisationCtrl;
	CString	m_CompositeNoStr;
	BOOL	m_bruteForce;
	BOOL	m_Brent;
	BOOL	m_Pollard;
	BOOL	m_Williams;
	BOOL	m_Lenstra;
	BOOL	m_QSieve;
	CString	m_Factorisation;
	CString	m_Name;
	CString	m_benoetigte_zeit_global;
	CString m_benoetigte_zeit_pro_factorisation;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgFactorisationDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgFactorisationDemo)
	afx_msg void OnButtonEnd();
	afx_msg void OnButtonFactorisation();
	afx_msg void OnButtonVollstaendigFaktorisation();
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateEditEingabe();
	afx_msg void OnShowFactorisationDetails();
	afx_msg void OnBnClickedLoadNumber();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CTutorialFactorisation f;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGTUTORIALFACTORISATION_H__7EFC6C44_6316_11D5_BB4A_000777640932__INCLUDED_
