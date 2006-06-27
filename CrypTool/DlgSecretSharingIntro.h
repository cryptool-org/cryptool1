#pragma once
#include "afxwin.h"

// CDlgSecretSharingIntro-Dialogfeld

class CDlgSecretSharingIntro : public CDialog
{

public:
	CDlgSecretSharingIntro(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgSecretSharingIntro();	

// Dialogfelddaten
	//{{AFX_DATA(CDlgSecretSharingIntro)
	enum { IDD = IDD_SECRETSHARING_INTRO };
	BOOL m_hide_intro;
	//}}AFX_DATA

	// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSecretSharingSetup)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSecretSharingIntro)
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


