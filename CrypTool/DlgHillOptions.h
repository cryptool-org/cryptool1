#pragma once


// DlgHillOptions dialog

class DlgHillOptions : public CDialog
{
	DECLARE_DYNAMIC(DlgHillOptions)

public:
	DlgHillOptions(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgHillOptions();

	unsigned long firstPosNull;
	unsigned long useFirstCharFromAlph;

	bool isInAlph(CString strChar);

// Dialog Data
	enum { IDD = IDD_Hill_Options };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog();
	void OnOK();
	void EnableFirstPosNull();
	void DisableFirstPosNull();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_FirstCharFromAlph;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	CString m_ownCharForPadding;
	afx_msg void OnEnChangeEdit2();
};
