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

// ModifiedDocument_Attachments.h: Schnittstelle für die Klasse ModifiedDocument_Attachments.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODIFIEDDOCUMENT_ATTACHMENTS_H__83E16D54_E57C_11D6_9DFD_000629718A52__INCLUDED_)
#define AFX_MODIFIEDDOCUMENT_ATTACHMENTS_H__83E16D54_E57C_11D6_9DFD_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ModifiedDocumentForHashing.h"

class ModifiedDocument_Attachments : public ModifiedDocumentForHashing  
{
public:
	ModifiedDocument_Attachments(const char *OriginalDocument, const int OriginalDocumentLength,
								const int SignificantBitLength, const int AttMethod)
	{
		SetData(OriginalDocument, OriginalDocumentLength, SignificantBitLength, AttMethod);
	}

	void ModifyDocument(const char *HashValue);
	int GetErrorcode() const { return m_Errorcode; }

private:

#ifdef _SIG_ATT_MODIFYING_OPTIMIZER

	unsigned char m_AttachmentTable[256 * 4];

#endif

#ifndef _SIG_ATT_MODIFYING_OPTIMIZER

	unsigned char m_AttachmentTable[256][4];

#endif

	unsigned char m_ch_unprintable[4];
	unsigned int m_SignificantByteLength;
	unsigned int m_LastBits;
	unsigned int m_LastAttachableBytes;
	unsigned int m_OriginalDocumentLength;

	void SetData(const char *OriginalDocument, const int OriginalDocumentLength,
		const int SignificantBitLength, const int AttMethod);
	virtual void ModifyOriginalDocument(const int RunNo);

};

#endif // !defined(AFX_MODIFIEDDOCUMENT_ATTACHMENTS_H__83E16D54_E57C_11D6_9DFD_000629718A52__INCLUDED_)
