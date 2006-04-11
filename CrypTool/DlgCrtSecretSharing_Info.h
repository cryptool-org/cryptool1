#pragma once


// DlgCrtSecretSharing_Info-Dialogfeld

class DlgCrtSecretSharing_Info : public CDialog
{
	DECLARE_DYNAMIC(DlgCrtSecretSharing_Info)

public:
	DlgCrtSecretSharing_Info(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~DlgCrtSecretSharing_Info();

// Dialogfelddaten
	enum { IDD = IDD_CRT_SECRETSHARING_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_checkInfo;
};
