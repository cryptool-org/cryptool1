#if !defined(AFX_DLGRANDPARAMETER_X2_MOD_N_H__28B88971_33CC_11D5_92F4_00B0D0161C45__INCLUDED_)
#define AFX_DLGRANDPARAMETER_X2_MOD_N_H__28B88971_33CC_11D5_92F4_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRandParameter_x2_mod_N.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgX2ModNRandomParamater 

class CDlgX2ModNRandomParamater : public CDialog
{
// Konstruktion
public:
	CString GetModul(void);
	void SetModul(CString &NStr);
	CDlgX2ModNRandomParamater(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgX2ModNRandomParamater)
	enum { IDD = IDD_X2MODN_RANDOMPARAMETER };
	CEdit	m_Control_Edit_Modul_N;
	CString	m_EditModul_N;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgX2ModNRandomParamater)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgX2ModNRandomParamater)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGRANDPARAMETER_X2_MOD_N_H__28B88971_33CC_11D5_92F4_00B0D0161C45__INCLUDED_
