// DlgPorts.cpp : implementation file
//

#include "stdafx.h"
#include "DlgPorts.h"

// CDlgPorts dialog

IMPLEMENT_DYNAMIC(CDlgPorts, CDialog)

CDlgPorts::CDlgPorts(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPorts::IDD, pParent)
{

}

CDlgPorts::~CDlgPorts()
{
}

void CDlgPorts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPorts, CDialog)
END_MESSAGE_MAP()

BOOL CDlgPorts::OnInitDialog() 
{
	CDialog::OnInitDialog();

	UpdateData(false);
	
	return TRUE;
}