#if !defined(AFX_DLGTUTORIALFACTORISATION_H__7EFC6C44_6316_11D5_BB4A_000777640932__INCLUDED_)
#define AFX_DLGTUTORIALFACTORISATION_H__7EFC6C44_6316_11D5_BB4A_000777640932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTutorialFactorisation.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgTutorialFactorisation 

struct NumFactor;

struct NumFactor {
	BOOL isPrime;
	long exponent;
	CString factorStr;
	NumFactor *next;
};

class DlgTutorialFactorisation : public CDialog
{
// Konstruktion
	NumFactor *factorList;
	void expandFactorisation( CString &, CString &, CString &);
public:
	CString Search_First_Composite_Factor();
	void Set_NonPrime_Factor_Red();
	DlgTutorialFactorisation(CWnd* pParent = NULL);   // Standardkonstruktor
	~DlgTutorialFactorisation();

// Dialogfelddaten
	//{{AFX_DATA(DlgTutorialFactorisation)
	enum { IDD = IDD_DIALOG_ZAHL_FAKTORISIEREN };
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
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(DlgTutorialFactorisation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(DlgTutorialFactorisation)
	afx_msg void OnButtonEnd();
	afx_msg void OnButtonFactorisation();
	afx_msg void OnButtonVollstaendigFaktorisation();
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateEditEingabe();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGTUTORIALFACTORISATION_H__7EFC6C44_6316_11D5_BB4A_000777640932__INCLUDED_
