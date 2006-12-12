// SelectCopyEncoding.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "SelectCopyEncoding.h"


// CSelectCopyEncoding dialog

IMPLEMENT_DYNAMIC(CSelectCopyEncoding, CDialog)
CSelectCopyEncoding::CSelectCopyEncoding(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectCopyEncoding::IDD, pParent)
{
}

CSelectCopyEncoding::~CSelectCopyEncoding()
{
}

void CSelectCopyEncoding::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ENCODING, ctrlComboEncoding);
}


BEGIN_MESSAGE_MAP(CSelectCopyEncoding, CDialog)
END_MESSAGE_MAP()


// CSelectCopyEncoding message handlers

BOOL CSelectCopyEncoding::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	ctrlComboEncoding.SetCurSel(0);
	// ctrlComboEncoding.Set
	return TRUE;
}

int CSelectCopyEncoding::selectCopyEncoding(void)
{
	CSelectCopyEncoding dlg;
	if ( IDOK != dlg.DoModal() )
		return -1;

	int retVal = dlg.ctrlComboEncoding.GetCurSel();
	return retVal;
}
