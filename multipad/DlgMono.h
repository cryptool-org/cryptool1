//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Christian Tobias
//////////////////////////////////////////////////////////////////

#ifndef AFX_DLGMONO_H__D7708DFF_AEAD_11D2_8D42_00C04F795E36__INCLUDED_
#define AFX_DLGMONO_H__D7708DFF_AEAD_11D2_8D42_00C04F795E36__INCLUDED_

// DlgMono.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgMono 

//#include "MyCEdit.h"

class CDlgMono : public CDialog
{
	CBitmapButton m_Paste;

	// Konstruktion
public:
	CDlgMono(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgMono)
	enum { IDD = IDD_DIALOG_KEY_INPUT_MONO };
	CEdit	m_edit2;
	CString	m_edit;
	//}}AFX_DATA
	int m_check;


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgMono)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgMono)
	afx_msg void OnChangeEdit1();
	afx_msg void OnDecrypt();
	afx_msg void OnEncrypt();
	virtual BOOL OnInitDialog();
	afx_msg void OnPasteKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGMONO_H__D7708DFF_AEAD_11D2_8D42_00C04F795E36__INCLUDED_
