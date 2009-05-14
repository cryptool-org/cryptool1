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


// SignatureAttackMFC.h: Schnittstelle für die Klasse SignatureAttackMFC.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGNATUREATTACKMFC_H__8BCF9CB3_E0C4_11D6_9DF9_000629718A52__INCLUDED_)
#define AFX_SIGNATUREATTACKMFC_H__8BCF9CB3_E0C4_11D6_9DF9_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SignatureAttack.h"


class SignatureAttackMFC : public SignatureAttack, public CProgressModel
{
public:
	SignatureAttackMFC();
	SignatureAttackMFC(OptionsForSignatureAttack *OptForSigAtt, FILE *SigAttTest,
									   int TotalAttemptsCounter, HWND hWnd, UINT messageID);
	virtual ~SignatureAttackMFC();
	static UINT StaticThreadFunction(void * param)
	{
		SignatureAttack *SA = (SignatureAttack *) param;
		ASSERT(NULL != SA);
		return SA->Do_Floyd();
	}

private:
	char m_Text[256];
	int m_SearchMode;
	CString m_ProgressText;
	HWND m_hwnd;
	__int64 m_OldProgressPercentage;
	__int64 m_NewProgressPercentage;
	UINT m_messageID;

	virtual bool CheckCanceledProgress();
	virtual void StartShowProgress();
	virtual double getProgress();
	virtual void SignalEnd();
	virtual void SetProgressTextNewRun(const bool IsNewRun);

};

#endif // !defined(AFX_SIGNATUREATTACKMFC_H__8BCF9CB3_E0C4_11D6_9DF9_000629718A52__INCLUDED_)
