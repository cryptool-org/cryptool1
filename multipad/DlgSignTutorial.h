#if !defined(AFX_DLGSIGNTUTORIAL_H__C8A91DA0_040A_11D6_8A81_000255320F1C__INCLUDED_)
#define AFX_DLGSIGNTUTORIAL_H__C8A91DA0_040A_11D6_8A81_000255320F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSignTutorial.h : Header-Datei
//

#include "TutorialCert.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSignTutorial 

class CDlgSignTutorial : public CDialog
{
// Konstruktion
public:
	CDlgSignTutorial(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgSignTutorial();

	// Funktionen
	BOOL InitDocument(const char *infile, const char* OldTitle);

protected:
	// Variablen
	CString			m_sPathName; // Pfadname des Dokuments
	CString			m_sFileName; // Titel des Dokuments
	CString			m_sFileNameNew; // Titel des signierten Dokuments
	CString			m_sHashAlg;  // Algorithmus Name
	int				m_nIDHash;
	int				m_nCols;
	CFont			m_Font1;	
	OctetString		m_osHash;
	OctetString		m_osHashEnc;
	BOOL			m_bUpdateHsh;
	BOOL			m_bUpdateEnc;
	BOOL			m_bUpdateRsl;

	// Zeiger
	OctetString*    m_Message;
	OctetString*	m_Signature;
	CTutorialCert*	m_Cert;
	CMyDocument*	m_NewDoc;

	// Buttons
	CBitmapButton m_ButtonSelectDoc;
	CBitmapButton m_ButtonInfoDoc;

// Dialogfelddaten
	//{{AFX_DATA(CDlgSignTutorial)
	enum { IDD = IDD_SIGN_TUTORIAL };
	CStatic	m_DisplayContentCtrl;
	CEdit	m_DisplayInfoCtrl;
	CString	m_DisplayInfo;
	CString	m_DisplayContent;
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSignTutorial)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	void EnableButtons();

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSignTutorial)
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
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSIGNTUTORIAL_H__C8A91DA0_040A_11D6_8A81_000255320F1C__INCLUDED_
