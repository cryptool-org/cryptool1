#if !defined(AFX_DLGSELECTHASH_H__912DFE1F_D9A2_11D5_8A59_000255320F1C__INCLUDED_)
#define AFX_DLGSELECTHASH_H__912DFE1F_D9A2_11D5_8A59_000255320F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelectHash.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSelectHash 

class CDlgSelectHash : public CDialog
{
// Konstruktion
public:
	CDlgSelectHash(CWnd* pParent = NULL);   // Standardkonstruktor

	BOOL InitHashID( int nIDHash );
	int  GetHashID();


// Dialogfelddaten
	//{{AFX_DATA(CDlgSelectHash)
	enum { IDD = IDD_DIALOG_SEL_HASH };
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSelectHash)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	int m_nIDFirst;
	int m_nIDLast;
	int m_nIDHash;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSelectHash)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSELECTHASH_H__912DFE1F_D9A2_11D5_8A59_000255320F1C__INCLUDED_
