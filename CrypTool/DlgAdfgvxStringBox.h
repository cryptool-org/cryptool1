#pragma once


// DlgAdfgvxStringBox-Dialogfeld

class DlgAdfgvxStringBox : public CDialog
{
	DECLARE_DYNAMIC(DlgAdfgvxStringBox)

public:
	DlgAdfgvxStringBox(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~DlgAdfgvxStringBox();

// Dialogfelddaten
	enum { IDD = IDD_ADFGVX_STRINGBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CString GetInput();
	afx_msg void OnBnClickedOk();
	afx_msg void OnOk();

private:
	CString input;
	void DlgAdfgvxStringBox::OnOK();
	BOOL DlgAdfgvxStringBox::OnInitDialog();
};
