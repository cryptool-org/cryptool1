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

	int intQualityKeePass;
	int intQualityMozilla;
	int intQualityPGP;
	int intQualityAverage;
	
	CString stringQualityKeePass;
	CString stringQualityMozilla;
	CString stringQualityPGP;
	CString stringQualityAverage;

	CProgressCtrl controlQualityKeePass;
	CProgressCtrl controlQualityMozilla;
	CProgressCtrl controlQualityPGP;
	CProgressCtrl controlQualityAverage;
};
