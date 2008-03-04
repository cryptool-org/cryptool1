#pragma once
#include "afxcmn.h"


// CListResults dialog

class CListResults : public CDialog
{
	DECLARE_DYNAMIC(CListResults)

public:
	CListResults(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListResults();
	void LoadList(struct candidate *candidate_list, int listSize);

// Dialog Data
	enum { IDD = IDD_LIST_RESULTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	struct candidate *clist;
		   int        clist_size;
		   int		  nItem;

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl resultListCtrl;
	virtual BOOL OnInitDialog();
	CString headerStr;
	afx_msg void OnBnClickedOk();
	char *get_keyhex();

protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	RECT initialRectDialog;
	RECT initialRectList;
	RECT initialRectButtonOK;
	RECT initialRectButtonCancel;
};
