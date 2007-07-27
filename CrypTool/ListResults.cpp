// ListResults.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "ListResults.h"
#include ".\listresults.h"
#include "bruteforceheap.h"
#include "DialogeMessage.h"

// CListResults dialog

IMPLEMENT_DYNAMIC(CListResults, CDialog)
CListResults::CListResults(CWnd* pParent /*=NULL*/)
	: CDialog(CListResults::IDD, pParent)
	, headerStr(_T(""))
	, clist_size(0)
	, nItem(-1)
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
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CListResults::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData();
	headerStr.LoadString(IDS_LISTBRUTEFORCECANDIDATES_HEADER);
	UpdateData(FALSE);
	// TODO:  Add extra initialization here

	CString ColumnText;
	resultListCtrl.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	ColumnText.LoadString(IDS_STRING_TITLE_ENTROPY);
	resultListCtrl.InsertColumn(1, ColumnText.GetBuffer(), LVCFMT_LEFT, 70, 1);
	ColumnText.LoadString(IDS_DECRYPTION_HEADER);
	resultListCtrl.InsertColumn(2, ColumnText.GetBuffer(), LVCFMT_LEFT, 300, 2);
	ColumnText.LoadString(IDS_DECRYPTION_HEADER_HEX_DUMP);
	resultListCtrl.InsertColumn(3, ColumnText.GetBuffer(), LVCFMT_LEFT, 700, 3);

	for ( int i=0; i<clist_size; i++)
	{
		char str[256+1], strhex[256*3];
		sprintf(str, "%3.4f", clist[i].entropy);
		resultListCtrl.InsertItem(i, str);
		str[0] = strhex[0] = '\0';
		for (int j=0; j<clist[i].plain_size && j<256; j++)
		{
			str[j] = ( (unsigned char)clist[i].plain[j] >= 32 
				    && (unsigned char)clist[i].plain[j] < 128 ) 
					? clist[i].plain[j] : '.';
			sprintf(strhex+3*j, "%02X ", (unsigned char)clist[i].plain[j]);
		}
		str[j] = '\0';
		resultListCtrl.SetItemText(i,1, strhex);
		resultListCtrl.SetItemText(i,2, str);
	}

	resultListCtrl.SetItem(0, 0, LVIF_STATE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED, 0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CListResults::LoadList(struct candidate *candidate_list, int listSize)
{
	clist = candidate_list;
	clist_size = listSize;
}

void CListResults::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	POSITION p = resultListCtrl.GetFirstSelectedItemPosition();
	
	if ( p ) {
		nItem = resultListCtrl.GetNextSelectedItem(p);
		OnOK();
	}
	else
	{
		nItem = -1;
		Message(IDS_NO_ITEM_SELECTED, MB_ICONINFORMATION);
	}
}


char* CListResults::get_keyhex()
 {
	if (nItem >= 0 && nItem < clist_size)
		return ((candidate*)clist+nItem)->key;
	else 
		return 0;
}
