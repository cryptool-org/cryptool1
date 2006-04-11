#pragma once


#include "afxwin.h"
#include "SizingDialog.h"
#ifndef baseCTestDlg
#define baseCTestDlg CSizingDialog
#endif
// CDlgCrtSecretSharing_Log-Dialogfeld

class CDlgCrtSecretSharing_Log : public baseCTestDlg
{
	DECLARE_DYNAMIC(CDlgCrtSecretSharing_Log)

public:
	CDlgCrtSecretSharing_Log(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgCrtSecretSharing_Log();

// Dialogfelddaten
	enum { IDD = IDD_CRT_SECRETSHARING_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_log;
	int m_need;
	int m_anzahl;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCrtSecretsharingLogSave();
};
