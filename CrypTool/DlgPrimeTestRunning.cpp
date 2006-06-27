// DlgPrimeTestRunning.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgPrimeTestRunning.h"
#include ".\dlgprimetestrunning.h"

#include "windows.h"
#include "winuser.h"

// CDlgPrimeTestRunning-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgPrimeTestRunning, CDialog)
CDlgPrimeTestRunning::CDlgPrimeTestRunning(CWnd* pParent /*=NULL*/)
	: CDialog()
{
  Create(CDlgPrimeTestRunning::IDD, pParent);
  //{{[AFX_DATA_INIT(CDlgPrimeTestRunning)
  //}}AFX_DATA_INIT
  CenterWindow();
}

CDlgPrimeTestRunning::~CDlgPrimeTestRunning()
{
}

void CDlgPrimeTestRunning::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPrimeTestRunning, CDialog)
  ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgPrimeTestRunning-Meldungshandler

void CDlgPrimeTestRunning::OnBnClickedCancel()
{
  PostMessage(m_messageID,0,0);
  
  // OnCancel() doesn't work here, because of a bug in dlgcore 
	CDialog::OnCancel();
}

void CDlgPrimeTestRunning::CloseWindow()
{
  PostMessage(m_messageID,0,0);
  CDialog::OnCancel();
  //if (m_nFlags & (WF_MODALLOOP|WF_CONTINUEMODAL))
	//	EndModalLoop(IDOK);
}
BOOL CDlgPrimeTestRunning::OnInitDialog()
{
  CDialog::OnInitDialog();
  return TRUE;  // return TRUE unless you set the focus to a control
  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

INT_PTR CDlgPrimeTestRunning::DoModal()
{
  return CDialog::DoModal();
}

void CDlgPrimeTestRunning::SetMessageParam(UINT messageID)
{
  this->m_messageID = messageID;
}

void CDlgPrimeTestRunning::EndDialog(int nResult)
{
  PostMessage(m_messageID,0,0);
  CDialog::OnCancel();
  //if (m_nFlags & (WF_MODALLOOP|WF_CONTINUEMODAL))
	//	EndModalLoop(IDOK);
}
