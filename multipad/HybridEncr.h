#if !defined(AFX_HYBRIDENCR_H__EB90CA93_1BA0_11D6_AB88_0006291976BD__INCLUDED_)
#define AFX_HYBRIDENCR_H__EB90CA93_1BA0_11D6_AB88_0006291976BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HybridEncr.h : Header-Datei
//
#include "s_prng.h"
#include "RsaEnc.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CHybridEncr 
#define MAX_LEN_EDIT 30000
#define KEY_LEN 16
#define DIR_ENCRYPT 0 

class CHybridEncr : public CDialog
{
// Konstruktion
public:
	char* m_in;
	int m_gc;
	void GetCertificateData(Certificate* Zert);
	CString m_strPfadEditorDat;
	bool m_barrSetCondition[8];
	void EnDisButtons();
	bool m_bAuswahlDat;
	CRsaEnc RsaDialog1;
	char SymKey[KEY_LEN];
	OctetString* EncSymKey;
	void RSAEncrypt();
	bool m_iIsGenAsymKey;
	bool m_iIsTxtAlreadySel;
	int m_iDatGroesse1;
	bool m_iIsGenSymKey;
	CFont m_font;
	CString m_strSymKey;
	CString m_strPathnameTxt;
	CString m_strEdit1;
	CString	m_strTitle1;

	CHybridEncr(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CHybridEncr)
	enum { IDD = IDD_DIALOG_HYBRID };
	CButton	m_ctrlShowTxt;
	CButton	m_ctrlShowAsymKey;
	CButton	m_ctrlShowSymKey;
	CButton	m_ctrlEncKeyAsym;
	CButton	m_ctrlGetAsymKey;
	CButton	m_ctrlEncTxtSym;
	CButton	m_ctrlGenSymKey;
	CString	m_strEdit;
	CString	m_strTitle;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CHybridEncr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CHybridEncr)
	afx_msg void OnButton1TxtEinfuegen();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonEncKeyAsym();
	afx_msg void OnButtonEncTxtSym();
	afx_msg void OnButtonGenSymKey();
	afx_msg void OnButtonGetAsymKey();
	afx_msg void OnButtonShowSymKey();
	afx_msg void OnButtonShowAsymKey();
	afx_msg void OnButtonShowtxt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_HYBRIDENCR_H__EB90CA93_1BA0_11D6_AB88_0006291976BD__INCLUDED_
