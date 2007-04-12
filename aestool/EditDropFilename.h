#pragma once


// CEditDropFilename

class CEditDropFilename : public CEdit
{
	DECLARE_DYNAMIC(CEditDropFilename)

public:
	CEditDropFilename();
	virtual ~CEditDropFilename();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDropFiles(HDROP hDropInfo);

protected:
	CString expandShortCut(LPTSTR);
};


