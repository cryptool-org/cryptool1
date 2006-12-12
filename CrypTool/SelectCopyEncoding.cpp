// SelectCopyEncoding.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "SelectCopyEncoding.h"

static int m_encode_type = 0;

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
	DDX_Radio(pDX, IDC_RADIO1, m_encode_type);
}


BEGIN_MESSAGE_MAP(CSelectCopyEncoding, CDialog)
END_MESSAGE_MAP()


// CSelectCopyEncoding message handlers

BOOL CSelectCopyEncoding::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	return TRUE;
}

int CSelectCopyEncoding::selectCopyEncoding(void)
{
	CSelectCopyEncoding dlg;
	if ( IDOK != dlg.DoModal() )
		return -1;

	return m_encode_type;
}
