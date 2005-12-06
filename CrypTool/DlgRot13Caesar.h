//#if !defined(AFX_DLGROT13CAESAR_H__F55065A9_4E94_4628_8094_05713C56FF7C__INCLUDED_)
//#define AFX_DLGROT13CAESAR_H__F55065A9_4E94_4628_8094_05713C56FF7C__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000
// DlgRot13Caesar.h : Header-Datei
//

#ifndef DIA1_H
#define DIA1_H
// dia1.h : header file
//

#include "KeyRepository.h"
#define MAX_VIGENERE	1024
#define MAX_DISPLAY		40
#define MAX_EXTRA		3
#define FILL_CHAR		'.'
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRot13Caesar 

class CDlgRot13Caesar : public CDialog
{
	CBitmapButton m_paste;
	CBitmapButton m_down;
// Konstruktion
public:
	UINT m_type;
	char strTitle[KEYDATA_HASHSTRING_LENGTH];
	CDlgRot13Caesar(CWnd* pParent = NULL);   // Standardkonstruktor
	long m_Decrypt;
	virtual int	Display();
	virtual char *	GetData( void );

// Dialogfelddaten
	//{{AFX_DATA(CDlgRot13Caesar)
	enum { IDD = IDD_ROT13_CAESAR };
	CEdit	m_to_control;
	CEdit	m_from_control;
	CButton	m_EncryptionButton;
	CButton	m_DecryptionButton;
	CStatic	m_dist_control;
	CEdit	m_key_control;
	CString	m_key;
	int		m_radio;
	CString	m_from;
	CString	m_to;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgRot13Caesar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgRot13Caesar)
	afx_msg void OnRot13Rad();
	afx_msg void OnCaesarRad();
	afx_msg void OnUpdateKey();
	virtual BOOL OnInitDialog();
	afx_msg void OnPasteKey();
	afx_msg void OnEncrypt();
	afx_msg void OnDecrypt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	char s_alternativeWindowText[127];
private:
	CString GetRot13Key();
	CString FinalizeOutput(CString);
	void UpdateFromTo(BOOL show);
	void SetCryptButtons(BOOL force);
	void UpdateDist();
	CFont m_font;
	CString m_source;
	int m_dist;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGROT13CAESAR_H__F55065A9_4E94_4628_8094_05713C56FF7C__INCLUDED_
