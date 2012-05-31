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

#ifndef _DLGCRYPTOOLPRNGSEEDCOLLECTOR_H_
#define _DLGCRYPTOOLPRNGSEEDCOLLECTOR_H_

#include "afxwin.h"
#include "resource.h"

class CDlgCrypToolPRNGSeedCollector : public CDialog
{
public:
	CDlgCrypToolPRNGSeedCollector(CWnd* pParent = NULL);

	enum { IDD = IDD_CRYPTOOL_PRNG_SEED_COLLECTOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	afx_msg BOOL OnInitDialog();
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	
	DECLARE_MESSAGE_MAP()

protected:
	// counts how many events we've collected so far
	int numberOfEventsProcessed;
	// the minimum amount of events to be collected
	int numberOfEventsNeeded;
protected:
	unsigned long seed;
public:
	unsigned long getSeed() { return seed; }
protected:
	// the control for the progress bar
	CProgressCtrl controlProgressBar;
	// the control for the dice image
	CStatic controlDiceImage;
	// the bitmap for the dice image
	CBitmap bitmapDiceImage;
protected:
	// called whenever we've collected an event
	void updateProgressBar();
};

#endif
