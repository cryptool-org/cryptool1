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


// ModifiedDocument_Blanks.cpp: Implementierung der Klasse ModifiedDocument_Blanks.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModifiedDocument_Blanks.h"
#include "CrypToolApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

void ModifiedDocument_Blanks::SetData(const char *OriginalDocument, const int OriginalDocumentLength,
									 const int SignificantBitLength, const int Blanks, const int DoubledBlanks)
// Beschreibung:	Reserviert den Speicher, den das modifizierte Dokument maximal benötigen könnte (wenn alle signifikanten
//					bits gesetzt sind),
//					setzt m_GeneralPositionsTable - in ihr sind die Positionen gespeichert, an denen Veränderungen im
//					Dokument vorgenommen werden können - in m_ModifiablePositions ist die Anzahl der Positionen abgelegt;
// Parameter:		das Originaldokument (= Ausgangsbasis für Modifikationen) [in],
//					Länge des Originaldokuments [in], signifikante Bitlänge [in], Flag, ob vor einem Zeilenumbruch ein
//					weiteres Leerzeichen eingefügt werden soll [in], Flag, ob ein Leerzeichen verdoppelt werden kann [in];
// Rückgabewert:	keiner;
{
	int counter = 0, ii;

	ModifiedDocumentForHashing::SetData(OriginalDocument, OriginalDocumentLength, SignificantBitLength);

	memcpy(m_DocumentData, OriginalDocument, OriginalDocumentLength);

	for (ii = m_OriginalDocument->GetDocumentLength() - 1; ii >= 0 ; ii --)
	{
		if (1 == Blanks && '\r' == m_OriginalDocument->GetDocumentDataAt(ii))	// ToDo: Problematik CR + LF unter UNIX!
		{
			m_GeneralPositionsTable[counter] = ii;
			counter ++;
			if (counter == SignificantBitLength)	// die Anzahl der Stellen, an denen im Dokument Modifkationen durchge-
			{										// führt werden können, ist auf die Anzahl der signifikanten bits
				break;								// begrenzt
			}
		}

		else if (1 == DoubledBlanks && ' ' == m_OriginalDocument->GetDocumentDataAt(ii))
		{
			m_GeneralPositionsTable[counter] = ii;
			counter ++;
			if (counter == SignificantBitLength)	// die Anzahl der Stellen, an denen im Dokument Modifkationen durchge-
			{										// führt werden können, ist auf die Anzahl der signifikanten bits
				break;								// begrenzt
			}
		}
	}

	m_ModifiablePositions = counter;				// m_ModifiablePositions = Anzahl der modifizierbaren Stellen
	if (m_ModifiablePositions < SignificantBitLength)
	{
		m_Errorcode = _SIG_ATT_BAD_MODIFIABILITY;	// in diesem Dokument gibt es zu wenige Stellen, an denen es modifiziert
	}												// werden kann
	else
	{
		m_Errorcode = _SIG_ATT_OK;
	}
}

void ModifiedDocument_Blanks::ModifyDocument(const char *HashValue)
// Beschreibung:	Modifiziert dieses Dokument (Suchrichtung: von rechts nach links im Dokument) an seinen signifikanten
//					Stellen (m_GeneralPositions), wenn das entsprechende bit des Hashwerts (dieser wird von links nach
//					rechts durchgegangen) auf '1' gesetzt ist;
// Parameter:		Hashwert [in];
// Rückgabewert:	keiner;
{
	int ii, MaxPositions = 0, OrigDocCurrPos, SelectedPositionsTable[_MAX_HASH_BIT_LENGTH];
	char c_current;

	OrigDocCurrPos = m_OriginalDocument->GetDocumentLength();
	
	for (ii = 1; ii <= m_ModifiablePositions; ii ++)		// hier werden die Stellen, an denen grundsätzlich eine Modifi-
	{														// kation im Dokument durchgeführt werden können
		c_current = HashValue[(ii - 1) / 8];				// (m_GeneralPositionsTable), auf die Stellen reduziert, bei denen
		int shift_it = 7 - ((ii - 1) % 8);					// das entsprechende bit im Hashwert gesetzt ist und in
		if(((c_current >> shift_it) & 1))					// SelectedPositionsTable gespeichert
		{
			SelectedPositionsTable[MaxPositions] = m_GeneralPositionsTable[ii - 1];
			MaxPositions ++;
		}
	}

	m_ModifiedBytes = MaxPositions;
	
	for (ii = 0; ii < MaxPositions; ii ++)
	{
		memcpy(m_DocumentData + (SelectedPositionsTable[ii] + MaxPositions - ii),
			m_OriginalDocument->GetDocumentData() + SelectedPositionsTable[ii],
			OrigDocCurrPos - SelectedPositionsTable[ii]);

		m_DocumentData[SelectedPositionsTable[ii] + MaxPositions - ii - 1] = ' ';
		OrigDocCurrPos = SelectedPositionsTable[ii];
	}

	memcpy(m_DocumentData + m_GeneralPositionsTable[m_ModifiablePositions - 1],
		m_OriginalDocument->GetDocumentData() + m_GeneralPositionsTable[m_ModifiablePositions - 1],
		OrigDocCurrPos - m_GeneralPositionsTable[m_ModifiablePositions - 1]);
	// der Teil des Dokumentes, der vor Position m_GeneralPositionsTable[m_ModifiablePositions - 1] liegt, verändert sich
	// nie, muss also nicht kopiert werden

	m_DocumentLength = m_OriginalDocument->GetDocumentLength() + MaxPositions;
}

void ModifiedDocument_Blanks::ModifyOriginalDocument(const int RunNo)
{/*
	m_OriginalDocument->SetDocumentDataAt(m_OriginalDocument->GetDocumentLength() - 2, m_ch_unprintable[RunNo / 4]);	
	m_OriginalDocument->SetDocumentDataAt(m_OriginalDocument->GetDocumentLength() - 1, m_ch_unprintable[RunNo % 4]);*/
}
