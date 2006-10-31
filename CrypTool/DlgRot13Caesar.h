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
#include "afxwin.h"
#define MAX_VIGENERE	1024
#define MAX_DISPLAY		40
#define MAX_EXTRA		3
#define FILL_CHAR		'.'
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRot13Caesar 

#include "DlgTextOptions.h"

class CDlgRot13Caesar : public CDialog
{
	CBitmapButton m_paste;
// Konstruktion
public:
	CDlgRot13Caesar(CWnd* pParent = NULL);   // Standardkonstruktor
	long m_Decrypt;
	unsigned long alphCode;
	unsigned long firstPosNull;
	bool caesarSelected;
	UINT m_type;   // PUBLIC PARAMETER {IDS_STRING_ROT13, IDS_STRING_CAESAR }
	CString m_key; // THE KEY!

	CString getAlphCode(CString alphChar);
	CString getAlphChar(CString alphPos);

	void EnableFirstPosNull();
	void DisableFirstPosNull();
	void OnTxtOptions();

	int getCifLength();


	// Dialogfelddaten
	//{{AFX_DATA(CDlgRot13Caesar)
	enum { IDD = IDD_ROT13_CAESAR };
	CEdit	m_CtrlTo;
	CEdit	m_CtrlFrom;
	CEdit	m_CtrlKey;
	CEdit	m_CtrlAlphCode;
	CEdit   m_dist_control;
	CButton m_EncryptionButton;
	CButton m_DecryptionButton;
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
	afx_msg void EnableAlphCode();
	afx_msg void DisableAlphCode();
	afx_msg void OnExitAlphCode();
	afx_msg void OnUpdateKey();
	afx_msg void OnUpdateAlphCode();
	virtual BOOL OnInitDialog();
	afx_msg void OnPasteKey();
	afx_msg void OnEncrypt();
	afx_msg void OnDecrypt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CFont m_font;
	int m_dist;
	char CheckPasteKeyVariant(int SID);
public:
	CButton m_CtrlRadioRot13;
	CEdit m_CtrlMessageRot13;
	CEdit m_CtrlShowAlSize;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGROT13CAESAR_H__F55065A9_4E94_4628_8094_05713C56FF7C__INCLUDED_
