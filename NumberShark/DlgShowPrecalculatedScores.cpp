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

// DlgShowPrecalculatedScores.cpp : implementation file
//

#include "stdafx.h"
#include "MFC-ZahlenHai.h"
#include "DlgShowPrecalculatedScores.h"
#include "DlgShowPrecalculatedScoresInDetail.h"

// CDlgShowPrecalculatedScores dialog

IMPLEMENT_DYNAMIC(CDlgShowPrecalculatedScores, CDialog)

CDlgShowPrecalculatedScores::CDlgShowPrecalculatedScores(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowPrecalculatedScores::IDD, pParent)
{

}

CDlgShowPrecalculatedScores::CDlgShowPrecalculatedScores(std::map<int, GameDataBlock> _mapPrecalculatedScores, CWnd* pParent /*=NULL*/) :
	mapPrecalculatedScores(_mapPrecalculatedScores),
	CDialog(CDlgShowPrecalculatedScores::IDD, pParent)
{

}

CDlgShowPrecalculatedScores::~CDlgShowPrecalculatedScores()
{
}

void CDlgShowPrecalculatedScores::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PRECALCULATED_SCORES, controlListPrecalculatedScores);
	DDX_Text(pDX, IDC_STATIC_INTRO, intro);
}

BOOL CDlgShowPrecalculatedScores::OnInitDialog()
{
	CDialog::OnInitDialog();

	// display the dialog intro (we need the amount of proved and best-known scores)
	int numberOfProvedScores = 0;
	int numberOfBestKnownScores = 0;

	for(mapPrecalculatedScoresIter=mapPrecalculatedScores.begin(); 
			mapPrecalculatedScoresIter!=mapPrecalculatedScores.end(); 
			mapPrecalculatedScoresIter++) {
		if((*mapPrecalculatedScoresIter).second.proved)
			numberOfProvedScores++;
		else
			numberOfBestKnownScores++;
	}

	intro.Format(IDS_PRECALCULATED_SCORES_INTRO, numberOfProvedScores, numberOfProvedScores + 1, numberOfProvedScores + numberOfBestKnownScores, numberOfProvedScores);

	// clear the score list
	controlListPrecalculatedScores.DeleteAllItems();
	// set some extended styles
	controlListPrecalculatedScores.SetExtendedStyle(controlListPrecalculatedScores.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	// add column headers
	CString columnHeader;
	columnHeader.Format(IDS_HEADING_NUMBER);
	controlListPrecalculatedScores.InsertColumn(0, columnHeader, LVCFMT_LEFT, 110);
	columnHeader.Format(IDS_HEADING_SCORE);
	controlListPrecalculatedScores.InsertColumn(1, columnHeader, LVCFMT_LEFT, 110);
	columnHeader.Format(IDS_HEADING_PROVED);
	controlListPrecalculatedScores.InsertColumn(2, columnHeader, LVCFMT_LEFT, 110);

	// insert scores
	for(mapPrecalculatedScoresIter=mapPrecalculatedScores.begin(); 
			mapPrecalculatedScoresIter!=mapPrecalculatedScores.end(); 
			mapPrecalculatedScoresIter++) {
		int index = controlListPrecalculatedScores.GetItemCount();
		controlListPrecalculatedScores.InsertItem(index, "ITEM");
		controlListPrecalculatedScores.SetItemText(index, 0, (*mapPrecalculatedScoresIter).second.limit);
		controlListPrecalculatedScores.SetItemText(index, 1, (*mapPrecalculatedScoresIter).second.score);
		CString proved;
		if((*mapPrecalculatedScoresIter).second.proved)
			proved.Format(IDS_PROVED_YES);
		else
			proved.Format(IDS_PROVED_NO);
		controlListPrecalculatedScores.SetItemText(index, 2, proved);
	}

	UpdateData(false);

	return true;
}

BEGIN_MESSAGE_MAP(CDlgShowPrecalculatedScores, CDialog)
	ON_BN_CLICKED(ID_SHOW_DETAILS, OnBnClickedShowSequence)
END_MESSAGE_MAP()


// CDlgShowPrecalculatedScores message handlers

void CDlgShowPrecalculatedScores::OnBnClickedShowSequence()
{
	// TODO: show all results in a window (for copy-paste)
	CDlgShowPrecalculatedScoresInDetail dlg(mapPrecalculatedScores);
	dlg.DoModal();
}
