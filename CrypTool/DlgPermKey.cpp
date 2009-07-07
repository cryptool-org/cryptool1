/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

// DlgPermKey.cpp : implementation file
//

#include "stdafx.h"
#include "DlgPermKey.h"
#include "DlgKeyPermutation.h"
#include "KeyRepository.h"
#include "resource.h"

// CDlgPermKey dialog

IMPLEMENT_DYNAMIC(CDlgPermKey, CDialog)

CDlgPermKey::CDlgPermKey(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPermKey::IDD, pParent)
	, m_permKey1(_T(""))
	, m_inDir1(_T(""))
	, m_permDir1(_T(""))
	, m_outDir1(_T(""))
{
	int inDir1 = inDir2 = 0;
	permDir1 = outDir1 = permDir2 = outDir2 = 0;
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
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgPermKey::OnBnClickedCopyKey)
END_MESSAGE_MAP()

void CDlgPermKey::setPermKey1(const permkey *key, int dataType)
{
	int i;
	char num[20];
	for (i=1; i<key->permSize; i++)
	{
		_itoa(key->permKey[i], num, 10);
		m_permKey1 += num;
	    m_permKey1 += _T(", ");
	}
	_itoa(key->permKey[i], num, 10);
	m_permKey1 += num;
	m_dataType = dataType;

	inDir1   = key->dirPlain;
	permDir1 = key->dirPerm;
	outDir1  = key->dirCipher;
	m_inDir1.LoadStringA  ( (inDir1   == col_dir) ? IDS_IOP_COL : IDS_IOP_ROW );
	m_permDir1.LoadStringA( (permDir1 == col_dir) ? IDS_IOP_COL : IDS_IOP_ROW );
	m_outDir1.LoadStringA ( (outDir1  == col_dir) ? IDS_IOP_COL : IDS_IOP_ROW );
}



// CDlgPermKey message handlers
#define PARAM_TOKEN "PARAMETER: "

void CDlgPermKey::OnBnClickedCopyKey()
{
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PERMUTATION,pc_str,STR_LAENGE_STRING_TABLE);
	CString strKey;
	strKey.Format("%s %s%s%i,%i,%i,%i,%i,%i", 
		m_permKey1, PARAM_TOKEN, (m_dataType) ? TEXT_TOKEN : BINARY_TOKEN, inDir1, permDir1, outDir1, inDir2, permDir2, outDir2);
	CopyKey ( pc_str, strKey );
	// TODO: Add your control notification handler code here
}
