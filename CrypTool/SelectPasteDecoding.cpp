// SelectPasteDecoding.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "SelectPasteDecoding.h"

static int m_decode_type = 0;

// CSelectPasteDecoding dialog

IMPLEMENT_DYNCREATE(CSelectPasteDecoding, CDialog)

CSelectPasteDecoding::CSelectPasteDecoding(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectPasteDecoding::IDD, pParent)
{
}

CSelectPasteDecoding::~CSelectPasteDecoding()
{
}

void CSelectPasteDecoding::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_decode_type);
}

BOOL CSelectPasteDecoding::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CSelectPasteDecoding, CDialog)
END_MESSAGE_MAP()


int CSelectPasteDecoding::selectPasteDecoding(void)
{
	CSelectPasteDecoding dlg;
	if ( IDOK != dlg.DoModal() )
		return -1;

	return m_decode_type;
}