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
