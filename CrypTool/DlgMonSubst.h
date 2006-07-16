#include "afxwin.h"
#if !defined(AFX_DLGMONSUBST_H__3570C2DB_B992_412D_BAAD_AC0520646674__INCLUDED_)
#define AFX_DLGMONSUBST_H__3570C2DB_B992_412D_BAAD_AC0520646674__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMonSubst.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgMonSubst 

class CDlgMonSubst : public CDialog
{
// Konstruktion
	CBitmapButton m_Paste;
	CFont m_font;

	BOOL f_FillAscendingOrder;


public:
	CDlgMonSubst(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgMonSubst();
	int   m_cryptDirection;
	char key[27];
	CString typeOfEncryption;
// Dialogfelddaten
	//{{AFX_DATA(CDlgMonSubst)
	enum { IDD = IDD_KEY_MONSUBST };
	CEdit	m_CtrlTo;
	CEdit	m_CtrlFrom;
	CEdit	m_CtrlKey;
	CButton m_RadioChooseKeyVariant;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgMonSubst)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgMonSubst)
	afx_msg void OnChangeKey();
	virtual BOOL OnInitDialog();
	afx_msg void OnPasteKey();
	afx_msg void OnEncrypt();
	afx_msg void OnDecrypt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ComputeSubstKeyMapping();
	int  CheckPasteKeyVariant(int SID, CString &keyStr);
public:
	afx_msg void OnBnClickedRadioSubstFillAscendingOrder();
	afx_msg void OnBnClickedRadioAddBash();
	afx_msg void OnBnClickedRadioSubstFillDescendingOrder();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGMONSUBST_H__3570C2DB_B992_412D_BAAD_AC0520646674__INCLUDED_
