//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_DIALOGVIENEREKEY_H__EA9CF03D_22EC_11D3_8D66_00C04F795E36__INCLUDED_
#define AFX_DIALOGVIENEREKEY_H__EA9CF03D_22EC_11D3_8D66_00C04F795E36__INCLUDED_

// DialogVienereKey.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogVienereKey 

class CDialogVienereKey : public CDialog
{
// Konstruktion
public:
	CDialogVienereKey(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDialogVienereKey)
	enum { IDD = IDD_DIALOG_KEY_VIGENERE };
	CEdit	m_text_ctl;
	CString	m_Str;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDialogVienereKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogVienereKey)
	afx_msg void OnUpdateEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DIALOGVIENEREKEY_H__EA9CF03D_22EC_11D3_8D66_00C04F795E36__INCLUDED_
