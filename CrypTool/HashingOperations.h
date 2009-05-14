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


// HashingOperations.h: Schnittstelle für die Klasse HashingOperations.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HASHINGOPERATIONS_H__94B56021_D434_11D6_9DEF_000629718A52__INCLUDED_)
#define AFX_HASHINGOPERATIONS_H__94B56021_D434_11D6_9DEF_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ErrorcodesForSignatureAttack.h"

typedef void (*fp_Init_t) (void *context);
typedef void (*fp_Update_t) (void *context, void *data, unsigned long len);
typedef void (*fp_Final_t) (void *hash, void *context);

struct HashAlgorithmsFP
{
	fp_Init_t fp_Init;
	fp_Update_t fp_Update;
	fp_Final_t fp_Final;
	void *Context;
	int ContextSize;
	int BitLength;
	char *Name;
	int HashOpsPerSecond;	// ausgehend von einem Rechner mit ???-Prozessor und ??? MHz Taktfrequenz
};

struct HashAlgorithmsFP HAFP[];

class HashingOperations  
{
	void *m_HashContext;
	int m_HashAlgorithmID;
	void SetData(int HashAlgorithmID);
	int m_Errorcode;
	int m_AlgorithmCounter;

public:
			 HashingOperations(int HashAlgorithmID) { SetData(HashAlgorithmID); }
	virtual ~HashingOperations();

	int		GetHashAlgorithmBitLength() const;
	char   *GetHashAlgorithmName() const;
	int		GetHashOpsPerSecond() const;
	int		GetErrorcode() const
	{ // 0 = OK, 1 = kein Hash-Algorithmus implementiert, 2 = ungültige Hash-Algorithmus-ID;
		return m_Errorcode;
	}
	int		GetHashAlgorithmID() const { return m_HashAlgorithmID; }
	void	DoHash(char *OriginalDocument, const int OriginalDocumentLength, char *ResultingHashValue) const;
	HashAlgorithmsFP *getHashAlgorithmsFP() { return &(HAFP[m_HashAlgorithmID]); };	
	// these three functions provide a public access for hashing in chunks
	void	chunkHashInit();
	void	chunkHashUpdate(void *_message, const int _messageLength);
	void	chunkHashFinal(char *_messageDigest);
};

#endif // !defined(AFX_HASHINGOPERATIONS_H__94B56021_D434_11D6_9DEF_000629718A52__INCLUDED_)
