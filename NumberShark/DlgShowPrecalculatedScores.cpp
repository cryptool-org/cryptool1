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

// CDlgShowPrecalculatedScores dialog

IMPLEMENT_DYNAMIC(CDlgShowPrecalculatedScores, CDialog)

CDlgShowPrecalculatedScores::CDlgShowPrecalculatedScores(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowPrecalculatedScores::IDD, pParent)
{

}

CDlgShowPrecalculatedScores::CDlgShowPrecalculatedScores(std::map<int, GameDataBlock> _mapProved, std::map<int, GameDataBlock> _mapBestKnown, CWnd* pParent /*=NULL*/) :
	mapProved(_mapProved),
	mapBestKnown(_mapBestKnown),
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

	// display the dialog intro
	int numberOfProvedScores = mapProved.size();
	int numberOfBestKnownScores = mapBestKnown.size();
	intro.Format(IDS_PRECALCULATED_SCORES_INTRO, numberOfProvedScores, numberOfProvedScores + 1, numberOfProvedScores + numberOfBestKnownScores);

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

	// insert proved scores
	std::map<int, GameDataBlock>::iterator iterProved;
	for(iterProved = mapProved.begin(); iterProved != mapProved.end(); iterProved++) {
		int index = controlListPrecalculatedScores.GetItemCount();
		controlListPrecalculatedScores.InsertItem(index, "ITEM");
		controlListPrecalculatedScores.SetItemText(index, 0, (*iterProved).second.limit);
		controlListPrecalculatedScores.SetItemText(index, 1, (*iterProved).second.score);
		CString proved;
		proved.Format(IDS_PROVED_YES);
		controlListPrecalculatedScores.SetItemText(index, 2, proved);
	}

	// insert best-known scores
	std::map<int, GameDataBlock>::iterator iterBestKnown;
	for(iterBestKnown = mapBestKnown.begin(); iterBestKnown != mapBestKnown.end(); iterBestKnown++) {
		int index = controlListPrecalculatedScores.GetItemCount();
		controlListPrecalculatedScores.InsertItem(index, "ITEM");
		controlListPrecalculatedScores.SetItemText(index, 0, (*iterBestKnown).second.limit);
		controlListPrecalculatedScores.SetItemText(index, 1, (*iterBestKnown).second.score);
		CString proved;
		proved.Format(IDS_PROVED_NO);
		controlListPrecalculatedScores.SetItemText(index, 2, proved);
	}

	UpdateData(false);

	return true;
}

BEGIN_MESSAGE_MAP(CDlgShowPrecalculatedScores, CDialog)
	ON_BN_CLICKED(ID_SHOW_SEQUENCE, &CDlgShowPrecalculatedScores::OnBnClickedShowSequence)
END_MESSAGE_MAP()


// CDlgShowPrecalculatedScores message handlers

void CDlgShowPrecalculatedScores::OnBnClickedShowSequence()
{
	int selection = controlListPrecalculatedScores.GetSelectionMark();
	if(selection == -1) return;

	// the indices for our maps are NOT ZERO-BASED, therefore we 
	// need to increment "selection" to get the selected item
	selection++;

	// temporary structure
	GameDataBlock data;

	// check if a "proved" score is selected
	if(selection <= mapProved.size()) {
		data = mapProved[selection];
	}
	// check if a "best-known" score is selected
	else {
		data = mapBestKnown[selection];
	}

	// show the "optimal way"
	CString message;
	message.Format(IDS_SHOW_SEQUENCE_FOR_THIS_SPECIFIC_SCORE, data.limit, data.score, data.sequence);
	AfxMessageBox(message);
}
