#pragma once
#include "afxwin.h"


// CDlgCrtSecretSharingOptions-Dialogfeld

class CDlgCrtSecretSharingOptions : public CDialog
{
	DECLARE_DYNAMIC(CDlgCrtSecretSharingOptions)

public:
	CDlgCrtSecretSharingOptions(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgCrtSecretSharingOptions();

// Dialogfelddaten
	enum { IDD = IDD_CRT_SECRETSHARING_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	int m_anzahl;
	int m_need;
	int calcmode;
	CString m_x;
	CString m_y;
	CEdit m_control_x;
	CEdit m_control_y;

	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeCrtSecretsharingedit3();
	afx_msg void OnEnChangeCrtSecretsharingedit4();
};
