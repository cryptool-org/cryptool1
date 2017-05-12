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

#ifndef _DLGCOMPUTEMERSENNENUMBERS_
#define _DLGCOMPUTEMERSENNENUMBERS_

#include "afxwin.h"
#include "NumberEdit.h"

// this is the timer ID for the dialog's timer
#define COMPUTE_MERSENNE_NUMBERS_TIMER_ID	9999

class CDlgComputeMersenneNumbers : public CDialog
{
	DECLARE_DYNAMIC(CDlgComputeMersenneNumbers)

public:
	CDlgComputeMersenneNumbers(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgComputeMersenneNumbers();

// Dialog Data
	enum { IDD = IDD_COMPUTE_MERSENNE_NUMBERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

protected:
	// the thread that computes the numbers
	CWinThread *computationThread;

	// some status flags
	bool running;
	bool canceled;
	bool done;

public:
	void setRunning(bool _running) { running = _running; };
	void setCanceled(bool _canceled) { canceled = _canceled; };
	void setDone(bool _done) { done = _done; };

public:
	bool isRunning() const { return running; }
	bool isCanceled() const { return canceled; }
	bool isDone() const { return done; }

protected:
	// start and end of computation
	time_t timeComputationStart;
	time_t timeComputationEnd;

protected:
	// we need these to enable/disable the buttons
	CNumberEdit numberEditBase;
	CNumberEdit numberEditExponent;
	CNumberEdit numberEditResult;
	CNumberEdit numberEditResultLength;
	CWnd *buttonStart;
	CWnd *buttonCancel;
	CWnd *buttonPrimeNumberTest;
	CWnd *buttonWriteResultToFile;
	CWnd *buttonClose;

public:
	// some random functions
	void setTimeComputationStart(const time_t _time) { timeComputationStart = _time; };
	void setTimeComputationEnd(const time_t _time) { timeComputationEnd = _time; };
	
public:
	// this function sets the result value displayed in the dialog; due to the potentially 
	// extremely large size of the result and the subsequent unresponsiveness of the GUI, 
	// we only write parts of the result back to the dialog if the result length exceeds 
	// a certain size (GUI_RESULT_LENGTH_LIMIT)
	void setResult(const std::string &_result);

public:
	// message handlers
	afx_msg void OnBnClickedStartComputation();
	afx_msg void OnBnClickedCancelComputation();
	afx_msg void OnBnClickedPrimeNumberTest();
	afx_msg void OnBnClickedWriteResultToFile();
	afx_msg void OnChangeEditBase();
	afx_msg void OnChangeEditExponent();
};

#endif