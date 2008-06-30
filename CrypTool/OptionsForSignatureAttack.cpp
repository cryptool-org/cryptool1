/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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
