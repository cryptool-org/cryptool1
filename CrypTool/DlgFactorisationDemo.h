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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CTutorialFactorisation f;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGTUTORIALFACTORISATION_H__7EFC6C44_6316_11D5_BB4A_000777640932__INCLUDED_
