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
CListResults::CListResults(const int &_numberOfBytesForEntropyCalculation, CWnd* pParent /*=NULL*/)
	: CDialog(CListResults::IDD, pParent)
	, headerStr(_T(""))
	, clist_size(0)
	, nItem(-1)
	, numberOfBytesForEntropyCalculation(_numberOfBytesForEntropyCalculation)
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
	ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL CListResults::OnInitDialog()
{
	CDialog::OnInitDialog();

	// flomar, 03/06/2010
	// as of today, the resource string IDS_LISTBRUTEFORCECANDIDATES_HEADER contains a format 
	// string wild-card (%d) for the number of bytes of the ciphertext that have been decrypted
	headerStr.Format(IDS_LISTBRUTEFORCECANDIDATES_HEADER, numberOfBytesForEntropyCalculation);

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

		int j;
		for (j=0; j<clist[i].plain_size && j<256; j++)
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

	// read window rects at dialog initialization
	GetWindowRect(&initialRectDialog);
	GetDlgItem(IDC_LIST4)->GetWindowRect(&initialRectList);
	GetDlgItem(IDOK)->GetWindowRect(&initialRectButtonOK);
	GetDlgItem(IDCANCEL)->GetWindowRect(&initialRectButtonCancel);

	UpdateData(false);

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

void CListResults::OnSize(UINT nType, int cx, int cy)
{
	CWnd *windowList = GetDlgItem(IDC_LIST4);
	CWnd *windowButtonOK = GetDlgItem(IDOK);
	CWnd *windowButtonCancel = GetDlgItem(IDCANCEL);

	// make sure we have valid pointers; if not, return
	if(!windowList || !windowButtonOK || !windowButtonCancel)
		return;

	// read the new dialog rect
	RECT newRectDialog;
	this->GetWindowRect(&newRectDialog);

	// return if the new dialog rect is smaller then the initial one
	int widthOld = initialRectDialog.right - initialRectDialog.left;
	int widthNew = newRectDialog.right - newRectDialog.left;
	int heightOld = initialRectDialog.bottom - initialRectDialog.top;
	int heightNew = newRectDialog.bottom - newRectDialog.top;
	if(widthNew < widthOld || heightNew < heightOld) {
		this->MoveWindow(newRectDialog.left, newRectDialog.top, widthOld, heightOld);
		return;
	}

	// compute new list window rect
	int marginRightList = initialRectDialog.right - initialRectList.right;
	int marginBottomList = initialRectDialog.bottom - initialRectList.bottom;
	int xList = initialRectList.left - initialRectDialog.left;
	int yList = initialRectList.top - initialRectDialog.top;
	int widthList = cx - xList - marginRightList;
	int heightList = cy - yList - marginBottomList;
	
	// compute new OK button rect
	int widthButtonOK = initialRectButtonOK.right - initialRectButtonOK.left;
	int heightButtonOK = initialRectButtonOK.bottom - initialRectButtonOK.top;
	int marginRightButtonOK = initialRectDialog.right - initialRectButtonOK.right;
	int marginBottomButtonOK = initialRectDialog.bottom - initialRectButtonOK.bottom;
	int xButtonOK = cx - widthButtonOK - marginRightButtonOK;
	int yButtonOK = cy - heightButtonOK - marginBottomButtonOK;

	// compute new CANCEL button rect
	int widthButtonCancel = initialRectButtonCancel.right - initialRectButtonCancel.left;
	int heightButtonCancel = initialRectButtonCancel.bottom - initialRectButtonCancel.top;
	int marginRightButtonCancel = initialRectDialog.right - initialRectButtonCancel.right;
	int marginBottomButtonCancel = initialRectDialog.bottom - initialRectButtonCancel.bottom;
	int xButtonCancel = cx - widthButtonCancel - marginRightButtonCancel;
	int yButtonCancel = cy - heightButtonCancel - marginBottomButtonCancel;

	// align dialog components
	windowList->MoveWindow(xList, yList, widthList, heightList);
	windowButtonOK->MoveWindow(xButtonOK, yButtonOK, widthButtonOK, heightButtonOK);
	windowButtonCancel->MoveWindow(xButtonCancel, yButtonCancel, widthButtonCancel, heightButtonCancel);

	Invalidate();
}

char* CListResults::get_keyhex()
 {
	if (nItem >= 0 && nItem < clist_size)
		return ((candidate*)clist+nItem)->key;
	else 
		return 0;
}
