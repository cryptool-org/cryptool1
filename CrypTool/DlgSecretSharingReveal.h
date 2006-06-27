#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "SecretSharingLog.h"


// CDlgSecretSharingReveal-Dialogfeld

class CDlgSecretSharingReveal : public CDialog
{
public:
	CDlgSecretSharingReveal(CWnd* pParent = NULL); 
	CDlgSecretSharingReveal(int nNew, int gNew, bool *selected, long *paraSelected, Big *sharesSelected, SecretSharingLog*, Big, CWnd* pParent = NULL);
	virtual ~CDlgSecretSharingReveal();

// Dialogfelddaten
	//{{AFX_DATA(CDlgSecretSharingReveal)
	enum { IDD = IDD_SECRETSHARING_REVEAL };
	CListCtrl m_list_participants;
	CString m_secret;
	CButton m_ctrl_showLog;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSecretSharingReveal)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSecretSharingReveal)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowLog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool *isSel;
	long *para;
	Big *sh, result;
	int n, p;	
	SecretSharingLog *logF;
};
