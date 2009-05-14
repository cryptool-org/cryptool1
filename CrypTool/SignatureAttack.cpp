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

// SignatureAttack.cpp: Implementierung der Klasse SignatureAttack.
//
// Jan Blumenstein, Deutsche Bank AG, September 2002
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SignatureAttack.h"
#include "CrypToolApp.h"
#include "s_prng.h"
#include "ErrorcodesForSignatureAttack.h"
#include <time.h>
#include <sys/timeb.h>
#include "assert.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

SignatureAttack::SignatureAttack()
{

}

SignatureAttack::SignatureAttack(OptionsForSignatureAttack *OptForSigAtt)
{
	m_OptSigAtt = OptForSigAtt;
	m_ResSigAtt = new ResultsOfSignatureAttack(m_OptSigAtt->GetHashOp()->GetHashAlgorithmID(),
		m_OptSigAtt->GetSignificantBitLength());
}

SignatureAttack::SignatureAttack(OptionsForSignatureAttack *OptForSigAtt, FILE *SigAttTest, int TotalAttemptsCounter)
{
	m_TotalAttemptsCounter = TotalAttemptsCounter;
	m_TestFile = SigAttTest;
	m_OptSigAtt = OptForSigAtt;
	m_ResSigAtt = new ResultsOfSignatureAttack(m_OptSigAtt->GetHashOp()->GetHashAlgorithmID(),
		m_OptSigAtt->GetSignificantBitLength());

	irand((unsigned)time(NULL));
}

SignatureAttack::~SignatureAttack()
{
	delete m_ResSigAtt;
}

void SignatureAttack::InternalStep(int &HashValueParity, char *HashValue)
// Beschreibung:	berechnet den Hashwert der übergebenen Nachricht und speichert ihn
// Parameter:		Parität des zuletzt berechneten Hashwertes (HashValueParity [Referenz auf int]),
//					zuletzt berechneter Hashwert (HashValue [Zeiger auf char])
// Rückgabewert:	keiner
{
	ModifiedDocumentForHashing *Document;

	m_ResSigAtt->IncreaseHashOperationsPerformed();
	HashValueParity = m_BitPar.GetParity(HashValue, m_OptSigAtt->GetSignificantBitLength());
	
	if (0 == HashValueParity)
	{
		Document = m_OptSigAtt->GetHarmlessDocument();
	}
	else
	{
		Document = m_OptSigAtt->GetDangerousDocument();
	}
	Document->ModifyDocument(HashValue);
	m_OptSigAtt->GetHashOp()->DoHash(Document->GetDocumentData(), Document->GetDocumentLength(), HashValue);
}

bool SignatureAttack::HashEqual(const char *HashValue_1, const char *HashValue_2) const
// Beschreibung:	vergleicht die signifikanten bits zweier Hashwerte miteinander und liefert das Ergebnis zurück;
// Parameter:		erster Hashwert (HashValue_1 [in]), zweiter Hashwert (HashValue_2 [in]);
// Rückgabewert:	true, wenn die signifikanten bits übereinstimmen - andernfalls false [out];
{
	char bit_mask = 0xff << (8 - (m_OptSigAtt->GetSignificantBitLength() % 8));	// unwichtige bits werden ausmaskiert
	int complete_bytes = m_OptSigAtt->GetSignificantBitLength() / 8;			// Anzahl der Bytes vom Hashwert, die
																				// komplett verglichen werden
	
	if (0 != memcmp(HashValue_1, HashValue_2, complete_bytes))
	{
		return false;	// Ganz-Byte-Anteil der signifikanten bits beider Hashwerte ist ungleich
	}

	if (m_OptSigAtt->GetSignificantBitLength() % 8)	// wenn die Anzahl der signifikanten bits (mod 8) ungleich 0 ist...
	{
		return (HashValue_1[complete_bytes] & bit_mask) == (HashValue_2[complete_bytes] & bit_mask);
			// die bits des "unvollständigen" Bytes beider Hashwerte sind ungleich
	}
		
	return true;	// alle signifikanten bits beider Hashwerte sind gleich
}

bool SignatureAttack::CollisionConfirmation(char *HashValue_single_step, char *HashValue_confirm_step)
// Beschreibung:	;
// Parameter:		erster Hashwert (HashValue_1 [in]), zweiter Hashwert (HashValue_2 [in]);
// Rückgabewert:	true, wenn die signifikanten bits übereinstimmen - andernfalls false [out];
{
	char *HashValue_pre_success1, *HashValue_pre_success2;
	int HashAlgorithmByteLength, HashValueParity_single_step, HashValueParity_confirm_step, RunID;

	if (true == HashEqual(HashValue_single_step, HashValue_confirm_step))
	{
		return false;	// schlechte Kollision, da Startpunkt der Folgen gleich dem Kollisionspunkt
	}

	if (m_OptSigAtt->GetTestMode())
	{
		HashAlgorithmByteLength = 1 + (m_OptSigAtt->GetHashOp()->GetHashAlgorithmBitLength() - 1) / 8;
		HashValue_pre_success1 = new char[HashAlgorithmByteLength];
		HashValue_pre_success2 = new char[HashAlgorithmByteLength];
	}

	RunID = m_ResSigAtt->GetRuns() - 1;

	while (1)
	{

		if (m_OptSigAtt->GetTestMode())
		{
			memcpy(HashValue_pre_success1, HashValue_single_step, HashAlgorithmByteLength);
			memcpy(HashValue_pre_success2, HashValue_confirm_step, HashAlgorithmByteLength);
		}

		m_ResSigAtt->IncreaseConfirmationStepsOfRun(RunID);
		InternalStep(HashValueParity_single_step, HashValue_single_step);
		InternalStep(HashValueParity_confirm_step, HashValue_confirm_step);

		if (true == HashEqual(HashValue_single_step, HashValue_confirm_step))
		{
			if (HashValueParity_single_step != HashValueParity_confirm_step)
			{

				if (m_OptSigAtt->GetTestMode())
				{	
					char *HashStore = new char[HashAlgorithmByteLength * 2 + 1];
					int ii, jj;

					for (jj = ii = 0; ii < HashAlgorithmByteLength; ii ++)
					{
						jj += _snprintf(HashStore + jj, 2, "%2.2X", (unsigned char) HashValue_confirm_step[ii]);
					}
					HashStore[jj] = 0;
					fprintf(m_TestFile,	"\nHashSuccess1=%s", HashStore);

					for (jj = ii = 0; ii < HashAlgorithmByteLength; ii ++)
					{
						jj += _snprintf(HashStore + jj, 2, "%2.2X", (unsigned char) HashValue_single_step[ii]);
					}
					HashStore[jj] = 0;
					fprintf(m_TestFile,	"\nHashSuccess2=%s", HashStore);

					for (jj = ii = 0; ii < HashAlgorithmByteLength; ii ++)
					{
						jj += _snprintf(HashStore + jj, 2, "%2.2X", (unsigned char) HashValue_pre_success1[ii]);
					}
					HashStore[jj] = 0;
					fprintf(m_TestFile,	"\nHashPreSuccess1=%s", HashStore);

					for (jj = ii = 0; ii < HashAlgorithmByteLength; ii ++)
					{
						jj += _snprintf(HashStore + jj, 2, "%2.2X", (unsigned char) HashValue_pre_success2[ii]);
					}
					HashStore[jj] = 0;
					fprintf(m_TestFile,	"\nHashPreSuccess2=%s", HashStore);

					delete []HashStore;
					delete []HashValue_pre_success1;
					delete []HashValue_pre_success2;
				}

				return true;	// gute Kollision gefunden -> Suche abbrechen
			}

			if (m_OptSigAtt->GetTestMode())
			{
				delete []HashValue_pre_success1;
				delete []HashValue_pre_success2;
			}

			return false;		// schlechte Kollision (gleicher Nachrichtentyp) -> nächster Run
		}
	}

	if (m_OptSigAtt->GetTestMode())
	{			
		delete []HashValue_pre_success1;
		delete []HashValue_pre_success2;
	}

	return false;	// Kollision nicht bestätigt, (noch) kein Nachrichtenpaar gefunden -> nächster Run
}

UINT SignatureAttack::Do_Floyd()
// Beschreibung:	führt den Floyd-Algorithmus aus, der zu zwei gegebenen Nachrichten Modifikationen findet, deren
//					Hashwerte gleich sind
// Parameter:		keine;
// Rückgabewert:	Fehlercode;
{
	Big RandomMax = "256", RandomResult = "0";
	bool DocumentsFound = false;
	char *HashValue_single_step, *HashValue_double_step, *HashValue_init, *HashValue_confirm_step;
	struct _timeb time_start, time_finish;
	int HashValueParity_single_step, HashValueParity_double_step;
	__int64 ii, MAX_StepsPerRun;

	StartShowProgress();

	int HashAlgorithmByteLength = 1 + (m_OptSigAtt->GetHashOp()->GetHashAlgorithmBitLength() - 1) / 8;
	HashValue_init = new char[HashAlgorithmByteLength];
	HashValue_single_step = new char[HashAlgorithmByteLength];
	HashValue_double_step = new char[HashAlgorithmByteLength];
	
	HashValue_confirm_step = new char[HashAlgorithmByteLength];
	// für die 4 Hashwerte werden jeweils - in Abhängigkeit vom Hash-Algorithmus - 16 oder 20 Bytes Speicher reserviert

	HashValueParity_single_step = HashValueParity_double_step = 0;	// Floyd-Algorithmus beginnt mit harmloser Nachricht
	MAX_StepsPerRun = (m_ResSigAtt->GetExpectedSteps() * m_OptSigAtt->GetSignificantBitLength());
	
	if (m_OptSigAtt->GetTestMode())
	{
		fprintf(m_TestFile,	"\n***\nTry_No=%d\nAlg_ID=%d\nSigBit=%d",
			m_TotalAttemptsCounter, m_OptSigAtt->GetHashOp()->GetHashAlgorithmID(), m_OptSigAtt->GetSignificantBitLength());
	}
	
	_ftime(&time_start);	// Zeitmessung beginnt

#ifdef _SIG_ATT_HASH_ONLY

#define _SA_HOPS 10000000
	char *buf = m_OptSigAtt->GetHarmlessDocument()->GetOriginalDocument()->GetDocumentData();
	int len = m_OptSigAtt->GetHarmlessDocument()->GetOriginalDocument()->GetDocumentLength();
	HashingOperations *hop = m_OptSigAtt->GetHashOp();
	for(ii = 0; ii < _SA_HOPS; ii ++)
	{   
		hop->DoHash(buf, len, HashValue_single_step);
		m_ResSigAtt->IncreaseHashOperationsPerformed();
	}
	_ftime(&time_finish);
	goto HASHTOKEN;

#endif


	while (false == DocumentsFound)
	{

#ifdef _SIG_ATT_SPEED_INCREMENT

		m_OptSigAtt->GetHarmlessDocument()->ModifyOriginalDocument(m_ResSigAtt->GetRuns());
		m_OptSigAtt->GetDangerousDocument()->ModifyOriginalDocument(m_ResSigAtt->GetRuns());

#endif

		m_ResSigAtt->IncreaseRuns();
		SetProgressTextNewRun(true);

		char Random[4];
		int i_Rand;
		for (ii = 0 ; ii < HashAlgorithmByteLength; ii ++)
		{
			bigrand(RandomMax.getbig(), RandomResult.getbig());
			Random << RandomResult;			
			i_Rand = atoi(Random);

			assert (i_Rand >= 0 && i_Rand <= 255);
			HashValue_init[ii] = i_Rand;
		}

		memcpy(HashValue_single_step, HashValue_init, HashAlgorithmByteLength);
		memcpy(HashValue_double_step, HashValue_init, HashAlgorithmByteLength);
		
		while (1)
		{
			if (true == CheckCanceledProgress())
			{
				return 0;
			}

			m_ResSigAtt->IncreaseCollisionStepsOfRun(m_ResSigAtt->GetRuns() - 1);

			InternalStep(HashValueParity_single_step, HashValue_single_step);
			InternalStep(HashValueParity_double_step, HashValue_double_step);
			InternalStep(HashValueParity_double_step, HashValue_double_step);

			if (true == HashEqual(HashValue_single_step, HashValue_double_step))
			{
				SetProgressTextNewRun(false);
				memcpy(HashValue_confirm_step, HashValue_init, HashAlgorithmByteLength);
				if (true == CollisionConfirmation(HashValue_single_step, HashValue_confirm_step))
				{
					_ftime(&time_finish);	// Zeitmessung endet
					DocumentsFound = true;	// aüßere while-Schleife wird verlassen
				}
				
				break;	// innere while-Schleife wird verlassen
			}

			if (MAX_StepsPerRun == m_ResSigAtt->GetCollisionStepsOfRun(m_ResSigAtt->GetRuns() - 1))
			{
				break;	// innere while-Schleife wird verlassen -> nächster Run
			}
		}

		if (m_OptSigAtt->GetTestMode())
		{
			__int64 jj;
		
			char *HashStore = new char[HashAlgorithmByteLength * 2 + 1];
			for (jj = ii = 0; ii < HashAlgorithmByteLength; ii ++)
			{
				jj += _snprintf(HashStore + jj, 2, "%2.2X", (unsigned char) HashValue_init[ii]);
			}
			HashStore[jj] = 0;

			fprintf(m_TestFile,	"\nRun_No=%2.2d\nHashInit=%s\nCollSteps=%I64i\nConfSteps=%I64i",
				m_ResSigAtt->GetRuns(), HashStore, m_ResSigAtt->GetCollisionStepsOfRun(m_ResSigAtt->GetRuns() - 1),
				m_ResSigAtt->GetConfirmationStepsOfRun(m_ResSigAtt->GetRuns() - 1));

			delete []HashStore;
		}

		if (_MAX_RUNS_SIG_ATT == m_ResSigAtt->GetRuns())
		{
			if (false == DocumentsFound)
			{
				_ftime(&time_finish);	// Zeitmessung endet
			}

			break;	// es wurden 10 Runs durchlaufen und kein Nachrichtenpaar gefunden -> Suche beenden
		}
	}

	double timeSpan = CalculateTimeSpan(time_start, time_finish);
	m_ResSigAtt->SetEffectiveTime(timeSpan);

	if (true == DocumentsFound)
	{
		m_ResSigAtt->SetFloydResult(_SIG_ATT_DOCUMENTS_FOUND);		// Nachrichtenpaar gefunden !
		m_ResSigAtt->SetMatchingHashBytes(HashValue_single_step, m_OptSigAtt->GetSignificantBitLength() / 8);
	}
	else
	{
		m_ResSigAtt->SetFloydResult(_SIG_ATT_NO_DOCUMENTS_FOUND);	// kein Nachrichtenpaar gefunden
	}

	if (m_OptSigAtt->GetTestMode())
	{
		fprintf(m_TestFile,	"\nResult=%d\nTotalSteps=%I64i\nExpectedSteps=%I64i\nHashOps=%I64i\nElapsedTime=%.3f",
			m_ResSigAtt->GetFloydResult(), m_ResSigAtt->GetTotalSteps(), m_ResSigAtt->GetExpectedSteps(),
			m_ResSigAtt->GetHashOperationsPerformed(), m_ResSigAtt->GetEffectiveTime());
	}

#ifdef _SIG_ATT_HASH_ONLY

HASHTOKEN:
	m_ResSigAtt->SetFloydResult(_SIG_ATT_DOCUMENTS_FOUND);
	m_ResSigAtt->SetEffectiveTime(CalculateTimeSpan(time_start, time_finish));
	m_ResSigAtt->SetExpectedTime(_SA_HOPS / (CalculateTimeSpan(time_start, time_finish) / CLOCKS_PER_SEC));

#endif

	theApp.fs.cancel();

	delete []HashValue_single_step;
	delete []HashValue_double_step;
	delete []HashValue_init;
	delete []HashValue_confirm_step;

	SignalEnd();
	return 0;
}

double SignatureAttack::CalculateTimeSpan(_timeb &Start, _timeb &Finish) 
{
	__int64 Seconds = Finish.time - Start.time, Milliseconds = Finish.millitm - Start.millitm;
	// Dauer der Floyd-Suche wird aus der Differenz der Start- und Endzeit ermittelt

	if (Milliseconds < 0)
	{
		Seconds -= 1;			// bei z.B. Start=13.9 und Finish=14.2 müssten diese Rechnungen
		Milliseconds += 1000;	// durchgeführt werden!
	}
	
	return ((double)Seconds + (double)Milliseconds / 1000);
}
