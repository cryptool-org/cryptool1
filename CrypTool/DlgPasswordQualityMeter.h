#pragma once


// CDlgPasswordQualityMeter-Dialogfeld

class CDlgPasswordQualityMeter : public CDialog
{
public:
	CDlgPasswordQualityMeter(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgPasswordQualityMeter();

// Dialogfelddaten
	enum { IDD = IDD_PASSWORDQUALITYMETER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	virtual void EditPasswordChanged();
	virtual void UpdateUserInterface();

	DECLARE_MESSAGE_MAP()

private:
	CString password;
	BOOL showPassword;
	BOOL useCrypToolAlphabet;

	int intQualityKeePass;
	int intQualityMozilla;
	int intQualityPGP;
	int intQualityCrypTool;
	
	CString stringQualityKeePass;
	CString stringQualityMozilla;
	CString stringQualityPGP;
	CString stringQualityCrypTool;

	CProgressCtrl controlQualityKeePass;
	CProgressCtrl controlQualityMozilla;
	CProgressCtrl controlQualityPGP;
	CProgressCtrl controlQualityCrypTool;
public:
	afx_msg void OnBnClickedCheckUsecryptoolalphabet();
	afx_msg void OnBnClickedCheckShowpassword();
};