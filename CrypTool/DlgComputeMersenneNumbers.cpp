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
#include "CrypToolApp.h"
#include "DlgComputeMersenneNumbers.h"

// include apfloat and utility headers
#include "../apfloat241/ap.h"
#include "../apfloat241/apint.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlgComputeMersenneNumbers dialog

IMPLEMENT_DYNAMIC(CDlgComputeMersenneNumbers, CDialog)

CDlgComputeMersenneNumbers::CDlgComputeMersenneNumbers(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgComputeMersenneNumbers::IDD, pParent)
{
	
}

CDlgComputeMersenneNumbers::~CDlgComputeMersenneNumbers()
{
	
}

void CDlgComputeMersenneNumbers::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BASE, stringBase);
	DDX_Text(pDX, IDC_EDIT_EXPONENT, stringExponent);
	DDX_Text(pDX, IDC_EDIT_RESULT, stringResult);
}

BEGIN_MESSAGE_MAP(CDlgComputeMersenneNumbers, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_START_COMPUTATION, &CDlgComputeMersenneNumbers::OnBnClickedStartComputation)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_COMPUTATION, &CDlgComputeMersenneNumbers::OnBnClickedCancelComputation)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CDlgComputeMersenneNumbers message handlers

BOOL CDlgComputeMersenneNumbers::OnInitDialog()
{
	CDialog::OnInitDialog();

	// get window handles to our buttons for enabling/disabling
	buttonStart = GetDlgItem(IDC_BUTTON_START_COMPUTATION);
	buttonCancel = GetDlgItem(IDC_BUTTON_CANCEL_COMPUTATION);
	assert(buttonStart);
	assert(buttonCancel);

	// enable start button, disable cancel button
	buttonStart->EnableWindow(true);
	buttonCancel->EnableWindow(false);

	return FALSE;
}

struct MersenneNumberComputationParameters {
	CDlgComputeMersenneNumbers *dialog;
	apint base;
	unsigned long exponent;
} mersenneComputationParameters;

UINT computeMersenneNumber(PVOID _parameters)
{
	// get parameters necessary for the computation
	MersenneNumberComputationParameters parameters = *(MersenneNumberComputationParameters*)(_parameters);

	// get the pointer to our dialog (the one that started this thread)
	CDlgComputeMersenneNumbers *dialog = parameters.dialog;
	
	// we go with base 10 by default
	apbase(10);

	// compute the mersenne number and store the time needed
	dialog->setTimeComputationStart(time(0));
	apint mersenneNumber = pow(parameters.base, parameters.exponent) - 1;
	dialog->setTimeComputationEnd(time(0));

	// convert apint to something readable
	std::ostringstream outbuffer;
	std::string buffer;
	outbuffer << mersenneNumber;
	buffer = outbuffer.str();

	// write the result back to the dialog
	dialog->setResult(buffer.c_str());

	// implicitly end this thread
	AfxEndThread(0);

	return 0;
}

void CDlgComputeMersenneNumbers::OnBnClickedStartComputation()
{
	UpdateData(true);

	// verification of "base" parameter
	if(stringBase.GetLength() == 0) {
		// TODO: throw error
		AfxMessageBox("TODO: no empty!");
		return;
	}
	for(int i=0; i<stringBase.GetLength(); i++) {
		if(stringBase[i] < '0' || stringBase[i] > '9') {
			// TODO: throw error
			AfxMessageBox("TODO: digits only!");
			return;
		}
	}

	// verification of "exponent" parameter
	if(stringExponent.GetLength() == 0) {
		// TODO: throw error
		AfxMessageBox("TODO: no empty!");
		return;
	}
	for(int i=0; i<stringExponent.GetLength(); i++) {
		if(stringExponent[i] < '0' || stringExponent[i] > '9') {
			// TODO: throw error
			AfxMessageBox("TODO: digits only!");
			return;
		}
	}

	// assign dialog object, base and exponent
	mersenneComputationParameters.dialog = this;
	mersenneComputationParameters.base = (char*)(LPCTSTR)(stringBase);
	mersenneComputationParameters.exponent = strtoul((LPCTSTR)(stringExponent), NULL, 10);

	// indicate that computation is running
	stringResult.Format(IDS_MERSENNE_NUMBER_COMPUTATION_RUNNING);

	// activate the timer (calls OnTimer every 10 ms)
	SetTimer(COMPUTE_MERSENNE_NUMBERS_TIMER_ID, 10, NULL);

	// disable start button, enable cancel button
	buttonStart->EnableWindow(false);
	buttonCancel->EnableWindow(true);

	// start the computation thread
	computationThread = AfxBeginThread(computeMersenneNumber, (PVOID)(&mersenneComputationParameters));

	UpdateData(false);
}

void CDlgComputeMersenneNumbers::OnBnClickedCancelComputation()
{
	// TODO
	computationThread->SuspendThread();

	// display some information for the user
	stringResult.Format(IDS_MERSENNE_NUMBER_COMPUTATION_CANCELLED);

	// enable start button, disable cancel button
	buttonStart->EnableWindow(true);
	buttonCancel->EnableWindow(false);

	UpdateData(false);
}

void CDlgComputeMersenneNumbers::OnTimer(UINT nIDEvent)
{
	// only process timer events that match our ID
	if (nIDEvent != COMPUTE_MERSENNE_NUMBERS_TIMER_ID) {
		CDialog::OnTimer(nIDEvent);
		return;
	}

	// this is quick and dirty... but it's working
	CString stringComputationRunning; stringComputationRunning.Format(IDS_MERSENNE_NUMBER_COMPUTATION_RUNNING);

	if(stringResult != stringComputationRunning) {
		// obviously, we have a result, so kill our timer
		KillTimer(COMPUTE_MERSENNE_NUMBERS_TIMER_ID);
		// enable start button, disable cancel button
		buttonStart->EnableWindow(true);
		buttonCancel->EnableWindow(false);
	}

	UpdateData(false);
}
