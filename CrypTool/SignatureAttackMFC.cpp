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

SignatureAttackMFC::SignatureAttackMFC(OptionsForSignatureAttack *OptForSigAtt, HWND hWnd, UINT messageID)
{
	m_Text[0] = 0;
	m_OptSigAtt = OptForSigAtt;
	m_hwnd = hWnd;
	m_messageID = messageID;
	m_ProgressText.LoadString(IDS_STRING_SIG_ATT_PROGRESS_CYCLE_SEARCH);
	m_ResSigAtt = new ResultsOfSignatureAttack(m_OptSigAtt->GetSignificantBitLength());
}

SignatureAttackMFC::~SignatureAttackMFC()
{
	
}

void SignatureAttackMFC::StartShowProgress()
{
	CString msg;

	m_OldProgressPercentage = 0;
	m_SearchMode = IDS_STRING_SIG_ATT_PROGRESS_CYCLE_SEARCH;
	msg.LoadString(IDS_STRING_SIG_ATT_FLOYD_RUNNING);
	theApp.fs.Display(LPCTSTR(msg));
}

void SignatureAttackMFC::UpdateShowProgress()
{
	if (0 != m_ResSigAtt->GetTotalSteps() % 5000)
	{
		return;		// nur alle 5000 Schritte Fortschrittsanzeige updaten
	}

	if (IDS_STRING_SIG_ATT_PROGRESS_CYCLE_SEARCH == m_SearchMode)
	{
		if ((m_NewProgressPercentage =
			(m_ResSigAtt->GetCollisionStepsOfRun(m_ResSigAtt->GetRuns() - 1) * 100) / m_ResSigAtt->GetExpectedSteps())
			> m_OldProgressPercentage)	// wenn sich Prozentangabe geändert hat...
		{
			if (100 < m_NewProgressPercentage)
			{
				m_NewProgressPercentage = 100;	// mehr als 100% sind nicht möglich!
			}
			_snprintf(m_Text, sizeof(m_Text) - 1, m_ProgressText, m_ResSigAtt->GetRuns(), m_NewProgressPercentage);
		}
	}
	else
	{
		if ((m_NewProgressPercentage =
			(m_ResSigAtt->GetConfirmationStepsOfRun(m_ResSigAtt->GetRuns() - 1) * 100) /
			m_ResSigAtt->GetCollisionStepsOfRun(m_ResSigAtt->GetRuns() - 1))
			> m_OldProgressPercentage&& m_NewProgressPercentage <= 100)
		{
			if (100 < m_NewProgressPercentage)
			{
				m_NewProgressPercentage = 100;
			}
			_snprintf(m_Text, sizeof(m_Text) - 1, m_ProgressText, m_ResSigAtt->GetRuns(), m_NewProgressPercentage);
		}
	}
	
	theApp.fs.Set(m_OldProgressPercentage = m_NewProgressPercentage, "", m_Text);
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
