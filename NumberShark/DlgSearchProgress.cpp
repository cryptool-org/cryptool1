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

#include "stdafx.h"
#include "MFC-ZahlenHai.h"
#include "DlgSearchProgress.h"
#include "MFC-ZahlenHaiDlg.h"

extern SearchStatus searchStatus;

// CDlgSearchProgress dialog

IMPLEMENT_DYNAMIC(CDlgSearchProgress, CDialog)

CDlgSearchProgress::CDlgSearchProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSearchProgress::IDD, pParent)
{
	created = false;

	start = 0;
	algorithm = "";
	limit = 0;
}

CDlgSearchProgress::~CDlgSearchProgress()
{
}

void CDlgSearchProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSearchProgress, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgSearchProgress message handlers

void CDlgSearchProgress::show(const long _start, const CString _algorithm, const int _limit)
{
	// assign parameters
	start = _start;
	algorithm = _algorithm;
	limit = _limit;

	// create the dialog (if necessary) and show it
	if(!created) {
		Create(CDlgSearchProgress::IDD);
		created = true;
	}
	ShowWindow(SW_SHOW);

	// start the timer: call our callback function every 500 ms
	SetTimer(NUMBER_SHARK_SEARCH_TIMER_ID, 500, NULL);
}

void CDlgSearchProgress::hide() 
{
	// stop the timer
	KillTimer(NUMBER_SHARK_SEARCH_TIMER_ID);

	// hide the dialog
	ShowWindow(SW_HIDE);
}

void CDlgSearchProgress::OnTimer(UINT nIDEvent) 
{
	// update the GUI (in particular: the display for the elapsed time)
	updateGUI();

	// check if the search is done and we need to close the dialog
	if(searchStatus == ABORTED || searchStatus == DONE) hide();

	CWnd::OnTimer(nIDEvent);
}

void CDlgSearchProgress::updateGUI()
{
	// get a pointer to the text window (for algorithm and limit)
	CWnd *textWindow = GetDlgItem(IDC_TEXT_SEARCH_PROGRESS_1);
	if(textWindow) {
		// update the window text
		CString text; text.Format(IDS_SEARCH_PROGRESS_TEXT_1, algorithm, limit);
		textWindow->SetWindowText(text);
	}
	// get a pointer to the elapsed time window
	CWnd *elapsedTimeWindow = GetDlgItem(IDC_TEXT_SEARCH_PROGRESS_2);
	if(elapsedTimeWindow) {
		// determine the elapsed time
		long secondsElapsed = (clock() - start) / 1000;
		// update the window text
		CString text; text.Format(IDS_SEARCH_PROGRESS_TEXT_2, secondsElapsed);
		elapsedTimeWindow->SetWindowText(text);
	}

	UpdateData(false);
}

BOOL CDlgSearchProgress::OnInitDialog()
{
	CDialog::OnInitDialog();

	// update the GUI initially
	updateGUI();

	return FALSE;
}

void CDlgSearchProgress::OnCancel()
{
	// indicate we're done
	searchStatus = ABORTED;

	CDialog::OnCancel();
}