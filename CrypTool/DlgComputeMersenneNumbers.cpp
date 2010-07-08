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
#include "FileTools.h"

// include apfloat and utility headers
#include "ap.h"
#include "apint.h"
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
	DDX_Control(pDX, IDC_EDIT_BASE, numberEditBase);
	DDX_Control(pDX, IDC_EDIT_EXPONENT, numberEditExponent);
	DDX_Control(pDX, IDC_EDIT_RESULT, numberEditResult);
	DDX_Control(pDX, IDC_EDIT_RESULT_LENGTH, numberEditResultLength);
}

BEGIN_MESSAGE_MAP(CDlgComputeMersenneNumbers, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_START_COMPUTATION, &CDlgComputeMersenneNumbers::OnBnClickedStartComputation)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_COMPUTATION, &CDlgComputeMersenneNumbers::OnBnClickedCancelComputation)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_RESULT_TO_FILE, &CDlgComputeMersenneNumbers::OnBnClickedWriteResultToFile)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT_BASE, &CDlgComputeMersenneNumbers::OnChangeEditBase)
	ON_EN_CHANGE(IDC_EDIT_EXPONENT, &CDlgComputeMersenneNumbers::OnChangeEditExponent)
END_MESSAGE_MAP()

// CDlgComputeMersenneNumbers message handlers

BOOL CDlgComputeMersenneNumbers::OnInitDialog()
{
	CDialog::OnInitDialog();

	// get window handles to our buttons for enabling/disabling
	buttonStart = GetDlgItem(IDC_BUTTON_START_COMPUTATION);
	buttonCancel = GetDlgItem(IDC_BUTTON_CANCEL_COMPUTATION);
	buttonWriteResultToFile = GetDlgItem(IDC_BUTTON_WRITE_RESULT_TO_FILE);

	assert(buttonStart);
	assert(buttonCancel);
	assert(buttonWriteResultToFile);

	// enable/disable buttons
	numberEditBase.EnableWindow(true);
	numberEditExponent.EnableWindow(true);
	buttonStart->EnableWindow(true);
	buttonCancel->EnableWindow(false);
	buttonWriteResultToFile->EnableWindow(false);
	numberEditResult.EnableWindow(false);
	numberEditResultLength.EnableWindow(false);

	// we go with base 2 by default
	numberEditBase.setText("2");
	numberEditExponent.setText("");

	UpdateData(false);

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
	dialog->setDone(true);
	dialog->setCanceled(false);
	dialog->setRunning(false);
	
	// implicitly end this thread
	AfxEndThread(0);

	return 0;
}

void CDlgComputeMersenneNumbers::OnBnClickedStartComputation()
{
	UpdateData(true);

	// assign dialog object, base and exponent
	mersenneComputationParameters.dialog = this;
	mersenneComputationParameters.base = (char*)(LPCTSTR)(numberEditBase.getNumberAsCString());
	mersenneComputationParameters.exponent = strtoul((LPCTSTR)(numberEditExponent.getNumberAsCString()), NULL, 10);

	// set some flags
	running = true;
	canceled = false;
	done = false;

	// indicate to the user that we're running
	CString stringInfo; stringInfo.Format(IDS_MERSENNE_NUMBER_COMPUTATION_RUNNING);
	numberEditResult.setText(stringInfo);

	// activate the timer (calls OnTimer every 10 ms)
	SetTimer(COMPUTE_MERSENNE_NUMBERS_TIMER_ID, 10, NULL);

	// enable/disable buttons
	numberEditBase.EnableWindow(false);
	numberEditExponent.EnableWindow(false);
	buttonStart->EnableWindow(false);
	buttonCancel->EnableWindow(true);
	buttonWriteResultToFile->EnableWindow(false);

	// flomar, 07/02/2010: hack of the day
	startApfloatComputation();

	// start the computation thread
	computationThread = AfxBeginThread(computeMersenneNumber, (PVOID)(&mersenneComputationParameters));

	UpdateData(false);
}

void CDlgComputeMersenneNumbers::OnBnClickedCancelComputation()
{
	// flomar, 07/02/2010: hack of the day
	cancelApfloatComputation();

	// set some flags
	running = false;
	canceled = true;
	done = false;

	// indicate to the user that the computation was canceled
	CString stringInfo; stringInfo.Format(IDS_MERSENNE_NUMBER_COMPUTATION_CANCELLED);
	numberEditResult.setText(stringInfo);

	// enable/disable buttons
	numberEditBase.EnableWindow(true);
	numberEditExponent.EnableWindow(true);
	buttonStart->EnableWindow(true);
	buttonCancel->EnableWindow(false);
	buttonWriteResultToFile->EnableWindow(false);

	UpdateData(false);
}

void CDlgComputeMersenneNumbers::OnBnClickedWriteResultToFile()
{
	// create temporary file name
	char *filename = new char[CRYPTOOL_PATH_LENGTH];
	GetTmpName(filename, "cry", ".txt");

	ofstream Outfile;
	Outfile.open(filename, std::ios::out | std::ios::trunc);
	Outfile << numberEditResult.getNumberAsCString();
	Outfile.close();

	CAppDocument *NewDoc = theApp.OpenDocumentFileNoMRU(filename);

	delete filename;	
}

void CDlgComputeMersenneNumbers::OnChangeEditBase()
{
	UpdateData(true);

	// clear result fields
	numberEditResult.setText("");
	numberEditResultLength.setText("");

	UpdateData(false);
}

void CDlgComputeMersenneNumbers::OnChangeEditExponent()
{
	UpdateData(true);

	// clear result fields
	numberEditResult.setText("");
	numberEditResultLength.setText("");

	UpdateData(false);
}

void CDlgComputeMersenneNumbers::OnTimer(UINT nIDEvent)
{
	// only process timer events that match our ID
	if (nIDEvent != COMPUTE_MERSENNE_NUMBERS_TIMER_ID) {
		CDialog::OnTimer(nIDEvent);
		return;
	}

	if(!running) {
		// obviously, we have a result, so kill our timer
		KillTimer(COMPUTE_MERSENNE_NUMBERS_TIMER_ID);

		// enable/disable buttons
		numberEditBase.EnableWindow(true);
		numberEditExponent.EnableWindow(true);
		buttonStart->EnableWindow(true);
		buttonCancel->EnableWindow(false);
		buttonWriteResultToFile->EnableWindow(false);
		
		if(done) {
			// we really do have a result (no cancellation), enable the write result to file button
			buttonWriteResultToFile->EnableWindow(true);
			// also update the result length
			CString stringResultLength; stringResultLength.Format("%d", numberEditResult.getNumberAsCString().GetLength());
			numberEditResultLength.setNumber(stringResultLength);
			// display the amount of time needed for the calculation (if it's longer than a sec)
			double timeNeeded = difftime(timeComputationEnd, timeComputationStart);
			if(timeNeeded > 1.0f) {
				CString stringTimeNeeded;
				stringTimeNeeded.Format(IDS_MERSENNE_NUMBER_COMPUTATION_TIME_NEEDED, timeNeeded);
				AfxMessageBox(stringTimeNeeded);
			}
		}
	}

	UpdateData(false);
}
