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
#include "DlgCrypToolPRNGSeedCollector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgCrypToolPRNGSeedCollector::CDlgCrypToolPRNGSeedCollector(CWnd* pParent) :
	CDialog(CDlgCrypToolPRNGSeedCollector::IDD, pParent),
	seed(0),
	numberOfEventsProcessed(0),
	numberOfEventsNeeded(100)
{
	
}

void CDlgCrypToolPRNGSeedCollector::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_BAR, controlProgressBar);
}


BEGIN_MESSAGE_MAP(CDlgCrypToolPRNGSeedCollector, CDialog)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


BOOL CDlgCrypToolPRNGSeedCollector::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// init progress bar
	controlProgressBar.SetRange(0, numberOfEventsNeeded);
	controlProgressBar.SetPos(0);
	
	UpdateData(false);

	return TRUE;
}

BOOL CDlgCrypToolPRNGSeedCollector::PreTranslateMessage(MSG* pMsg) {
	if(pMsg->message == WM_KEYDOWN) {
		// TODO/FIXME: use something more random...
		seed += (unsigned long)(pMsg->lParam);
		seed += (unsigned long)(pMsg->wParam);
		numberOfEventsProcessed++;
		updateProgressBar();
		return true;
	}
	if(pMsg->message == WM_KEYUP) {
		// TODO/FIXME: use something more random...
		seed += (unsigned long)(pMsg->lParam);
		seed += (unsigned long)(pMsg->wParam);
		numberOfEventsProcessed++;
		updateProgressBar();
		return true;
	}
	if(pMsg->message == WM_MOUSEMOVE) {
		// TODO/FIXME: use something more random...
		seed += (unsigned long)(pMsg->lParam);
		seed += (unsigned long)(pMsg->wParam);
		numberOfEventsProcessed++;
		updateProgressBar();
		return true;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgCrypToolPRNGSeedCollector::updateProgressBar() {
	// update the progress bar
	controlProgressBar.SetPos(numberOfEventsProcessed);
	UpdateData(false);
	// check if we're done generating data
	if(numberOfEventsProcessed >= numberOfEventsNeeded)
		EndDialog(0);
}