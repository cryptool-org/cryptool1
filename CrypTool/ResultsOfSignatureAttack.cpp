// ResultsOfSignatureAttack.cpp: Implementierung der Klasse ResultsOfSignatureAttack.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "ResultsOfSignatureAttack.h"
#include "ErrorcodesForSignatureAttack.h"
#include "HashingOperations.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

ResultsOfSignatureAttack::ResultsOfSignatureAttack()
{

}

ResultsOfSignatureAttack::ResultsOfSignatureAttack(const int HashAlgorithmID, const int BitLength)
{
	SetData(HashAlgorithmID, BitLength);	
}

ResultsOfSignatureAttack::~ResultsOfSignatureAttack()
{
	delete []m_MatchingHashBytes;
}

void ResultsOfSignatureAttack::SetData(const int &HashAlgorithmID, const int &BitLength)
{
	int ii;

	m_FloydResult = _SIG_ATT_NO_DOCUMENTS_FOUND;

	for (ii = 0; ii < _MAX_RUNS_SIG_ATT; ii ++)
	{
		m_StepsPerRun[ii].StepsUntilCollision = 0;
		m_StepsPerRun[ii].StepsUntilConfirmation = 0;
		m_StepsPerRun[ii].TotalSteps = 0;
	}

	m_Runs = 0;
	m_TotalSteps = 0;
	m_EffectiveTime = 0.0;
	m_HashOperationsPerformed = 0;

	m_ExpectedSteps = (pow(2, ((double) BitLength / 2)) * 1.25 * 2);	// stimmt 1.25 ?

	HashingOperations HO(HashAlgorithmID);
	m_ExpectedTime = (double) m_ExpectedSteps * 5 / HO.GetHashOpsPerSecond();	// rechnerabhängig!

	m_MatchingHashBytes = new char[BitLength / 8];
}

void ResultsOfSignatureAttack::SetMatchingHashBytes(const char *MatchingHashBytes, const int CompleteByteLength)
{
	int ii;
	
	for (ii = 0; ii < CompleteByteLength; ii ++)
	{
		m_MatchingHashBytes[ii] = MatchingHashBytes[ii];
	}
}
