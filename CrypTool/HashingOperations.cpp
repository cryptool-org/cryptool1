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


// HashingOperations.cpp: Implementierung der Klasse HashingOperations.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrypToolApp.h"
#include "HashingOperations.h"


namespace __SSL
{
#include "OpenSSL//md2.h"
#include "OpenSSL//md4.h"
#include "OpenSSL//md5.h"
#include "OpenSSL//ripemd.h"
#include "OpenSSL//sha.h"
}

// namespace MD2


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

HashAlgorithmsFP HAFP[] =
{
	{
		(fp_Init_t) __SSL::MD2_Init,
		(fp_Update_t) __SSL::MD2_Update,
		(fp_Final_t) __SSL::MD2_Final,
		NULL,
		sizeof(__SSL::MD2_CTX),
		128,
		"MD2",
		50831
	},
	{
		(fp_Init_t) __SSL::MD4_Init,
		(fp_Update_t) __SSL::MD4_Update,
		(fp_Final_t) __SSL::MD4_Final,
		NULL,
		sizeof(__SSL::MD4_CTX),
		128,
		"MD4",
		887430
	},
	{
		(fp_Init_t) __SSL::MD5_Init,
		(fp_Update_t) __SSL::MD5_Update,
		(fp_Final_t) __SSL::MD5_Final,
		NULL,
		sizeof(__SSL::MD5_CTX),
		128,
		"MD5",
		767548
	},
	{
		(fp_Init_t) __SSL::SHA_Init,
		(fp_Update_t) __SSL::SHA_Update,
		(fp_Final_t) __SSL::SHA_Final,
		NULL,
		sizeof(__SSL::SHA_CTX),
		160,
		"SHA",
		425155
	},
	{
		(fp_Init_t) __SSL::SHA1_Init,
		(fp_Update_t) __SSL::SHA1_Update,
		(fp_Final_t) __SSL::SHA1_Final,
		NULL,
		sizeof(__SSL::SHA_CTX),
		160,
		"SHA-1",
		475445
	},
	{
		(fp_Init_t) __SSL::RIPEMD160_Init,
		(fp_Update_t) __SSL::RIPEMD160_Update,
		(fp_Final_t) __SSL::RIPEMD160_Final,
		NULL,
		sizeof(__SSL::RIPEMD160_CTX),
		160,
		"RIPEMD-160",
		382310
	},
	{
		(fp_Init_t) __SSL::SHA256_Init,
		(fp_Update_t) __SSL::SHA256_Update,
		(fp_Final_t) __SSL::SHA256_Final,
		NULL,
		sizeof(__SSL::SHA256_CTX),
		256,
		"SHA-256",
		555555 // FIXME
	},
	{
		(fp_Init_t) __SSL::SHA512_Init,
		(fp_Update_t) __SSL::SHA512_Update,
		(fp_Final_t) __SSL::SHA512_Final,
		NULL,
		sizeof(__SSL::SHA512_CTX),
		512,
		"SHA-512",
		777777 // FIXME
	}
};

HashingOperations::~HashingOperations()
{
	if (_SIG_ATT_OK != m_Errorcode)
	{
		free(m_HashContext);
		free(HAFP[m_HashAlgorithmID].Context);
	}
}

void HashingOperations::DoHash(char *OriginalDocument, const int OriginalDocumentLength, char *ResultingHashValue) const
// Beschreibung:	berechnet den Hashwert des übergebenen Dokuments und speichert ihn;
// Parameter:		Dokument, das gehasht werden soll [in]; Länge des zu hashenden Dokuments [int]; Speicherbereich, in den
//					der Hashwert gespeichert werden soll[in & out];
// Rückgabewert:	Fehlercode;
{
	HashAlgorithmsFP *p_HFP = &(HAFP[m_HashAlgorithmID]);

#ifdef _SIG_ATT_ALWAYS_INIT_HASH

	p_HFP->fp_Init(p_HFP->Context);
	
#endif
	
#ifndef _SIG_ATT_ALWAYS_INIT_HASH

	memcpy(p_HFP->Context, m_HashContext, p_HFP->ContextSize);

#endif

	p_HFP->fp_Update(p_HFP->Context, OriginalDocument, OriginalDocumentLength);
	p_HFP->fp_Final(ResultingHashValue, p_HFP->Context);
}

void HashingOperations::chunkHashInit()
{
	HashAlgorithmsFP *fp = &(HAFP[m_HashAlgorithmID]);
	fp->fp_Init(fp->Context);
}

void HashingOperations::chunkHashUpdate(void *_message, const int _messageLength)
{
	HashAlgorithmsFP *fp = &(HAFP[m_HashAlgorithmID]);
	fp->fp_Update(fp->Context, _message, _messageLength);
}

void HashingOperations::chunkHashFinal(char *_messageDigest)
{
	HashAlgorithmsFP *fp = &(HAFP[m_HashAlgorithmID]);
	fp->fp_Final(_messageDigest, fp->Context);
}

void HashingOperations::SetData(int HashAlgorithmID)
{
	int StructLength = sizeof(HAFP) / sizeof(HashAlgorithmsFP);
	m_AlgorithmCounter = 0;

	if (0 == StructLength)
	{
		m_Errorcode = _SIG_ATT_NO_HASH_ALGORITHM_IMPLEMENTED;
		return;
	}

	m_HashAlgorithmID = HashAlgorithmID;
	if (m_HashAlgorithmID < 0 || m_HashAlgorithmID >= StructLength)
	{
		m_Errorcode = _SIG_ATT_BAD_HASH_ALGORITHM;
		return;
	}

	m_HashContext = (void *) malloc(HAFP[m_HashAlgorithmID].ContextSize);
	HAFP[m_HashAlgorithmID].Context = (void *) malloc(HAFP[m_HashAlgorithmID].ContextSize);

#ifndef _SIG_ATT_ALWAYS_INIT_HASH

	HAFP[m_HashAlgorithmID].fp_Init(m_HashContext);

#endif

	m_Errorcode = _SIG_ATT_OK;
}

int HashingOperations::GetHashAlgorithmBitLength() const
{
	return HAFP[m_HashAlgorithmID].BitLength;
}

char *HashingOperations::GetHashAlgorithmName() const
{
	return HAFP[m_HashAlgorithmID].Name;
}

int HashingOperations::GetHashOpsPerSecond() const
{
	return HAFP[m_HashAlgorithmID].HashOpsPerSecond;
}
