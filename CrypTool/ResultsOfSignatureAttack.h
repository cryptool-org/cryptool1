// ResultsOfSignatureAttack.h: Schnittstelle für die Klasse ResultsOfSignatureAttack.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESULTSOFSIGNATUREATTACK_H__DBD92911_D1DB_11D6_9DEE_000629718A52__INCLUDED_)
#define AFX_RESULTSOFSIGNATUREATTACK_H__DBD92911_D1DB_11D6_9DEE_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _MAX_RUNS_SIG_ATT	10


class ResultsOfSignatureAttack
// enthält zahlreiche Get- und Set-Methoden, um statistische Daten über den Floyd-Algorithmus zu speichern bzw. für den
// Auswertungs-Dialog zur Verfügung zu stellen
{
public:
	ResultsOfSignatureAttack ();
	ResultsOfSignatureAttack (const int HashAlgorithmID, const int BitLength);
	virtual ~ResultsOfSignatureAttack ();

	int GetRuns () const										{ return m_Runs; }
	double GetTotalSteps () const								{ return m_TotalSteps; }
	double GetExpectedSteps () const							{ return m_ExpectedSteps; }
	double GetCollisionStepsOfRun (const int index) const		{ return m_StepsPerRun[index].StepsUntilCollision; }
	double GetConfirmationStepsOfRun (const int index) const	{ return m_StepsPerRun[index].StepsUntilConfirmation; }
	double GetTotalStepsOfRun (const int index) const			{ return m_StepsPerRun[index].TotalSteps; }
	double GetHashOperationsPerformed () const					{ return m_HashOperationsPerformed; }
	double GetExpectedTime () const								{ return m_ExpectedTime; }
	double GetEffectiveTime () const							{ return m_EffectiveTime; }
	int GetFloydResult () const									{ return m_FloydResult; }
	char *GetMatchingHashBytes() const							{ return m_MatchingHashBytes; }

	void IncreaseRuns ()										{ m_Runs ++; }
	void IncreaseHashOperationsPerformed ()						{ m_HashOperationsPerformed ++; }
	void IncreaseCollisionStepsOfRun (const int index)
	{
		m_StepsPerRun[index].StepsUntilCollision ++;
		m_StepsPerRun[index].TotalSteps ++;
		m_TotalSteps ++;
	}
	void IncreaseConfirmationStepsOfRun (const int index)
	{
		m_StepsPerRun[index].StepsUntilConfirmation ++;
		m_StepsPerRun[index].TotalSteps ++;
		m_TotalSteps ++;
	}
	void SetExpectedTime (const double ExpectedTime)			{ m_ExpectedTime = ExpectedTime; }
	void SetEffectiveTime (const double EffectiveTime)			{ m_EffectiveTime = EffectiveTime; }
	void SetFloydResult (const int Errorcode)					{ m_FloydResult = Errorcode; }
	void SetMatchingHashBytes (const char *MatchingHashBytes, const int CompleteByteLength);

private:
	void SetData (const int &HashAlgorithmID, const int &BitLength);
	int m_Runs;
	struct Steps
	{
		double StepsUntilCollision;
		double StepsUntilConfirmation;
		double TotalSteps;
	} m_StepsPerRun[_MAX_RUNS_SIG_ATT];

	double m_TotalSteps;
	double m_ExpectedTime;
	double m_EffectiveTime;
	double m_ExpectedSteps;
	double m_HashOperationsPerformed;
	int m_FloydResult;
	char *m_MatchingHashBytes;
};

#endif // !defined(AFX_RESULTSOFSIGNATUREATTACK_H__DBD92911_D1DB_11D6_9DEE_000629718A52__INCLUDED_)
