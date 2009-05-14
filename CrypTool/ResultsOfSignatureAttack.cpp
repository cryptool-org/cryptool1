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
	c_filename_fake = c_filename_original = m_MatchingHashBytes = NULL;
}

ResultsOfSignatureAttack::ResultsOfSignatureAttack(const int HashAlgorithmID, const int BitLength)
{
	c_filename_fake = c_filename_original = m_MatchingHashBytes = NULL;
	SetData(HashAlgorithmID, BitLength);	
}

void ResultsOfSignatureAttack::SetFilenames(const char *filenameOriginal, const char *filenameFake)
{
	if ( filenameFake )
	{
		if (c_filename_fake) delete []c_filename_fake;
		c_filename_fake = new char[strlen(filenameFake)+1];
		strcpy(c_filename_fake, filenameFake);
	}	
	if ( filenameOriginal )
	{
		if (c_filename_original) delete []c_filename_original;
		c_filename_original = new char[strlen(filenameOriginal)+1];
		strcpy(c_filename_original, filenameOriginal);
	}
}

ResultsOfSignatureAttack::~ResultsOfSignatureAttack()
{
	delete []m_MatchingHashBytes;
	delete []c_filename_fake;
	delete []c_filename_original;
}

void ResultsOfSignatureAttack::SetData(const int &HashAlgorithmID, const int &BitLength)
{
	int ii;

	m_FloydResult = _SIG_ATT_NO_DOCUMENTS_FOUND;
	for (ii = 0; ii < _MAX_RUNS_SIG_ATT; ii ++)
	{
		m_StepsPerRun[ii].StepsUntilCollision		= 0;
		m_StepsPerRun[ii].StepsUntilConfirmation	= 0;
		m_StepsPerRun[ii].TotalSteps				= 0;
	}

	m_ExpectedSteps = (long long)ceil((double)(pow((double)2, ((double) BitLength / 2)) * 1.25 * 2));	// stimmt 1.25 ?
	m_Runs						= 0;
	m_TotalSteps				= 0;
	m_EffectiveTime				= 0.0;
	m_HashOperationsPerformed	= 0;
	HashingOperations HO(HashAlgorithmID);
	m_HashAlgorithmID			= HashAlgorithmID;

	m_ExpectedTime				= (double) m_ExpectedSteps * 5 / HO.GetHashOpsPerSecond();	// rechnerabhängig!
	m_BitLength					= BitLength;
	m_MatchingHashBytes			= new char[BitLength / 8];
}

void ResultsOfSignatureAttack::SetMatchingHashBytes(const char *MatchingHashBytes, const int CompleteByteLength)
{
	int ii;
	
	for (ii = 0; ii < CompleteByteLength; ii ++)
	{
		m_MatchingHashBytes[ii] = MatchingHashBytes[ii];
	}
}
