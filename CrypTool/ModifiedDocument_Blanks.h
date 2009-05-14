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
