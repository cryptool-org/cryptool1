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
