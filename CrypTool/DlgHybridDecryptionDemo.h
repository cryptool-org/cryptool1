#if !defined(AFX_DLGHYBRIDDECRYPTIONDEMO_H__634A1871_40B8_11D6_AD1A_000255321174__INCLUDED_)
#define AFX_DLGHYBRIDDECRYPTIONDEMO_H__634A1871_40B8_11D6_AD1A_000255321174__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHybridDecryptionDemo.h : Header-Datei
//
#define MAX_LEN_EDIT 30000
#define KEY_LEN 16
#define DIR_ENCRYPT 0 

#include "s_prng.h"
#include "DlgRSADecryption.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHybridDecryptionDemo 

class CDlgHybridDecryptionDemo : public CDialog
{
// Konstruktion
public:
	bool zugross;
	CString sModN, sPhiN, sKeyPublic, sKeyPrivate, sOutput;
	OctetString message;
	CString EncSessionKey;
	OctetString OctetEncSessionKey;
	CString DecSessionKey;
	CString SymAlg;
	CString AsymAlg;
	CString UserKeyId;
	CString UserKeyId_Datei;
	CString SymAlg_Datei;
	CString AsymAlg_Datei;
	CString EncSessionKey_Datei;
	CString m_CertificateData;
	void RsaDec();
	char SymKey[KEY_LEN];
	bool m_iIsGenAsymKey;
	CString PinCode;
	CDlgRSADecryption RsaDialog1;
	int UpdateDataDisplay();
	CFont m_font;
	int m_gc;
	bool m_bAuswahlDat;
	CString	m_strTitle1;
	char* m_strEdit1;
	CString m_strPathnameTxt;
	CDlgHybridDecryptionDemo(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgHybridDecryptionDemo();
// Dialogfelddaten
	//{{AFX_DATA(CDlgHybridDecryptionDemo)
	enum { IDD = IDD_HYBRID_DECRYPTION_DEMO };
	CEdit	m_DisplayDataCtrl;
	CEdit	m_StepCtrl;
	CEdit	m_TextSignStepsCtrl;
	CButton	m_FlushDecDataCtrl;
	CButton	m_ContinueButtonCtrl;
	CString	m_TextSignSteps;
	CString	m_Step;
	CString	m_DisplayData;
	CButton m_ShowCertificate;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgHybridDecryptionDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	void SetHeadLine( CString &mHeader, int IDS_STRING_ID, int base = 0 );	
	CPSEDemo* m_Cert;			// Zeiger auf CPSEDemo
	int nFirstVisibleLine;
	int step;
	CFont m_Font;
	CFont m_Font2;
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgHybridDecryptionDemo)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonContinue();
	afx_msg void OnButtonShowCertificate();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGHYBRIDDECRYPTIONDEMO_H__634A1871_40B8_11D6_AD1A_000255321174__INCLUDED_
