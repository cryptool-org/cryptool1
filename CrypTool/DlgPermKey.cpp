// DlgPermKey.cpp : implementation file
//

#include "stdafx.h"
#include "DlgPermKey.h"


// CDlgPermKey dialog

IMPLEMENT_DYNAMIC(CDlgPermKey, CDialog)

CDlgPermKey::CDlgPermKey(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPermKey::IDD, pParent)
	, m_permKey1(_T(""))
	, m_inDir1(_T(""))
	, m_permDir1(_T(""))
	, m_outDir1(_T(""))
{

}

CDlgPermKey::~CDlgPermKey()
{
}

void CDlgPermKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PERMKEY1, m_permKey1);
	DDX_Text(pDX, IDC_inDir1, m_inDir1);
	DDX_Text(pDX, IDC_permDir1, m_permDir1);
	DDX_Text(pDX, IDC_OUTDIR1, m_outDir1);
}


BEGIN_MESSAGE_MAP(CDlgPermKey, CDialog)
END_MESSAGE_MAP()

void CDlgPermKey::setPermKey1(const permkey *key)
{
	int i;
	char num[20];
	for (i=0; i<key->permSize-1; i++)
	{
		_itoa(key->permKey[i], num, 10);
		m_permKey1 += num;
	    m_permKey1 += _T(", ");
	}
	_itoa(key->permKey[i], num, 10);
	m_permKey1 += num;
	m_inDir1.LoadStringA( (key->dirPlain == col_dir) ? IDS_IOP_COL : IDS_IOP_ROW );
	m_permDir1.LoadStringA( (key->dirPerm == col_dir) ? IDS_IOP_COL : IDS_IOP_ROW );
	m_outDir1.LoadStringA( (key->dirCipher == col_dir) ? IDS_IOP_COL : IDS_IOP_ROW );
}



// CDlgPermKey message handlers
