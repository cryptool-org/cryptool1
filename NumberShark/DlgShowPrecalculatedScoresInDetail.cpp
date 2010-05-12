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

	// read window rects at dialog initialization
	GetWindowRect(&initialRectDialog);
	GetDlgItem(IDC_EDIT_PRECALCULATED_SCORES)->GetWindowRect(&initialRectEditScores);
	GetDlgItem(IDOK)->GetWindowRect(&initialRectButtonClose);

	UpdateData(false);

	return true;
}



BEGIN_MESSAGE_MAP(CDlgShowPrecalculatedScoresInDetail, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgShowPrecalculatedScoresInDetail message handlers

void CDlgShowPrecalculatedScoresInDetail::OnSize(UINT nType, int cx, int cy)
{
	CWnd *windowEditScores = GetDlgItem(IDC_EDIT_PRECALCULATED_SCORES);
	CWnd *windowButtonClose = GetDlgItem(IDOK);

	// make sure we have valid pointers; if not, return
	if(!windowEditScores || !windowButtonClose)
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

	// compute new edit scores window rect
	int marginRightList = initialRectDialog.right - initialRectEditScores.right;
	int marginBottomList = initialRectDialog.bottom - initialRectEditScores.bottom;
	int xList = initialRectEditScores.left - initialRectDialog.left;
	int yList = initialRectEditScores.top - initialRectDialog.top;
	int widthList = cx - xList - marginRightList;
	int heightList = cy - yList - marginBottomList;
	
	// compute new close button window rect
	int widthButtonClose = initialRectButtonClose.right - initialRectButtonClose.left;
	int heightButtonClose = initialRectButtonClose.bottom - initialRectButtonClose.top;
	int marginRightButtonClose = initialRectDialog.right - initialRectButtonClose.right;
	int marginBottomButtonClose = initialRectDialog.bottom - initialRectButtonClose.bottom;
	int xButtonClose = cx - widthButtonClose - marginRightButtonClose;
	int yButtonClose = cy - heightButtonClose - marginBottomButtonClose;

	// align dialog components
	windowEditScores->MoveWindow(xList, yList, widthList, heightList);
	windowButtonClose->MoveWindow(xButtonClose, yButtonClose, widthButtonClose, heightButtonClose);

	Invalidate();
}