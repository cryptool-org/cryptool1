//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// OptionsDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgOptionsAnalysis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsAnalysis 


CDlgOptionsAnalysis::CDlgOptionsAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsAnalysis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsAnalysis)
	m_CKey = TRUE;
	m_CKorr = TRUE;
	m_CHist = TRUE;
	m_VKey = TRUE;
	m_VLen = TRUE;
	m_VKorr = TRUE;
	m_VBase = FALSE;
	m_BFEntropyWindow = 128;
	//}}AFX_DATA_INIT
}

static long GetWindowTextAsLong(CWnd *wnd)
{
	CString text;
	wnd->GetWindowText(text);
	return atol(text);
}

void CDlgOptionsAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	pDX->PrepareCtrl(IDC_EDIT_ENTROPY_WINDOW); // this is needed to set the focus to IDC_EDIT_ENTROPY_WINDOW if the following check fails
	// we do DDV_MinMaxLong before DDX_Text to prevent MFC from change the value of m_BFEntropyWindow to something
	// outside the valid range. This value would be kept even on pressing Cancel
	DDV_MinMaxLong(pDX, GetWindowTextAsLong(GetDlgItem(IDC_EDIT_ENTROPY_WINDOW)), 32, 4096); 
	//{{AFX_DATA_MAP(CDlgOptionsAnalysis)
	DDX_Check(pDX, IDC_CHECK1, m_CKey);
	DDX_Check(pDX, IDC_CHECK2, m_CKorr);
	DDX_Check(pDX, IDC_CHECK3, m_CHist);
	DDX_Check(pDX, IDC_CHECK6, m_VKey);
	DDX_Check(pDX, IDC_CHECK7, m_VLen);
	DDX_Check(pDX, IDC_CHECK8, m_VKorr);
	DDX_Check(pDX, IDC_CHECK4, m_VBase);
	DDX_Text(pDX, IDC_EDIT_ENTROPY_WINDOW, m_BFEntropyWindow);
	//}}AFX_DATA_MAP
	//DDV_MinMaxLong(pDX, m_BFEntropyWindow, 32, 4096); // see remark above
}


BEGIN_MESSAGE_MAP(CDlgOptionsAnalysis, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsAnalysis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

