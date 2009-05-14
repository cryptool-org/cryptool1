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

// OptionsForSignatureAttack.h: Schnittstelle für die Klasse OptionsForSignatureAttack.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONSFORSIGNATUREATTACK_H__CF40A0E1_C08F_11D6_9DDD_000629718A52__INCLUDED_)
#define AFX_OPTIONSFORSIGNATUREATTACK_H__CF40A0E1_C08F_11D6_9DDD_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CrypToolApp.h"
#include "ModifiedDocumentForHashing.h"
#include "HashingOperations.h"

class OptionsForSignatureAttack  
{
public:
	int GetErrorcode() const { return m_Errorcode; }
	OptionsForSignatureAttack()
	{
		m_HarmlessDocument = m_DangerousDocument = NULL;
		m_HashOp = NULL;
	}
	OptionsForSignatureAttack(const char *HarmlessFile, const char *DangerousFile, const int TestMode)
	{
		m_HarmlessDocument = m_DangerousDocument = NULL;
		m_HashOp = NULL;
		SetData(HarmlessFile, DangerousFile);
		m_TestMode = TestMode;
	}

	virtual ~OptionsForSignatureAttack()
	{
		if (true == m_IsDataFreed)
		{
			return;
		}

		m_IsDataFreed = true;
		if (NULL != m_HarmlessDocument)
		{
			delete m_HarmlessDocument;
		}
		if (NULL != m_DangerousDocument)
		{
			delete m_DangerousDocument;
		}
		if (NULL != m_HashOp)
		{
			delete m_HashOp;
		}		
	}

	HashingOperations *GetHashOp() { return m_HashOp; }
	
	ModifiedDocumentForHashing *GetHarmlessDocument() const
// Beschreibung:	liefert das "harmlose" Dokument zurück;
// Parameter:		keine;
// Rückgabewert:	das harmlose Dokument [out];
	{
		return m_HarmlessDocument;
	} 

	ModifiedDocumentForHashing *GetDangerousDocument() const
// Beschreibung:	liefert das "gefährliche" Dokument zurück;
// Parameter:		keine;
// Rückgabewert:	das gefährliche Dokument [out];
	{
		return m_DangerousDocument;
	} 

	int GetSignificantBitLength() const
// Beschreibung:	liefert die in den Optionen eingestellte signifikante Bitlänge zurück;
// Parameter:		keine;
// Rückgabewert:	signifikante Bitlänge [out];
	{
		return m_SignificantBitLength;
	}

	int GetTestMode() const
	{
		return m_TestMode;
	}

private:
	bool m_IsDataFreed;
	ModifiedDocumentForHashing *m_HarmlessDocument;
	ModifiedDocumentForHashing *m_DangerousDocument;
	HashingOperations *m_HashOp;
	int m_Errorcode;
	int m_HashAlgorithmBitLength;
	int m_SignificantBitLength;
	int m_TestMode;

	void SetData(const char *HarmlessFile, const char *DangerousFile);
	void FreeData()
	{
		if (true == m_IsDataFreed)
		{
			return;
		}

		m_IsDataFreed = true;
		if (NULL != m_HarmlessDocument)
		{
			delete m_HarmlessDocument;
		}
		if (NULL != m_DangerousDocument)
		{
			delete m_DangerousDocument;
		}
		if (NULL != m_HashOp)
		{
			delete m_HashOp;
		}
	}
};

#endif // !defined(AFX_OPTIONSFORSIGNATUREATTACK_H__CF40A0E1_C08F_11D6_9DDD_000629718A52__INCLUDED_)
