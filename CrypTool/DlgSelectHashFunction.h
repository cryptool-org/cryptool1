#if !defined(AFX_SELCTAHASHFUNCTION_H__F4D10A11_197E_11D6_9392_00B0D0161C45__INCLUDED_)
#define AFX_SELCTAHASHFUNCTION_H__F4D10A11_197E_11D6_9392_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelctAHashfunction.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSelectHashFunction 

class CDlgSelectHashFunction : public CDialog
{
// Konstruktion
public:
	CDlgSelectHashFunction(CWnd* pParent = NULL);   // Standardkonstruktor

	bool    m_deactivateMD4;
	int		m_selectedHashFunction;
// Dialogfelddaten
	//{{AFX_DATA(CDlgSelectHashFunction)
	enum { IDD = IDD_SELECT_HASHFUNCTION };
	CButton	m_selectedHashFunctionMD4Ctrl;
	int		m_selectedHashFunctionMD2;
	int		m_selectedHashFunctionMD4;
	int		m_selectedHashFunctionMD5;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSelectHashFunction)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSelectHashFunction)
	afx_msg void OnSelectedMD2();
	afx_msg void OnSelectedMD4();
	afx_msg void OnSelectedMD5();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectSHA();
	afx_msg void OnSelectedSHA_1();
	afx_msg void OnSelectedRIPEMD_160();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SELCTAHASHFUNCTION_H__F4D10A11_197E_11D6_9392_00B0D0161C45__INCLUDED_
