#if !defined(AFX_DLGRANDPARAMETER_X2_MOD_N_H__28B88971_33CC_11D5_92F4_00B0D0161C45__INCLUDED_)
#define AFX_DLGRANDPARAMETER_X2_MOD_N_H__28B88971_33CC_11D5_92F4_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRandParameter_x2_mod_N.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgRandParameter_x2_mod_N 

class DlgRandParameter_x2_mod_N : public CDialog
{
// Konstruktion
public:
	CString GetModul(void);
	void SetModul(CString &NStr);
	DlgRandParameter_x2_mod_N(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(DlgRandParameter_x2_mod_N)
	enum { IDD = IDD_RANDOM_PARAMETER_X2_MOD_N };
	CString	m_EditModul_N;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(DlgRandParameter_x2_mod_N)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(DlgRandParameter_x2_mod_N)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGRANDPARAMETER_X2_MOD_N_H__28B88971_33CC_11D5_92F4_00B0D0161C45__INCLUDED_
