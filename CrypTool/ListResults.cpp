// ListResults.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "ListResults.h"
#include ".\listresults.h"


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


// CListResults message handlers

BOOL CListResults::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData();
	headerStr.LoadString(IDS_LISTBRUTEFORCECANDIDATES_HEADER);
	UpdateData(FALSE);
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
