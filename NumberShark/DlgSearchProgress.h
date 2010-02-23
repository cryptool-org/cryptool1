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

#ifndef _DLGSEARCHPROGRESS_H_
#define _DLGSEARCHPROGRESS_H_

// this is our timer ID for the GUI update function
#define NUMBER_SHARK_SEARCH_TIMER_ID	8888

class CDlgSearchProgress : public CDialog
{
	DECLARE_DYNAMIC(CDlgSearchProgress)

public:
	CDlgSearchProgress(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSearchProgress();

	// show the dialog with a start time, an algorithm name and an upper limit
	void show(const long _start, const CString _algorithm, const int _limit);
	// hide the dialog (and do some clean-up work)
	void hide();

protected:
	// was the dialog created properly?
	bool created;

	// the start time (whenever the show() function was called)
	long start;
	// the name of the algorithm in use
	CString algorithm;
	// the upper limit (see NumberShark game)
	int limit;

	// the GUI update function
	void updateGUI();

// Dialog Data
	enum { IDD = IDD_SEARCH_PROGRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
};

#endif