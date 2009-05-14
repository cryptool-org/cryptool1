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


// ModifiedDocument_Attachments.cpp: Implementierung der Klasse ModifiedDocument_Attachments.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModifiedDocument_Attachments.h"
#include "CrypToolApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

void ModifiedDocument_Attachments::SetData(const char *OriginalDocument, const int OriginalDocumentLength,
									 const int SignificantBitLength, const int AttMethod)
// Beschreibung:	Reserviert den Speicher, den das modifizierte Dokument maximal benötigen könnte (wenn alle signifikanten
//					bits gesetzt sind),
//					setzt m_GeneralPositionsTable - in ihr sind die Positionen gespeichert, an denen Veränderungen im
//					Dokument vorgenommen werden können - in m_GeneralPositionsTable[0] ist die Anzahl der Positionen abgelegt
// Parameter:		das Originaldokument (= Ausgangsbasis für Modifikationen) (OriginalDocument [Zeiger auf const char]),
//					Länge des Originaldokuments (OriginalDocumentLength [const int]),
//					Bitlänge des verwendeten Hash-Algorithmus' (HashAlgorithmBitLength [const int]);
// Rückgabewert:	keiner;
{
	int ii;

	ModifiedDocumentForHashing::SetData(OriginalDocument, OriginalDocumentLength, SignificantBitLength);
	m_ModifiablePositions = SignificantBitLength;

	m_DocumentLength = OriginalDocumentLength + (m_ModifiablePositions + 1) / 2;
	m_ModifiedBytes = (m_ModifiablePositions + 1) / 2;

#ifdef _SIG_ATT_SPEED_INCREMENT

	m_ModifiedBytes += 2;

#endif

	if (0 == AttMethod)	// druckbare Zeichen ('A', 'B', 'C', 'D') werden angehängt
	{
		m_ch_unprintable[0] = 65;
		m_ch_unprintable[1] = 66;
		m_ch_unprintable[2] = 67;
		m_ch_unprintable[3] = 68;
	}
	else // nicht druckbare Zeichen werden angehängt
	{
		m_ch_unprintable[0] = 9;
		m_ch_unprintable[1] = 10;
		m_ch_unprintable[2] = 32;
		m_ch_unprintable[3] = 160;
	}
	// in dieses kleine Array schreibt man die Zeichen, die beim Modifizieren an das Dokument gehängt werden können.
	// Damit der Empfänger des Dokumentes keinen Verdacht schöpft, empfiehlt es sich, Zeichen zu verwenden, die den Inhalt
	// nicht verändern oder nicht darstellbar sind

#ifdef _SIG_ATT_MODIFYING_OPTIMIZER

	for (ii = 0; ii < 256; ii ++)
	{
		m_AttachmentTable[ii * 4 + 0] = m_ch_unprintable[(ii / 64) % 4];
		m_AttachmentTable[ii * 4 + 1] = m_ch_unprintable[(ii / 16) % 4];
		m_AttachmentTable[ii * 4 + 2] = m_ch_unprintable[(ii / 4) % 4];
		m_AttachmentTable[ii * 4 + 3] = m_ch_unprintable[ii % 4];
	}

#endif

#ifndef _SIG_ATT_MODIFYING_OPTIMIZER

	for (ii = 0; ii < 256; ii ++)
	{
		m_AttachmentTable[ii][0] = m_ch_unprintable[(ii / 64) % 4];
		m_AttachmentTable[ii][1] = m_ch_unprintable[(ii / 16) % 4];
		m_AttachmentTable[ii][2] = m_ch_unprintable[(ii / 4) % 4];
		m_AttachmentTable[ii][3] = m_ch_unprintable[ii % 4];
	}

#endif

	m_SignificantByteLength = m_ModifiablePositions / 8;
	m_LastBits = m_ModifiablePositions % 8;
	m_LastAttachableBytes = (1 + m_LastBits) / 2;
	m_OriginalDocumentLength = m_OriginalDocument->GetDocumentLength();

#ifdef _SIG_ATT_SPEED_INCREMENT

	ModifyOriginalDocument(0);

#endif

	memcpy(m_DocumentData, m_OriginalDocument->GetDocumentData(), OriginalDocumentLength);

	m_Errorcode = _SIG_ATT_OK;
}

void ModifiedDocument_Attachments::ModifyDocument(const char *HashValue)
// Beschreibung:	Modifiziert dieses Dokument (Suchrichtung: von rechts nach links im Dokument) an seinen signifikanten
//					Stellen (m_GeneralPositions), wenn das entsprechende bit des Hashwerts (dieser wird von links nach
//					rechts durchgegangen) auf '1' gesetzt ist;
// Parameter:		Hashwert (HashValue [in]); Anzahl der signifikanten bits (= maximale Anzahl der Veränderungen)
//					(SignificantBitLength [in]);
// Rückgabewert:	keiner;
{
	unsigned char ch;
	unsigned int ii;
	long *l_dest, *l_src;

	// zunächst werden die "kompletten" Bytes der signifikanten Bitlänge zum Modifizieren benutzt...

#ifdef _SIG_ATT_MODIFYING_OPTIMIZER

	l_dest = (long *)(m_DocumentData + m_OriginalDocumentLength);
	for (ii = 0; ii < m_SignificantByteLength; ii ++)
	{
		l_src = (long *)(m_AttachmentTable + 4 * (unsigned)(unsigned char)HashValue[ii]);
	    *l_dest ++ = *l_src;
	}

#endif

#ifndef _SIG_ATT_MODIFYING_OPTIMIZER

	unsigned int jj;

	for (ii = 0; ii < m_SignificantByteLength; ii ++)
	{
		m_DocumentData[m_OriginalDocumentLength + 4 * ii] = m_AttachmentTable[(unsigned char) HashValue[ii]][0];
		m_DocumentData[m_OriginalDocumentLength + 4 * ii + 1] = m_AttachmentTable[(unsigned char) HashValue[ii]][1];
		m_DocumentData[m_OriginalDocumentLength + 4 * ii + 2] = m_AttachmentTable[(unsigned char) HashValue[ii]][2];
		m_DocumentData[m_OriginalDocumentLength + 4 * ii + 3] = m_AttachmentTable[(unsigned char) HashValue[ii]][3];
	}

#endif

	// ... und jetzt die restlichen Bits, d.h. (signifikante Bitlänge % 8)

	if (0 != m_LastBits)
	{
		ch = HashValue[ii] &  ~(0xff >> m_LastBits);

#ifdef _SIG_ATT_MODIFYING_OPTIMIZER

		char *dest = (char *) l_dest;
		char *src = (char *)(m_AttachmentTable + ch * 4);
		switch (m_LastAttachableBytes)
		{
			case 4: *(dest + 3) = *(src + 3);
			case 3: *(dest + 2) = *(src + 2);
			case 2: *(dest + 1) = *(src + 1);
			case 1: *dest = *src;
		}

#endif

#ifndef _SIG_ATT_MODIFYING_OPTIMIZER

		for (jj = 0; jj < m_LastAttachableBytes; jj ++)
		{
			m_DocumentData[m_OriginalDocumentLength + 4 * ii + jj] = m_AttachmentTable[ch][jj];
		}

#endif

	}
}

void ModifiedDocument_Attachments::ModifyOriginalDocument(const int RunNo)
{
	m_OriginalDocument->SetDocumentDataAt(m_OriginalDocument->GetDocumentLength() - 2, m_ch_unprintable[RunNo / 4]);
	m_OriginalDocument->SetDocumentDataAt(m_OriginalDocument->GetDocumentLength() - 1, m_ch_unprintable[RunNo % 4]);
	memcpy(m_DocumentData, m_OriginalDocument->GetDocumentData(), m_OriginalDocument->GetDocumentLength());
}
