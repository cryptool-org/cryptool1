#if !defined(AFX_DLGSHOWHASH_H__6AB34981_AE98_11D5_936B_00B0D0161C45__INCLUDED_)
#define AFX_DLGSHOWHASH_H__6AB34981_AE98_11D5_936B_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgShowHash.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowHash 

class CDlgShowHash : public CDialog
{
// Konstruktion
public:
	void SetHash( OctetString &hash, const char * );
	CDlgShowHash(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgShowHash)
	enum { IDD = IDD_SHOW_HASH };
	CString	m_HashStr;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgShowHash)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgShowHash)
	afx_msg void OnShowHashInDesktop();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char title[256];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSHOWHASH_H__6AB34981_AE98_11D5_936B_00B0D0161C45__INCLUDED_
