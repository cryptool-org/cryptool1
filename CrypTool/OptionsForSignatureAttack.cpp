// OptionsForSignatureAttack.cpp: Implementierung der Klasse OptionsForSignatureAttack.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModifiedDocument_Blanks.h"
#include "ModifiedDocument_Attachments.h"
#include "OptionsForSignatureAttack.h"
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

void OptionsForSignatureAttack::SetData(const char *HarmlessFile, const char *DangerousFile)
{
	char *HarmlessText, *DangerousText;
	ifstream ifstr_Harmless, ifstr_Dangerous;
	int ii, AttMethod, Blanks, DoubledBlanks, HarmlessDocumentLength, DangerousDocumentLength, ModifyingMethod;
	struct stat stat_object;

	m_Errorcode = _SIG_ATT_OK;
	m_IsDataFreed = false;
	m_HashOp = new HashingOperations(theApp.GetProfileInt("Settings", "SignatureAttackHashAlgorithmID", 0));
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

	m_HashAlgorithmBitLength = m_HashOp->GetHashAlgorithmBitLength();
	m_SignificantBitLength = theApp.GetProfileInt("Settings", "SignatureAttackSignificantBitLength", 8);
	ModifyingMethod = theApp.GetProfileInt("Settings", "SignatureAttackModificationMethod", 0);
	Blanks = theApp.GetProfileInt("Settings", "SignatureAttackCheck1", 0);
	DoubledBlanks = theApp.GetProfileInt("Settings", "SignatureAttackCheck3", 1);
	AttMethod = theApp.GetProfileInt("Settings", "SignatureAttackAttMethod", 0);

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
