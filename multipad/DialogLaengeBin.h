//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_DIALOGLAENGEBIN_H__EA9CF03C_22EC_11D3_8D66_00C04F795E36__INCLUDED_
#define AFX_DIALOGLAENGEBIN_H__EA9CF03C_22EC_11D3_8D66_00C04F795E36__INCLUDED_

// DialogLaengeBin.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogLaengeBin 

class CDialogLaengeBin : public CDialog
{
// Konstruktion
public:
	char m_c;
	CDialogLaengeBin(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDialogLaengeBin)
	enum { IDD = IDD_DIALOG_SCHLUESSELLAENGE_BIN };
	CEdit	m_Ctl;
	CString	m_Char;
	UINT	m_laenge;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDialogLaengeBin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogLaengeBin)
	afx_msg void OnChangeEdit2();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DIALOGLAENGEBIN_H__EA9CF03C_22EC_11D3_8D66_00C04F795E36__INCLUDED_
