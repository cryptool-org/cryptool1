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


// SignatureAttackMFC.cpp: Implementierung der Klasse SignatureAttackMFC.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrypToolApp.h"
#include "SignatureAttackMFC.h"
#include "ErrorcodesForSignatureAttack.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

SignatureAttackMFC::SignatureAttackMFC()
{

}

SignatureAttackMFC::SignatureAttackMFC(OptionsForSignatureAttack *OptForSigAtt, FILE *SigAttTest,
									   int TotalAttemptsCounter, HWND hWnd, UINT messageID)
{
	m_TestFile = SigAttTest;
	m_TotalAttemptsCounter = TotalAttemptsCounter;
	m_Text[0] = 0;
	m_OptSigAtt = OptForSigAtt;
	m_hwnd = hWnd;
	m_messageID = messageID;
	m_ProgressText.LoadString(IDS_STRING_SIG_ATT_PROGRESS_CYCLE_SEARCH);
	m_ResSigAtt = new ResultsOfSignatureAttack(m_OptSigAtt->GetHashOp()->GetHashAlgorithmID(),
		m_OptSigAtt->GetSignificantBitLength());
}

SignatureAttackMFC::~SignatureAttackMFC()
{
	
}

void SignatureAttackMFC::StartShowProgress()
{

	m_SearchMode = IDS_STRING_SIG_ATT_PROGRESS_CYCLE_SEARCH;
	theApp.fs.setModelTitleFormat(this,IDS_STRING_SIG_ATT_FLOYD_RUNNING,"");
	theApp.fs.Display();

}

double SignatureAttackMFC::getProgress()
{
	double res;
	int run = m_ResSigAtt->GetRuns() - 1;
	if (IDS_STRING_SIG_ATT_PROGRESS_CYCLE_SEARCH == m_SearchMode)
	{
		res =  (double)m_ResSigAtt->GetCollisionStepsOfRun(run);
		res /= (double)m_ResSigAtt->GetExpectedSteps();
	}
	else
	{
		res =  (double)m_ResSigAtt->GetConfirmationStepsOfRun(run);
		res /= (double)m_ResSigAtt->GetCollisionStepsOfRun(run);
	}
	if ( res < 1e-100 ) res = 1e-100;
	CString f;
	f.Format(m_ProgressText,run+1, m_OptSigAtt->GetSignificantBitLength());
	theApp.fs.setFormat(f);
	if (res > 1.0)
		res = 1.0;
	return res;
}



bool SignatureAttackMFC::CheckCanceledProgress()
{
	if (theApp.fs.m_canceled)
	{
		m_ResSigAtt->SetFloydResult(_SIG_ATT_FLOYD_CANCELED);
		theApp.fs.cancel();
		SignalEnd();

		return true;
	}

	return false;
}

void SignatureAttackMFC::SignalEnd()
{
	PostMessage(m_hwnd, m_messageID, 3, 3);	
}

void SignatureAttackMFC::SetProgressTextNewRun(const bool IsNewRun)
{
	m_OldProgressPercentage = m_NewProgressPercentage = 0;

	if (true == IsNewRun)
	{
		m_SearchMode = IDS_STRING_SIG_ATT_PROGRESS_CYCLE_SEARCH;
		m_ProgressText.LoadString(IDS_STRING_SIG_ATT_PROGRESS_CYCLE_SEARCH);
	}
	else
	{
		m_SearchMode = IDS_STRING_SIG_ATT_PROGRESS_CYCLE_START;
		m_ProgressText.LoadString(IDS_STRING_SIG_ATT_PROGRESS_CYCLE_START);
	}
}
