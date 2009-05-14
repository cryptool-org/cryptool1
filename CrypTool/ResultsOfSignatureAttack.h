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
	int m_Runs;
	struct Steps
	{
		long long StepsUntilCollision;
		long long StepsUntilConfirmation;
		long long TotalSteps;
	} m_StepsPerRun[_MAX_RUNS_SIG_ATT];

	long long	m_TotalSteps;
	double		m_ExpectedTime;
	double		m_EffectiveTime;
	long long	m_ExpectedSteps;
	long long	m_HashOperationsPerformed;
	int			m_FloydResult;
	int			m_BitLength;
	int         m_HashAlgorithmID;
	char	   *m_MatchingHashBytes;
	char	   *c_filename_original;
	char	   *c_filename_fake;

public:
	ResultsOfSignatureAttack ();
	ResultsOfSignatureAttack (const int HashAlgorithmID, const int BitLength);
	virtual ~ResultsOfSignatureAttack ();

	int GetRuns () const										{ return m_Runs; }
	long long GetTotalSteps () const							{ return m_TotalSteps; }
	long long GetExpectedSteps () const							{ return m_ExpectedSteps; }
	long long GetCollisionStepsOfRun (const int index) const	{ return m_StepsPerRun[index].StepsUntilCollision; }
	long long GetConfirmationStepsOfRun (const int index) const	{ return m_StepsPerRun[index].StepsUntilConfirmation; }
	long long GetTotalStepsOfRun (const int index) const		{ return m_StepsPerRun[index].TotalSteps; }
	long long GetHashOperationsPerformed () const				{ return m_HashOperationsPerformed; }
	double GetExpectedTime () const								{ return m_ExpectedTime; }
	double GetEffectiveTime () const							{ return m_EffectiveTime; }
	int GetFloydResult () const									{ return m_FloydResult; }
	char *GetMatchingHashBytes() const							{ return m_MatchingHashBytes; }
	int GetHashAlgorithmID() const								{ return m_HashAlgorithmID; }

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
	void SetStrHashFunction(int id);
	void SetFilenames(const char *filenameOriginal, const char *filenameFake);
	const char *getStrFilenameFake()		const { return c_filename_fake; }
	const char *getStrFilenameOriginal()	const { return c_filename_original; }
private:
	void SetData (const int &HashAlgorithmID, const int &BitLength);
};

#endif // !defined(AFX_RESULTSOFSIGNATUREATTACK_H__DBD92911_D1DB_11D6_9DEE_000629718A52__INCLUDED_)
