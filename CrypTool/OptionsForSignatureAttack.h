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
	OptionsForSignatureAttack(const char *HarmlessFile, const char *DangerousFile)
	{
		m_HarmlessDocument = m_DangerousDocument = NULL;
		m_HashOp = NULL;
		SetData(HarmlessFile, DangerousFile);
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

private:
	bool m_IsDataFreed;
	ModifiedDocumentForHashing *m_HarmlessDocument;
	ModifiedDocumentForHashing *m_DangerousDocument;
	HashingOperations *m_HashOp;
	int m_Errorcode;
	int m_HashAlgorithmBitLength;
	int m_SignificantBitLength;

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
