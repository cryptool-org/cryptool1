#pragma once
#include "afxcmn.h"
#include "DynTabCtrl.h"


// propPage1-Dialogfeld

class propPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(propPage1)

public:
	propPage1();
	virtual ~propPage1();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	DynTabCtrl tabctrl;
	virtual BOOL OnInitDialog();
};
