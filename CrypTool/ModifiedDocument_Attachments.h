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
