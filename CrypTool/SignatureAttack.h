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


// SignatureAttack.h: Schnittstelle für die Klasse SignatureAttack.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGNATUREATTACK_H__C4452B93_B590_11D6_9DD3_000629718A52__INCLUDED_)
#define AFX_SIGNATUREATTACK_H__C4452B93_B590_11D6_9DD3_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BitParity.h"
#include "HashingOperations.h"
#include "OptionsForSignatureAttack.h"
#include "ResultsOfSignatureAttack.h"
#include "sys\timeb.h"

class SignatureAttack  
{
	double CalculateTimeSpan(_timeb &Start, _timeb &Finish);
	bool CollisionConfirmation(char *HashValue_single_step, char *HashValue_init);
	bool HashEqual(const char *HashValue_single_step, const char *HashValue_double_step) const;
	void InternalStep(int &HashValueParity, char *HashValue);

protected:
	virtual void SignalEnd() { ; }
	virtual bool CheckCanceledProgress() { return false; }
	virtual void StartShowProgress() { ; }
	virtual void SetProgressTextNewRun(const bool IsNewRun) { ; }
	BitParity m_BitPar;
	OptionsForSignatureAttack *m_OptSigAtt;
	ResultsOfSignatureAttack *m_ResSigAtt;
	FILE *m_TestFile;
	int m_TotalAttemptsCounter;

public:
	SignatureAttack();
	SignatureAttack(OptionsForSignatureAttack *m_OptSigAtt);
	SignatureAttack(OptionsForSignatureAttack *m_OptSigAtt, FILE *SigAttTest, int TotalAttemptsCounter);
	virtual ~SignatureAttack();
	UINT Do_Floyd();
	ResultsOfSignatureAttack *GetResults() const { return m_ResSigAtt; }
	
};

#endif // !defined(AFX_SIGNATUREATTACK_H__C4452B93_B590_11D6_9DD3_000629718A52__INCLUDED_)
