// ListResults.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "ListResults.h"
#include ".\listresults.h"
#include "bruteforceheap.h"

// CListResults dialog

IMPLEMENT_DYNAMIC(CListResults, CDialog)
CListResults::CListResults(CWnd* pParent /*=NULL*/)
	: CDialog(CListResults::IDD, pParent)
	, headerStr(_T(""))
{
}

CListResults::~CListResults()
{
}

void CListResults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST4, resultListCtrl);
	DDX_Text(pDX, IDC_HEADER, headerStr);
}


BEGIN_MESSAGE_MAP(CListResults, CDialog)
END_MESSAGE_MAP()


BOOL CListResults::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData();
	headerStr.LoadString(IDS_LISTBRUTEFORCECANDIDATES_HEADER);
	UpdateData(FALSE);
	// TODO:  Add extra initialization here

	resultListCtrl.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	resultListCtrl.InsertColumn(1, "Entropy", LVCFMT_LEFT, 70, 1);
	resultListCtrl.InsertColumn(2, "Decryption Hex-Dump", LVCFMT_LEFT, 350, 2);
	resultListCtrl.InsertColumn(3, "Decryption", LVCFMT_LEFT, 250, 3);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
