#if !defined(AFX_DLGSELHASH_H__C8A91DA3_040A_11D6_8A81_000255320F1C__INCLUDED_)
#define AFX_DLGSELHASH_H__C8A91DA3_040A_11D6_8A81_000255320F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelHash.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSelHash 

class CDlgSelHash : public CDialog
{
// Konstruktion
public:
	CDlgSelHash(CWnd* pParent = NULL);   // Standardkonstruktor

	CString m_sHashAlg;

// Dialogfelddaten
	//{{AFX_DATA(CDlgSelHash)
	enum { IDD = IDD_SEL_HASH };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSelHash)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	int m_nIDHash;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSelHash)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSELHASH_H__C8A91DA3_040A_11D6_8A81_000255320F1C__INCLUDED_
