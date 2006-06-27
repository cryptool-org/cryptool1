#pragma once
#include "afxwin.h"


// CDlgSecretSharingOptions-Dialogfeld

class CDlgSecretSharingOptions : public CDialog
{

public:
	CString m_limit;
	CString m_prime;

	CDlgSecretSharingOptions(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgSecretSharingOptions();

// Dialogfelddaten
	//{{AFX_DATA(CDlgSecretSharingOptions)
	enum { IDD = IDD_SECRETSHARING_OPTIONS };
	//}}AFX_DATA

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgSecretSharingOptions)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSecretSharingOptions)
	afx_msg void OnButtonOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
