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
}
HAFP[] =
{/*
	{
		(fp_Init_t)theApp.SecudeLib.sec_MD2Init,
		(fp_Update_t)theApp.SecudeLib.sec_MD2Update,
		(fp_Final_t)theApp.SecudeLib.sec_MD2Final,
		NULL,
		sizeof(SEC_MD2_CTX),
		128,
		"MD2"
	},
	{
		(fp_Init_t)theApp.SecudeLib.sec_MD4Init,
		(fp_Update_t)theApp.SecudeLib.sec_MD4Update,
		(fp_Final_t)theApp.SecudeLib.sec_MD4Final,
		NULL,
		sizeof(SEC_MD4_CTX),
		128,
		"MD4"
	},
	{
		(fp_Init_t)theApp.SecudeLib.sec_MD5Init,
		(fp_Update_t)theApp.SecudeLib.sec_MD5Update,
		(fp_Final_t)theApp.SecudeLib.sec_MD5Final,
		NULL,
		sizeof(SEC_MD5_CTX),
		128,
		"MD5"
	}*/
	{
		(fp_Init_t) __SSL::MD2_Init,
		(fp_Update_t) __SSL::MD2_Update,
		(fp_Final_t) __SSL::MD2_Final,
		NULL,
		sizeof(__SSL::MD2_CTX),
		128,
		"MD2"
	},
	{
		(fp_Init_t) __SSL::MD4_Init,
		(fp_Update_t) __SSL::MD4_Update,
		(fp_Final_t) __SSL::MD4_Final,
		NULL,
		sizeof(__SSL::MD4_CTX),
		128,
		"MD4"
	},
	{
		(fp_Init_t) __SSL::MD5_Init,
		(fp_Update_t) __SSL::MD5_Update,
		(fp_Final_t) __SSL::MD5_Final,
		NULL,
		sizeof(__SSL::MD5_CTX),
		128,
		"MD5"
	},
	{
		(fp_Init_t) __SSL::RIPEMD160_Init,
		(fp_Update_t) __SSL::RIPEMD160_Update,
		(fp_Final_t) __SSL::RIPEMD160_Final,
		NULL,
		sizeof(__SSL::RIPEMD160_CTX),
		160,
		"RIPEMD-160"
	},
	{
		(fp_Init_t) __SSL::SHA_Init,
		(fp_Update_t) __SSL::SHA_Update,
		(fp_Final_t) __SSL::SHA_Final,
		NULL,
		sizeof(__SSL::SHA_CTX),
		160,
		"SHA"
	},
	{
		(fp_Init_t) __SSL::SHA1_Init,
		(fp_Update_t) __SSL::SHA1_Update,
		(fp_Final_t) __SSL::SHA1_Final,
		NULL,
		sizeof(__SSL::SHA_CTX),
		160,
		"SHA-1"
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
