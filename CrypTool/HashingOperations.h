// HashingOperations.h: Schnittstelle für die Klasse HashingOperations.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HASHINGOPERATIONS_H__94B56021_D434_11D6_9DEF_000629718A52__INCLUDED_)
#define AFX_HASHINGOPERATIONS_H__94B56021_D434_11D6_9DEF_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ErrorcodesForSignatureAttack.h"


class HashingOperations  
{
public:
	int GetHashAlgorithmBitLength() const;
	char *GetHashAlgorithmName() const;

	int GetErrorcode() const
// Beschreibung:	liefert den Fehlercode zurück, der in SetData() bestimmt wurde und sollte nach Anlegen eines
//					HashingOperations-Objekts aufgerufen werden: wenn das Ergebnis ungleich 0 ist, kann das Aufrufen
//					der Get-Methoden zu einem Absturt führen!;
// Parameter:		keine;
// Rückgabewert:	Fehlercode [out]: 0 = OK, 1 = kein Hash-Algorithmus implementiert, 2 = ungültige Hash-Algorithmus-ID;
	{
		return m_Errorcode;
	}

	int GetHashAlgorithmID() const { return m_HashAlgorithmID; }
	HashingOperations(int HashAlgorithmID) { SetData(HashAlgorithmID); }
	virtual ~HashingOperations();
	void DoHash(char *OriginalDocument, const int OriginalDocumentLength, char *ResultingHashValue) const;
	
private:
	void *m_HashContext;
	int m_HashAlgorithmID;
	void SetData(int HashAlgorithmID);
	int m_Errorcode;
	int m_AlgorithmCounter;
};

#endif // !defined(AFX_HASHINGOPERATIONS_H__94B56021_D434_11D6_9DEF_000629718A52__INCLUDED_)
