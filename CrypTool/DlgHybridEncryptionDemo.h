#if !defined(AFX_HYBRIDENCR_H__EB90CA93_1BA0_11D6_AB88_0006291976BD__INCLUDED_)
#define AFX_HYBRIDENCR_H__EB90CA93_1BA0_11D6_AB88_0006291976BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HybridEncr.h : Header-Datei
//
#include "s_prng.h"
#include "DlgRSAEncryption.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHybridEncryptionDemo 
#define MAX_LEN_EDIT 30000
#define KEY_LEN 16
#define DIR_ENCRYPT 0 

class CDlgHybridEncryptionDemo : public CDialog
{
// Konstruktion
public:
	bool DateiOeffnen(const CString &DateiPfadName);
	bool m_arrSetButtons[10];
	bool m_barrSetCondition[10];
	bool m_setMatrix[10][10];
	CString m_strBuffEditEncKeyAsym;
	CString m_strBuffEditEncDoc;
	CString Edit;
	char* m_strBuffEditDoc;
	int m_iDocSize;
	bool m_bAuswahlDat;
	CDlgRSAEncryption rsaDlg;
	char SymKey[KEY_LEN];
	OctetString* EncSymKey;
	//bool m_iIsGenAsymKey;
	//bool m_iIsTxtAlreadySel;

	int m_iDocSizeForEnc;
	CFont m_font;
	CString m_strSymKey;
	CString m_strPathSelDoc;
	CString	m_strBuffTitle;

	CDlgHybridEncryptionDemo(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgHybridEncryptionDemo();
	void ShowButtons();
	void EnDisButtons();
	void RSAEncrypt();


// Dialogfelddaten
	//{{AFX_DATA(CDlgHybridEncryptionDemo)
	enum { IDD = IDD_HYBRID_ENCRYPTION_DEMO };
	CStatic	m_ctrlBG;
	CString	m_strEdit;
	CString	m_strTitle;
	//}}AFX_DATA

	CBitmapButton m_ctrlBmpRaute1;
	CBitmapButton m_ctrlBmpRaute2;
	CBitmapButton m_ctrlBmpRaute3;
	CBitmapButton m_ctrlBmpRaute4;
	CBitmapButton m_ctrlBmpRaute5;
	CBitmapButton m_ctrlBmpSechseck1;
	CBitmapButton m_ctrlBmpSechseck2;
	CBitmapButton m_ctrlBmpSechseck3;
	CBitmapButton m_ctrlBmpViereck1;
	CBitmapButton m_ctrlBmpViereck2;
	CBitmapButton m_ctrlBmpOval1;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgHybridEncryptionDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgHybridEncryptionDemo)
	afx_msg void OnButton1TxtEinfuegen();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonEncKeyAsym();
	afx_msg void OnButtonEncTxtSym();
	afx_msg void OnButtonGenSymKey();
	afx_msg void OnButtonGetAsymKey();
	afx_msg void OnButtonShowSymKey();
	afx_msg void OnButtonShowAsymKey();
	afx_msg void OnButtonShowtxt();
	afx_msg void OnShowEncTxt();
	afx_msg void OnShowEncSymKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_HYBRIDENCR_H__EB90CA93_1BA0_11D6_AB88_0006291976BD__INCLUDED_
