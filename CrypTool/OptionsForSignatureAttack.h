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
