#pragma once
#include "afxcmn.h"


// CListResults dialog

class CListResults : public CDialog
{
	DECLARE_DYNAMIC(CListResults)

public:
	CListResults(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListResults();

// Dialog Data
	enum { IDD = IDD_LIST_RESULTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl resultListCtrl;
	virtual BOOL OnInitDialog();
	CString headerStr;
};
