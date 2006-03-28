#pragma once


// DlgAdfgvxIntro-Dialogfeld

class DlgAdfgvxIntro : public CDialog
{
	DECLARE_DYNAMIC(DlgAdfgvxIntro)

public:
	DlgAdfgvxIntro(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~DlgAdfgvxIntro();

// Dialogfelddaten
	enum { IDD = IDD_ADFGVX_INTRO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
private:
	BOOL noIntro;
public:
	afx_msg void OnBnClickedCheck1();
};
