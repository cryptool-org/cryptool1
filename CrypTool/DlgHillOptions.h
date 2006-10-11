#pragma once


// DlgHillOptions dialog

class DlgHillOptions : public CDialog
{
	DECLARE_DYNAMIC(DlgHillOptions)

public:
	DlgHillOptions(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgHillOptions();

	unsigned long firstPosNull;

// Dialog Data
	enum { IDD = IDD_Hill_Options };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog();
	void OnOK();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
