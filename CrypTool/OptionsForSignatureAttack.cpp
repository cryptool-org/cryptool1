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


// OptionsForSignatureAttack.cpp: Implementierung der Klasse OptionsForSignatureAttack.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModifiedDocument_Blanks.h"
#include "ModifiedDocument_Attachments.h"
#include "OptionsForSignatureAttack.h"
#include "ErrorcodesForSignatureAttack.h"
#include "HashingOperations.h"
#include "CrypToolTools.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

void OptionsForSignatureAttack::SetData(const char *HarmlessFile, const char *DangerousFile)
{
	char *HarmlessText, *DangerousText;
	ifstream ifstr_Harmless, ifstr_Dangerous;
	int ii, AttMethod, Blanks, DoubledBlanks, HarmlessDocumentLength, DangerousDocumentLength, ModifyingMethod;
	struct stat stat_object;


	m_Errorcode = _SIG_ATT_OK;
	m_IsDataFreed = false;

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "SignatureAttack" ) == ERROR_SUCCESS )
	{

		unsigned long u_SignatureAttackHashAlgorithmID = (unsigned long)FALSE;
		CT_READ_REGISTRY_DEFAULT(u_SignatureAttackHashAlgorithmID, "HashAlgorithmID", u_SignatureAttackHashAlgorithmID);
		m_HashOp = new HashingOperations(u_SignatureAttackHashAlgorithmID);
		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}

	if (0 != m_HashOp->GetErrorcode())
	{
		m_Errorcode = _SIG_ATT_BAD_HASH_ALGORITHM;
		return;
	}

	ifstr_Harmless.open(HarmlessFile, ios::in | ios::binary);
	ifstr_Dangerous.open(DangerousFile, ios::in | ios::binary);
	if (!ifstr_Harmless)
	{
		m_Errorcode = _SIG_ATT_BAD_HARMLESS_FILE;
		return;
	}
	if (!ifstr_Dangerous)
	{
		m_Errorcode = _SIG_ATT_BAD_DANGEROUS_FILE;
		return;
	}
	
	stat((const char *) HarmlessFile, & stat_object);
	if (0 == stat_object.st_size)
	{
		m_Errorcode = _SIG_ATT_BAD_HARMLESS_FILE;
		return;
	}
	HarmlessDocumentLength = stat_object.st_size;

	stat((const char *) DangerousFile, & stat_object);
	if (0 == stat_object.st_size)
	{
		m_Errorcode = _SIG_ATT_BAD_DANGEROUS_FILE;
		return;
	}
	DangerousDocumentLength = stat_object.st_size;

	HarmlessText= new char[HarmlessDocumentLength];
	DangerousText= new char[DangerousDocumentLength];

	ii = 0;
	while (0 == ifstr_Harmless.eof())
	{
		ifstr_Harmless.read(HarmlessText + ii, 1);
		ii ++;
	}
	ifstr_Harmless.close();

	ii = 0;
	while (0 == ifstr_Dangerous.eof())
	{
		ifstr_Dangerous.read(DangerousText + ii, 1);
		ii ++;
	}
	ifstr_Dangerous.close();


	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "SignatureAttack" ) == ERROR_SUCCESS )
	{
		m_HashAlgorithmBitLength = m_HashOp->GetHashAlgorithmBitLength();

		unsigned long u_SignificantBitLength = 8;
		CT_READ_REGISTRY_DEFAULT(u_SignificantBitLength, "SignificantBitLength", u_SignificantBitLength);
		m_SignificantBitLength = u_SignificantBitLength;

		unsigned long u_ModifyingMethod = 0;
		CT_READ_REGISTRY_DEFAULT(u_ModifyingMethod, "ModificationMethod", u_ModifyingMethod);
		ModifyingMethod = u_ModifyingMethod;

		unsigned long u_Blanks = 0;
		CT_READ_REGISTRY_DEFAULT(u_Blanks, "ModfiyBlankEOL", u_Blanks);
		Blanks = u_Blanks;

		unsigned long u_DoubledBlanks = 1;
		CT_READ_REGISTRY_DEFAULT(u_DoubledBlanks, "ModifyDoubleBlank", u_DoubledBlanks);
		DoubledBlanks = u_DoubledBlanks;

		unsigned long u_AttMethod = 1;
		CT_READ_REGISTRY_DEFAULT(u_AttMethod, "ModifyCharSet", u_AttMethod);
		AttMethod = u_AttMethod;

		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}


	if (m_SignificantBitLength > m_HashAlgorithmBitLength)
	{
		m_SignificantBitLength = m_HashAlgorithmBitLength;
	}

	if (AttMethod < 0|| AttMethod > 1)
	{
		AttMethod = 1;
	}

	if (m_TestMode)
	{
		ModifyingMethod = 1;
	}

	if (0 == ModifyingMethod)
	{
		if (1 != Blanks && 1 != DoubledBlanks)
		{
			Blanks = 1;
		}

#ifdef _SIG_ATT_SPEED_INCREMENT
		m_HarmlessDocument = new ModifiedDocument_Blanks(HarmlessText, HarmlessDocumentLength + 4, m_SignificantBitLength,
			Blanks, DoubledBlanks);
#endif

#ifndef _SIG_ATT_SPEED_INCREMENT
		m_HarmlessDocument = new ModifiedDocument_Blanks(HarmlessText, HarmlessDocumentLength, m_SignificantBitLength,
			Blanks, DoubledBlanks);
#endif

		if (_SIG_ATT_OK != m_HarmlessDocument->GetErrorcode())
		{
			m_Errorcode = _SIG_ATT_BAD_MODIFIABILITY;
		}

#ifdef _SIG_ATT_SPEED_INCREMENT
		m_DangerousDocument = new ModifiedDocument_Blanks(DangerousText, DangerousDocumentLength + 4, m_SignificantBitLength,
			Blanks, DoubledBlanks);
#endif

#ifndef _SIG_ATT_SPEED_INCREMENT
		m_DangerousDocument = new ModifiedDocument_Blanks(DangerousText, DangerousDocumentLength, m_SignificantBitLength,
			Blanks, DoubledBlanks);
#endif

		if (_SIG_ATT_OK != m_DangerousDocument->GetErrorcode())
		{
			m_Errorcode = _SIG_ATT_BAD_MODIFIABILITY;
		}
	}

	else if (1 == ModifyingMethod)
	{

#ifdef _SIG_ATT_SPEED_INCREMENT
		m_HarmlessDocument = new ModifiedDocument_Attachments
			(HarmlessText, HarmlessDocumentLength + 2, m_SignificantBitLength, AttMethod);
#endif

#ifndef _SIG_ATT_SPEED_INCREMENT
		m_HarmlessDocument = new ModifiedDocument_Attachments
			(HarmlessText, HarmlessDocumentLength, m_SignificantBitLength, AttMethod);
#endif

		if (_SIG_ATT_OK != m_HarmlessDocument->GetErrorcode())
		{
			m_Errorcode = _SIG_ATT_BAD_MODIFIABILITY;
		}

#ifdef _SIG_ATT_SPEED_INCREMENT
		m_DangerousDocument = new ModifiedDocument_Attachments
			(DangerousText, DangerousDocumentLength + 2, m_SignificantBitLength, AttMethod);
#endif

#ifndef _SIG_ATT_SPEED_INCREMENT
		m_DangerousDocument = new ModifiedDocument_Attachments
			(DangerousText, DangerousDocumentLength, m_SignificantBitLength, AttMethod);
#endif

		if (_SIG_ATT_OK != m_DangerousDocument->GetErrorcode())
		{
			m_Errorcode = _SIG_ATT_BAD_MODIFIABILITY;
		}
	}

	if (_SIG_ATT_OK != m_Errorcode)
	{
		FreeData();
	}

	delete []HarmlessText;
	delete []DangerousText;
}
