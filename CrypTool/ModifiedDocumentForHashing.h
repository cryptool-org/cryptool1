// ModifiedDocumentForHashing.h: Schnittstelle für die Klasse ModifiedDocumentForHashing.
//
// Jan Blumenstein, Deutsche Bank AG, September 2002
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODIFIEDDOCUMENTFORHASHING_H__2EEFBED0_C007_11D6_9DDC_000629718A52__INCLUDED_)
#define AFX_MODIFIEDDOCUMENTFORHASHING_H__2EEFBED0_C007_11D6_9DDC_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "DocumentForHashing.h"


class ModifiedDocumentForHashing : public DocumentForHashing  
{
public:
	ModifiedDocumentForHashing()
	{
		m_OriginalDocument = NULL;
	}

	ModifiedDocumentForHashing(const char *OriginalDocument, const int OriginalDocumentLength,
								const int SignificantBitLength)
	{
		m_OriginalDocument = NULL;
		SetData(OriginalDocument, OriginalDocumentLength, SignificantBitLength);
	}

	virtual ~ModifiedDocumentForHashing()
	{
		if (NULL != m_OriginalDocument)
		{
			delete m_OriginalDocument;
		}
	}

	virtual void ModifyDocument(const char *HashValue) = 0;
	virtual int GetErrorcode() const = 0;
	virtual void ModifyOriginalDocument(const int RunNo) = 0;
	DocumentForHashing *GetOriginalDocument() const { return m_OriginalDocument; }

protected:
	DocumentForHashing *m_OriginalDocument;
	int m_Errorcode;
	int m_GeneralPositionsTable [_MAX_HASH_BIT_LENGTH];
	int m_ModifiablePositions;

	void SetData(const char *OriginalDocument, const int OriginalDocumentLength, const int SignificantBitLength);
	
};

#endif // !defined(AFX_MODIFIEDDOCUMENTFORHASHING_H__2EEFBED0_C007_11D6_9DDC_000629718A52__INCLUDED_)
