#if !defined(AFX_DLGSIGNTUTORIAL_H__C8A91DA0_040A_11D6_8A81_000255320F1C__INCLUDED_)
#define AFX_DLGSIGNTUTORIAL_H__C8A91DA0_040A_11D6_8A81_000255320F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSignTutorial.h : Header-Datei
//

#include "PSEDemo.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSignatureDemo 

class CDlgSignatureDemo : public CDialog
{
// Konstruktion
public:
	CDlgSignatureDemo(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgSignatureDemo();

	// Funktionen
	BOOL InitDocument(const char *infile, const char* OldTitle);

protected:
	// Variablen
	CString			m_sPathName;	// Pfadname des Dokuments
	CString			m_sFileName;	// Titel des Dokuments
	CString			m_sFileNameNew; // Titel des signierten Dokuments
	int				m_nIDHash;
	int				m_nCols;		// Spaltenzahl des Displays
	CFont			m_Font1;	
	BOOL			m_bUpdateHsh;
	BOOL			m_bUpdateEnc;
	BOOL			m_bUpdateSgn;
	BOOL			m_bUpdateCrt;

	// Zeiger
	OctetString*	m_osHash;
	OctetString*	m_osHashEnc;
	OctetString*    m_Message;
	OctetString*	m_Signature;
	OctetString*	m_SignText;
	CPSEDemo*	m_Cert;
	CAppDocument*	m_NewDoc;

	// Buttons
	CBitmapButton m_ButtonSelectDoc;
	CBitmapButton m_ButtonInfoDoc;

// Dialogfelddaten
	//{{AFX_DATA(CDlgSignatureDemo)
	enum { IDD = IDD_SIGNATURE_DEMO };
	CStatic	m_DisplayContentCtrl;
	CEdit	m_DisplayInfoCtrl;
	CString	m_DisplayInfo;
	CString	m_DisplayContent;
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSignatureDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	void EnableButtons();
	void ClearInfo();

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSignatureDemo)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectDocument();
	afx_msg void OnInfoDocument();
	afx_msg void OnSelectKey();
	afx_msg void OnInfoKey();
	afx_msg void OnSelectHashAlg();
	afx_msg void OnCompute();
	afx_msg void OnInfoHash();
	afx_msg void OnEncrypt();
	afx_msg void OnInfoHashEnc();
	afx_msg void OnSelectCert();
	afx_msg void OnInfoAlg();
	afx_msg void OnCombine();
	virtual void OnOK();
	afx_msg void OnInfoCert();
	afx_msg void OnInfoSign();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSIGNTUTORIAL_H__C8A91DA0_040A_11D6_8A81_000255320F1C__INCLUDED_
