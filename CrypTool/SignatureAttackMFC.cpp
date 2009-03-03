/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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
