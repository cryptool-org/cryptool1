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
		res =  m_ResSigAtt->GetCollisionStepsOfRun(run);
		res /= m_ResSigAtt->GetExpectedSteps();
	}
	else
	{
		res =  m_ResSigAtt->GetConfirmationStepsOfRun(run);
		res /= m_ResSigAtt->GetCollisionStepsOfRun(run);
	}
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
