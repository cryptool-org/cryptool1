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

// DlgShowPrecalculatedScoresInDetail.cpp : implementation file
//

#include "stdafx.h"
#include "MFC-ZahlenHai.h"
#include "DlgShowPrecalculatedScoresInDetail.h"

// CDlgShowPrecalculatedScoresInDetail dialog

IMPLEMENT_DYNAMIC(CDlgShowPrecalculatedScoresInDetail, CDialog)

CDlgShowPrecalculatedScoresInDetail::CDlgShowPrecalculatedScoresInDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowPrecalculatedScoresInDetail::IDD, pParent)
{

}

CDlgShowPrecalculatedScoresInDetail::CDlgShowPrecalculatedScoresInDetail(std::map<int, GameDataBlock> _mapPrecalculatedScores, CWnd* pParent /*=NULL*/) : 
	mapPrecalculatedScores(_mapPrecalculatedScores),
	CDialog(CDlgShowPrecalculatedScoresInDetail::IDD, pParent)
{

}

CDlgShowPrecalculatedScoresInDetail::~CDlgShowPrecalculatedScoresInDetail()
{
}

void CDlgShowPrecalculatedScoresInDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PRECALCULATED_SCORES, textPrecalculatedScores);
}

BOOL CDlgShowPrecalculatedScoresInDetail::OnInitDialog()
{
	CDialog::OnInitDialog();

	// create content for text field
	textPrecalculatedScores.Empty();

	// go through all scores and add them to the text field
	for(mapPrecalculatedScoresIter=mapPrecalculatedScores.begin();
			mapPrecalculatedScoresIter!=mapPrecalculatedScores.end();
			mapPrecalculatedScoresIter++) {

		CString stringHeading;

		stringHeading.Format(IDS_HEADING_NUMBER);
		textPrecalculatedScores.Append(stringHeading);
		textPrecalculatedScores.Append(": ");
		textPrecalculatedScores.Append((*mapPrecalculatedScoresIter).second.limit);
		textPrecalculatedScores.Append("\r\n");
		
		stringHeading.Format(IDS_HEADING_SCORE);
		textPrecalculatedScores.Append(stringHeading);
		textPrecalculatedScores.Append(": ");
		textPrecalculatedScores.Append((*mapPrecalculatedScoresIter).second.score);
		textPrecalculatedScores.Append("\r\n");
		
		stringHeading.Format(IDS_HEADING_PROVED);
		textPrecalculatedScores.Append(stringHeading);
		textPrecalculatedScores.Append(" ");
		CString proved;
		if((*mapPrecalculatedScoresIter).second.proved)
			proved.Format(IDS_PROVED_YES);
		else
			proved.Format(IDS_PROVED_NO);
		textPrecalculatedScores.Append(proved);
		textPrecalculatedScores.Append("\r\n");
		
		stringHeading.Format(IDS_HEADING_SEQUENCE_LENGTH);
		textPrecalculatedScores.Append(stringHeading);
		textPrecalculatedScores.Append(": ");
		textPrecalculatedScores.Append((*mapPrecalculatedScoresIter).second.sequenceLength);
		textPrecalculatedScores.Append("\r\n");
		
		stringHeading.Format(IDS_HEADING_SEQUENCE);
		textPrecalculatedScores.Append(stringHeading);
		textPrecalculatedScores.Append(": ");
		textPrecalculatedScores.Append((*mapPrecalculatedScoresIter).second.sequence);
		textPrecalculatedScores.Append("\r\n");

		textPrecalculatedScores.Append("\r\n");

	}

	UpdateData(false);

	return true;
}



BEGIN_MESSAGE_MAP(CDlgShowPrecalculatedScoresInDetail, CDialog)
END_MESSAGE_MAP()


// CDlgShowPrecalculatedScoresInDetail message handlers