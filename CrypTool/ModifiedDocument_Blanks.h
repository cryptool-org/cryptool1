// ModifiedDocument_Blanks.h: Schnittstelle für die Klasse ModifiedDocument_Blanks.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODIFIEDDOCUMENT_BLANKS_H__83E16D53_E57C_11D6_9DFD_000629718A52__INCLUDED_)
#define AFX_MODIFIEDDOCUMENT_BLANKS_H__83E16D53_E57C_11D6_9DFD_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ModifiedDocumentForHashing.h"

class ModifiedDocument_Blanks : public ModifiedDocumentForHashing  
{
public:
	ModifiedDocument_Blanks(const char *OriginalDocument, const int OriginalDocumentLength,
								const int SignificantBitLength, const int Blanks, const int DoubledBlanks)
	{
		SetData(OriginalDocument, OriginalDocumentLength, SignificantBitLength, Blanks, DoubledBlanks);
	}

	void ModifyDocument(const char *HashValue);
	int GetErrorcode() const { return m_Errorcode; }

private:

	void SetData(const char *OriginalDocument, const int OriginalDocumentLength, const int SignificantBitLength,
		const int Blanks, const int DoubledBlanks);
	virtual void ModifyOriginalDocument(const int RunNo);

};

#endif // !defined(AFX_MODIFIEDDOCUMENT_BLANKS_H__83E16D53_E57C_11D6_9DFD_000629718A52__INCLUDED_)
