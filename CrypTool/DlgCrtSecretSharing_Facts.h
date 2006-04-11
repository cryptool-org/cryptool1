#pragma once


// CDlgCrtSecretSharing_Facts-Dialogfeld

class CDlgCrtSecretSharing_Facts : public CDialog
{
	DECLARE_DYNAMIC(CDlgCrtSecretSharing_Facts)

public:
	CDlgCrtSecretSharing_Facts(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgCrtSecretSharing_Facts();

// Dialogfelddaten
	enum { IDD = IDD_CRT_SECRETSHARING_FACTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_min_k;
	CString m_max_kminus1;
	CString m_w;
	CString m_s;
	CString m_a;
	CString m_s_;
	int m_need;
	int m_anzahl;
	CString m_log;
	afx_msg void OnBnClickedCrtShowlog();
	afx_msg void OnBnClickedOk();
	CString m_CrtFacts1;
	CString m_CrtFacts2;
};
