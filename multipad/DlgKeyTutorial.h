#if !defined(AFX_DLGKEYTUTORIAL_H__73C6A6D7_05B6_11D6_8A83_000255320F1C__INCLUDED_)
#define AFX_DLGKEYTUTORIAL_H__73C6A6D7_05B6_11D6_8A83_000255320F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKeyTutorial.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyTutorial 

#include "TutorialCert.h"

class CDlgKeyTutorial : public CDialog
{
// Konstruktion
public:
	CDlgKeyTutorial(CWnd* pParent = NULL);   // Standardkonstruktor

	void InitRSA(CTutorialCert* Cert);

protected:
	CBitmap m_bmpCheck;
	CBitmap m_bmpNoCheck;
	CBitmapButton m_ButtonInfo;

private:
	CTutorialCert* m_Cert; // Zertifikat

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyTutorial)
	enum { IDD = IDD_KEY_TUTORIAL };
	CStatic	m_BitLengthCtrl;
	CStatic	m_CheckPrimeCtrl;
	CStatic	m_CheckPublicCtrl;
	CEdit	m_KeyPublicCtrl;
	CButton	m_ButtonOKCtrl;
	CString	m_sPrime_p;
	CString	m_sPrime_q;
	CString	m_sKeyPublic;
	CString	m_sKeyPrivate;
	CString	m_sModN;
	CString	m_sPhiN;
	CString	m_sFirstName;
	CString	m_sName;
	CString	m_sPIN;
	CString	m_sPINv;
	CString	m_sCheckPrime;
	CString	m_sCheckPublic;
	CString	m_sBitLength;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyTutorial)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyTutorial)
	virtual BOOL OnInitDialog();
	afx_msg void OnGeneratePrime();
	afx_msg void OnUpdateParameter();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGKEYTUTORIAL_H__73C6A6D7_05B6_11D6_8A83_000255320F1C__INCLUDED_
