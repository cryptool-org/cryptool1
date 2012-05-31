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
	numberOfEventsNeeded(256)
{
	// initialize the bitmap
	bitmapDiceImage.LoadBitmapA(IDB_DICE_IMAGE);
}

void CDlgCrypToolPRNGSeedCollector::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_BAR, controlProgressBar);
	DDX_Control(pDX, IDC_DICE_IMAGE, controlDiceImage);
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
	// set the dice image
	controlDiceImage.SetBitmap(bitmapDiceImage);
	
	UpdateData(false);

	return TRUE;
}

BOOL CDlgCrypToolPRNGSeedCollector::PreTranslateMessage(MSG* pMsg) {
	// react to key presses, key releases, and mouse movement
	if(	pMsg->message == WM_KEYDOWN ||
			pMsg->message == WM_KEYUP ||
			pMsg->message == WM_MOUSEMOVE) {
				// use message params and clock() to generate some random data
				seed += (unsigned long)(pMsg->lParam) + (unsigned long)(clock());
				seed += (unsigned long)(pMsg->wParam) + (unsigned long)(clock());
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