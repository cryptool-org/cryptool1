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

// ModifiedDocumentForHashing.cpp: Implementierung der Klasse ModifiedDocumentForHashing.
//
// Jan Blumenstein, Deutsche Bank AG, September 2002
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModifiedDocumentForHashing.h"
#include "CrypToolApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

void ModifiedDocumentForHashing::SetData(const char *OriginalDocument, const int OriginalDocumentLength,
									 const int SignificantBitLength)
// Beschreibung:	Reserviert den Speicher, den das modifizierte Dokument maximal benötigen könnte (wenn alle signifikanten
//					bits gesetzt sind),
//					setzt m_GeneralPositionsTable - in ihr sind die Positionen gespeichert, an denen Veränderungen im
//					Dokument vorgenommen werden können - in m_ModifiablePositions ist die Anzahl der Positionen abgelegt
// Parameter:		das Originaldokument (= Ausgangsbasis für Modifikationen) (OriginalDocument [Zeiger auf const char]),
//					Länge des Originaldokuments (OriginalDocumentLength [const int]),
//					Bitlänge des verwendeten Hash-Algorithmus' (HashAlgorithmBitLength [const int]);
// Rückgabewert:	keiner;
{
	m_DocumentLength = OriginalDocumentLength + SignificantBitLength;
	m_DocumentData = new char[m_DocumentLength];
	m_OriginalDocument = new DocumentForHashing(OriginalDocument, OriginalDocumentLength);
	m_ModifiedBytes = 0;
}
