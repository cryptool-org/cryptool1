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

class SignatureAttack  
{
public:
	SignatureAttack();
	SignatureAttack(OptionsForSignatureAttack *m_OptSigAtt);
	SignatureAttack(OptionsForSignatureAttack *m_OptSigAtt, FILE *SigAttTest, int TotalAttemptsCounter);
	virtual ~SignatureAttack();
	UINT Do_Floyd();
	ResultsOfSignatureAttack *GetResults() const { return m_ResSigAtt; }
	
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

private:
	double CalculateTimeSpan(const struct _timeb Start, const struct _timeb Finish) const;
	bool CollisionConfirmation(char *HashValue_single_step, char *HashValue_init);
	bool HashEqual(const char *HashValue_single_step, const char *HashValue_double_step) const;
	void InternalStep(int &HashValueParity, char *HashValue);
		
};

#endif // !defined(AFX_SIGNATUREATTACK_H__C4452B93_B590_11D6_9DD3_000629718A52__INCLUDED_)
